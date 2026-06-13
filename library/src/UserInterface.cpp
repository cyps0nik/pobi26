/**
 * @file UserInterface.cpp
 * @brief Implementacja modułów sterujących i walidacji wejścia interfejsu CLI.
 */

#include "../include/UserInterface.h"
#include "model/Client.h"
#include "model/Car.h"
#include "model/Engine.h"
#include "model/Accumulator.h"
#include "model/naprawa/Repair.h"
#include "model/naprawa/Mechanic.h"
#include "model/naprawa/Resource.h"
#include "model/naprawa/DiagnosticService.h"
#include "model/naprawa/NewPartReplacement.h"
#include "model/naprawa/PartRegenaration.h"

#include <iostream>
#include <limits>
#include <boost/date_time.hpp>

using namespace std;
namespace pt = boost::posix_time;

UserInterface::UserInterface(LogicContainerPtr logicContainer) : logic(logicContainer) {}

void UserInterface::clearInputBuffer() const {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int UserInterface::readInt(const string& prompt) const {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            clearInputBuffer();
            return value;
        } else {
            cout << "[Blad] Oczekiwano poprawnej wartości liczbowej. Sprobuj ponownie.\n";
            clearInputBuffer();
        }
    }
}

string UserInterface::readString(const string& prompt) const {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void UserInterface::run() {
    bool running = true;
    while (running) {
        cout << "\n==================================================\n";
        cout << "      PANEL PRACOWNIKA WARSZTATU SAMOCHODOWEGO\n";
        cout << "==================================================\n";
        cout << "1. Modul Klientow i Floty Pojazdow (CRUD)\n";
        cout << "2. Modul Rejestracji i Rozliczania Zlecen\n";
        cout << "3. Modul Zarzadzania Zasobami i Personelem\n";
        cout << "0. Wyjdz z systemu aplikacji\n";

        int choice = readInt("Wprowadz opcje: ");

        switch (choice) {
            case 1:
                manageClientsAndCars();
                break;
            case 2:
                manageRepairs();
                break;
            case 3:
                manageResourcesAndPersonel();
                break;
            case 0:
                cout << "Zamykanie systemu i bezpieczne odpinanie struktur bazy danych...\n";
                running = false;
                break;
            default:
                cout << "[Blad] Skladowa menu o podanym numerze nie istnieje.\n";
        }
    }
}

void UserInterface::manageClientsAndCars() {
    bool back = false;
    while (!back) {
        cout << "\n--- ZARZADZANIE KLIENTAMI I POJAZDAMI (PElNE CRUD) ---\n";
        cout << "1. Rejestracja nowego klienta (Create)\n";
        cout << "2. Wyszukiwanie klienta po identyfikatorze PESEL (Read)\n";
        cout << "3. Wyrejestrowanie/Archiwizacja klienta (Delete)\n";
        cout << "4. Wyswietl pelna liste aktywnych klientow (Read)\n";
        cout << "5. Rejestracja nowego pojazdu klienta (Create)\n";
        cout << "6. Wyszukiwanie pojazdu po numerze VIN (Read)\n";
        cout << "7. Wyrejestrowanie/Archiwizacja pojazdu z systemu (Delete)\n";
        cout << "0. Powrot do menu glownego\n";

        int choice = readInt("Wybierz opcje: ");
        switch (choice) {
            case 1: {
                string fName = readString("Podaj imie klienta: ");
                string lName = readString("Podaj nazwisko klienta: ");
                string phone = readString("Podaj numer telefonu: ");
                string email = readString("Podaj adres email: ");
                string pesel = readString("Podaj numer PESEL: ");

                try {
                    ClientPtr nc = logic->getClientManager()->registerClient(fName, lName, phone, email, pesel);
                    cout << "[Sukces] Operacja powiodla sie: " << nc->getInfo() << "\n";
                } catch (const invalid_argument& e) {
                    cout << "[Blad walidacji danych wejsciowych] " << e.what() << "\n";
                }
                break;
            }
            case 2: {
                string pesel = readString("Podaj PESEL: ");
                ClientPtr client = logic->getClientManager()->getClient(pesel);
                if (client) {
                    cout << "[Wynik] " << client->getInfo() << " | Status archiwalny: " << (client->isArchive() ? "Tak" : "Nie") << "\n";
                } else {
                    cout << "[Info] Brak klienta o podanym numerze identyfikacyjnym.\n";
                }
                break;
            }
            case 3: {
                string pesel = readString("Podaj PESEL klienta do usuniecia z aktywnego uzytku: ");
                ClientPtr client = logic->getClientManager()->getClient(pesel);
                if (client) {
                    logic->getClientManager()->unregisterClient(client);
                    cout << "[Sukces] Klient oznaczony jako archiwalny.\n";
                } else {
                    cout << "[Blad] Wskazany klient nie istnieje.\n";
                }
                break;
            }
            case 4: {
                auto clients = logic->getClientManager()->findAllClients();
                if (clients.empty()) {
                    cout << "Baza aktywnych klientow jest pusta.\n";
                } else {
                    for (const auto& c : clients) cout << c->getInfo() << "\n";
                }
                break;
            }
            case 5: {
                string pesel = readString("Podaj PESEL wlasciciela pojazdu: ");
                ClientPtr owner = logic->getClientManager()->getClient(pesel);
                if (!owner) {
                    cout << "[Blad] Nie mozna zarejestrowac auta dla nieistniejacego klienta!\n";
                    break;
                }

                string brand = readString("Podaj marke pojazdu: ");
                string model = readString("Podaj model pojazdu: ");
                string vin = readString("Podaj unikalny numer VIN: ");

                cout << "Wybierz typ jednostki napedowej pojazdu:\n1. Silnik Spalinowy\n2. Akumulator (Pojazd Elektryczny)\n";
                int pType = readInt("Wybor: ");
                PoweredUniqPtr power = nullptr;

                if (pType == 1) {
                    int disp = readInt("Podaj pojemnosc silnika w cm3: ");
                    cout << "Rodzaj paliwa:\n1. Benzyna\n2. Diesel\n";
                    int fChoice = readInt("Wybor: ");
                    FuelType ft = (fChoice == 2) ? Diesel : Petrol;
                    power = make_unique<Engine>(disp, ft);
                } else if (pType == 2) {
                    int cap = readInt("Podaj pojemnosc ogniwa (kWh): ");
                    int deg = readInt("Podaj stopien degradacji baterii (0-100): ");
                    try {
                        power = make_unique<Accumulator>(cap, deg);
                    } catch (const invalid_argument& e) {
                        cout << "[Blad domenowy] " << e.what() << "\n";
                        break;
                    }
                } else {
                    cout << "[Blad] Wybrano niepoprawny typ zasilania.\n";
                    break;
                }

                CarPtr newCar = logic->getCarManager()->registerCar(brand, model, vin, std::move(power), owner);
                cout << "[Sukces] Pojazd przypisany do wlasciciela: " << newCar->getInfo() << "\n";
                break;
            }
            case 6: {
                string vin = readString("Podaj VIN poszukiwanego pojazdu: ");
                CarPtr car = logic->getCarManager()->getCar(vin);
                if (car) {
                    cout << "[Wynik] " << car->getInfo() << " | Status archiwalny: " << (car->isArchive() ? "Tak" : "Nie") << "\n";
                } else {
                    cout << "[Info] Brak pojazdu o podanym numerze VIN w strukturach repozytorium.\n";
                }
                break;
            }
            case 7: {
                string vin = readString("Podaj VIN pojazdu do bezpiecznej archiwizacji: ");
                CarPtr car = logic->getCarManager()->getCar(vin);
                if (car) {
                    logic->getCarManager()->unregisterCar(car);
                    cout << "[Sukces] Pojazd zostal pomyslnie wyrejestrowany z aktywnego rejestru.\n";
                } else {
                    cout << "[Blad] Nie znaleziono wskazanego pojazdu.\n";
                }
                break;
            }
            case 0:
                back = true;
                break;
            default:
                cout << "[Blad] Bledna opcja wyboru.\n";
        }
    }
}

void UserInterface::manageRepairs() {
    bool back = false;
    while (!back) {
        cout << "\n--- ZARZADZANIE ZLECENIAMI I NAPRAWAMI ---\n";
        cout << "1. Utworz nowe zlecenie naprawy pojazdu (Create)\n";
        cout << "2. Dodaj i zaplanuj usluge w ramach otwartego zlecenia\n";
        cout << "3. Aktualny koszt i podglad zlecenia (Read)\n";
        cout << "4. Zamknij i rozlicz finansowo zlecenie (Update/Delete)\n";
        cout << "5. Wykaz wszystkich aktywnych zlecen (Read)\n";
        cout << "6. Wyszukaj zarchiwizowane zlecenie po ID (Read)\n";
        cout << "0. Powrot do menu glownego\n";

        int choice = readInt("Wybierz opcje: ");
        switch (choice) {
            case 1: {
                string vin = readString("Wprowadz VIN pojazdu do naprawy: ");
                CarPtr car = logic->getCarManager()->getCar(vin);
                if (!car || car->isArchive()) {
                    cout << "[Blad] Pojazd nie figuruje w systemie lub zostal uprzednio zarchiwizowany.\n";
                    break;
                }

                RepairPtr repair = logic->getRepairManager()->registerRepair(pt::second_clock::local_time(), car);
                cout << "[Sukces] Rejestracja powiodla sie. Otwarto zlecenie o unikalnym ID: " << repair->getId() << "\n";
                break;
            }
            case 2: {
                int id = readInt("Podaj ID zlecenia naprawy: ");
                RepairPtr repair = logic->getRepairManager()->getRepair(id);
                if (repair && !repair->isArchive()) {
                    manageServicesForRepair(repair);
                } else {
                    cout << "[Blad] Zlecenie nie istnieje lub zostalo juz zamkniete.\n";
                }
                break;
            }
            case 3: {
                int id = readInt("Podaj ID zlecenia: ");
                RepairPtr repair = logic->getRepairManager()->getRepair(id);
                if (repair) {
                    repair->calculateTotal();
                    cout << "\n--- AKTUALNY STAN ZLECENIA ---\n" << repair->getInfo() << "\n";
                } else {
                    cout << "[Blad] Wskazane zlecenie nie widnieje w rejestrach.\n";
                }
                break;
            }
            case 4: {
                int id = readInt("Podaj ID zlecenia do ostatecznego zamkniecia: ");
                RepairPtr repair = logic->getRepairManager()->getRepair(id);
                if (repair && !repair->isArchive()) {
                    double total = repair->calculateTotal();
                    cout << "\n=========================================\n";
                    cout << "       FAKTURA ROZLICZENIOWA KRACOWA     \n";
                    cout << "=========================================\n";
                    cout << repair->getInfo() << "\n";
                    cout << "Do zaplaty brutto (z uwzglednieniem mnoznika napedu): " << total << " PLN\n";

                    logic->getRepairManager()->unregisterRepair(repair); // Usunięcie ze zleceń aktywnych
                    cout << "[Sukces] Zlecenie zostalo zamkniete, zasoby moga zostac zwolnione.\n";
                } else {
                    cout << "[Blad] Zlecenie jest juz archiwalne lub nie istnieje.\n";
                }
                break;
            }
            case 5: {
                auto repairs = logic->getRepairManager()->findAllRepairs();
                if (repairs.empty()) {
                    cout << "Brak zarejestrowanych aktywnych napraw w systemie.\n";
                } else {
                    for (const auto& r : repairs) cout << r->getInfo() << "\n";
                }
                break;
            }
            case 6: {
                int id = readInt("Podaj ID poszukiwanego zarchiwizowanego zlecenia: ");
                RepairPtr repair = logic->getRepairManager()->getRepair(id);

                if (repair && repair->isArchive()) {
                    cout << "\n--- ZNALEZIONO ZARCHIWIZOWANE ZLECENIE (HISTORIA) ---\n";
                    cout << repair->getInfo() << "\n";
                    cout << "Calkowity, historyczny koszt naprawy: " << repair->calculateTotal() << " PLN\n";
                } else if (repair && !repair->isArchive()) {
                    cout << "[Info] Zlecenie o nr ID " << id << " jest nadal w toku. Otworz je uzywajac opcji nr 3.\n";
                } else {
                    cout << "[Blad] Zlecenie o takim numerze identyfikacyjnym nie widnieje w bazie danych.\n";
                }
                break;
            }
            case 0:
                back = true;
                break;
            default:
                cout << "[Blad] Wybierz poprawny numer.\n";
        }
    }
}

void UserInterface::manageServicesForRepair(RepairPtr repair) {
    cout << "\n--- KREATOR I PLANOWANIE SYSTEMOWE USlUGI ---\n";

    // WALIDACJA OGRANICZEN BIZNESOWYCH: Dynamiczna kontrola dostepnosci
    auto availableMechanics = logic->getMechanicManager()->findMechanics([](const MechanicPtr& m) { return m->isAvailable(); });
    auto availableResources = logic->getResourceManager()->findResources([](const ResourcePtr& r) { return r->isAvailable(); });

    if (availableMechanics.empty()) {
        cout << "[Blad Blokady Systemu] Przerwanie procedury: Wszyscy mechanicy sa obecnie zajeci!\n";
        return;
    }
    if (availableResources.empty()) {
        cout << "[Blad Blokady Systemu] Przerwanie procedury: Wszystkie stanowiska i podnosniki sa zajete!\n";
        return;
    }

    cout << "Wybierz model biznesowy realizowanej usługi:\n";
    cout << "1. Usluga Diagnostyczna (Koszt staly)\n";
    cout << "2. Wymiana podzespolu na nowy (Czasowa + koszt nowej czesci)\n";
    cout << "3. Regeneracja czesci mechanicznej (Czasowa + stopien zuzycia)\n";
    int sType = readInt("Wybor modelu: ");

    if (sType < 1 || sType > 3) {
        cout << "[Blad] Nieprawidlowy typ operacji serwisowej.\n";
        return;
    }

    // Alokacja pracownika
    cout << "\nLista wolnych kadr pracowniczych:\n";
    for (const auto& m : availableMechanics) {
        cout << " -> ID: " << m->getId() << " | " << m->getFirstName() << " " << m->getLastName() << " (" << m->getInfo() << ")\n";
    }
    int mId = readInt("Wybierz ID pracownika: ");
    MechanicPtr mechanic = logic->getMechanicManager()->getMechanic(mId);
    if (!mechanic || !mechanic->isAvailable()) {
        cout << "[Blad] Wybrany mechanik nie istnieje lub ulegl zablokowaniu.\n";
        return;
    }

    // Alokacja sprzetu/stanowiska
    cout << "\nLista dostepnego oprzyrzadowania warsztatu:\n";
    for (const auto& r : availableResources) {
        cout << " -> ID: " << r->getId() << " | " << r->getResourceName() << " (" << r->getInfo() << ")\n";
    }
    int rId = readInt("Wybierz ID oprzyrzadowania: ");
    ResourcePtr resource = logic->getResourceManager()->getResource(rId);
    if (!resource || !resource->isAvailable()) {
        cout << "[Blad] Zasob techniczny jest niedostepny.\n";
        return;
    }

    string sName = readString("Wprowadz opis/nazwe operacji naprawczej: ");
    ServicePtr newService = nullptr;

    try {
        if (sType == 1) {
            int price = readInt("Podaj stala kwote ryczaltu diagnostycznego (PLN): ");
            newService = make_shared<DiagnosticService>(sName, price, resource, mechanic);
        } else if (sType == 2) {
            int hPrice = readInt("Podaj stawke roboczogodziny (PLN): ");
            int partPrice = readInt("Podaj koszt fabryczny nowej czesci (PLN): ");

            auto npr = make_shared<NewPartReplacement>(sName, hPrice, pt::second_clock::local_time(), partPrice, resource, mechanic);
            int hours = readInt("Podaj faktyczny czas trwania wymiany (w pelnych godzinach): ");
            npr->endService(pt::second_clock::local_time() + pt::hours(hours));
            newService = npr;
        } else if (sType == 3) { // ZINTEGROWANY TYP REGENERACJI CZESCI
            int hPrice = readInt("Podaj stawke za roboczogodzine (PLN): ");
            int usage = readInt("Wprowadz poczatkowy procent zuzycia podzespolu (0-100%): ");

            auto pr = make_shared<PartRegenaration>(sName, hPrice, pt::second_clock::local_time(), usage, resource, mechanic);
            int hours = readInt("Podaj czas trwania procesu regeneracji komponentu (w godzinach): ");
            pr->endService(pt::second_clock::local_time() + pt::hours(hours));
            newService = pr;
        }
    } catch (const invalid_argument& e) {
        cout << "[Blad Wyjatku Domeny] Walidacja odrzucona: " << e.what() << "\n";
        return;
    }

    if (newService) {
        // Blokowanie zasobów w systemie na czas trwania operacji
        mechanic->setBusy(true);
        resource->setBusy(true);
        repair->add(newService);
        cout << "[Sukces] Usluga zostala zwalidowana, zarezerwowana i podpieta pod zlecenie.\n";
    }
}

void UserInterface::manageResourcesAndPersonel() {
    bool back = false;
    while (!back) {
        cout << "\n--- ZARZADZANIE ZASOBAMI TECHNICZNYMI I KADRAMI (CRUD) ---\n";
        cout << "1. Zatrudnienie i rejestracja mechanika (Create)\n";
        cout << "2. Zwolnienie/Wyrejestrowanie mechanika (Delete)\n";
        cout << "3. Dodaj nowe stanowisko/narzedzie na stan warsztatu (Create)\n";
        cout << "4. Usun/Wyrejestruj wyposazenie z parku technicznego (Delete)\n";
        cout << "5. Przegladaj personel (Read - Filtry Specjalistyczne)\n";
        cout << "6. Przegladaj pelny stan wyposazenia technicznego (Read)\n";
        cout << "0. Powrot do menu glownego\n";

        int choice = readInt("Wybierz opcje: ");
        switch (choice) {
            case 1: {
                string fName = readString("Podaj imie pracownika: ");
                string lName = readString("Podaj nazwisko pracownika: ");
                cout << "Okresl profil specjalizacji pracownika:\n1. Elektryk\n2. Mechanik silnikowy\n3. Diagnosta\n4. Specjalista VAG\n5. Mistrz (Master)\n";
                int specChoice = readInt("Wybor: ");
                Specialization spec = engineMechanic;
                if (specChoice == 1) spec = Electrician;
                else if (specChoice == 3) spec = Diagnostician;
                else if (specChoice == 4) spec = VAGSpecialist;
                else if (specChoice == 5) spec = Master;

                MechanicPtr nm = logic->getMechanicManager()->registerMechanic(fName, lName, spec);
                cout << "[Sukces] Pracownik zarejestrowany. Przypisano ID: " << nm->getId() << "\n";
                break;
            }
            case 2: {
                int id = readInt("Podaj ID mechanika do wyrejestrowania: ");
                MechanicPtr mechanic = logic->getMechanicManager()->getMechanic(id);
                if (mechanic) {
                    logic->getMechanicManager()->unregisterMechanic(mechanic);
                    cout << "[Sukces] Mechanik zostal permanentnie wyrejestrowany z grafiku.\n";
                } else {
                    cout << "[Blad] Nie odnaleziono pracownika o tym identyfikatorze.\n";
                }
                break;
            }
            case 3: {
                string name = readString("Podaj nazwe fabryczna zasobu: ");
                cout << "Kategoria sprzetowa:\n1. Podnosnik kolumnowy\n2. Komputer diagnostyczny OBD\n3. Kompresor cisnieniowy\n4. Ogolne narzedzia warsztatowe\n";
                int rTypeChoice = readInt("Wybor: ");
                ResourceType rt = tools;
                if (rTypeChoice == 1) rt = carLift;
                else if (rTypeChoice == 2) rt = diagnosticComputer;
                else if (rTypeChoice == 3) rt = airCompressor;

                ResourcePtr nr = logic->getResourceManager()->registerResource(name, rt);
                cout << "[Sukces] Sprzet przyety na stan. Nadane systemowe ID: " << nr->getId() << "\n";
                break;
            }
            case 4: {
                int id = readInt("Podaj ID wyposazenia do wyrejestrowania: ");
                ResourcePtr resource = logic->getResourceManager()->getResource(id);
                if (resource) {
                    logic->getResourceManager()->unregisterResource(resource);
                    cout << "[Sukces] Sprzet wycofany z rejestru roboczego.\n";
                } else {
                    cout << "[Blad] Zasob techniczny nie figuruje w spisie.\n";
                }
                break;
            }
            case 5: {
                cout << "Wybierz kryteria filtrowania kadr:\n1. Wyswietl wszystkich pracownikow\n2. Filtruj: Tylko Elektrycy\n3. Filtruj: Tylko Mechanicy Silnikowi\n4. Filtruj: Tylko Diagnosci\n5. Filtruj: Tylko Specjalisci grupy VAG\n6. Filtruj: Tylko Kadra Master\n";
                int fType = readInt("Wybor filtra: ");
                vector<MechanicPtr> list;
                if (fType == 2) list = logic->getMechanicManager()->findElectricianMechanics();
                else if (fType == 3) list = logic->getMechanicManager()->findEngineMechanics();
                else if (fType == 4) list = logic->getMechanicManager()->findDiagnosticianMechanics();
                else if (fType == 5) list = logic->getMechanicManager()->findVAGSpecialistMechanics();
                else if (fType == 6) list = logic->getMechanicManager()->findMasterMechanics();
                else if (fType == 1) list = logic->getMechanicManager()->findAllMechanics();

                if (list.empty()) {
                    cout << "Brak zarejestrowanego personelu odpowiadajacego kryteriom.\n";
                } else {
                    for (const auto& m : list) cout << m->getInfo() << "\n";
                }
                break;
            }
            case 6: {
                auto resources = logic->getResourceManager()->findAllResources();
                if (resources.empty()) {
                    cout << "Brak zarejestrowanych zasobow technicznych.\n";
                } else {
                    for (const auto& r : resources) cout << r->getInfo() << "\n";
                }
                break;
            }
            case 0:
                back = true;
                break;
            default:
                cout << "[Blad] Nieznana galaz menu.\n";
        }
    }
}