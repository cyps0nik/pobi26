/**
 * @file LogicContainer.h
 * @brief Klasa integrująca warstwę danych z warstwą logiki biznesowej.
 * @details Agreguje instancję StorageContainer oraz wszystkich managerów,
 * zapewniając spójny dostęp do funkcjonalności systemu z poziomu interfejsu użytkownika lub testów.
 */

#ifndef WARSZTATSAMOCHODOWY_LOGICCONTAINER_H
#define WARSZTATSAMOCHODOWY_LOGICCONTAINER_H

#include <memory>
#include "StorageContainer.h"
#include "managers/CarManager.h"
#include "managers/ClientManager.h"
#include "managers/MechanicManager.h"
#include "managers/RepairManager.h"
#include "managers/ResourceManager.h"

/**
 * @class LogicContainer
 * @brief Kontener zarządzający instancjami managerów logiki biznesowej.
 * @details Klasa realizuje wzorzec wstrzykiwania zależności,
 * przekazując odpowiednie repozytoria ze StorageContainer do poszczególnych managerów.
 */
class LogicContainer {
private:
    /** @brief Inteligentny wskaźnik do magazynu danych. */
    std::shared_ptr<StorageContainer> storage;

    /** @brief Manager zarządzający operacjami na klientach. */
    ClientManagerPtr clientManager;

    /** @brief Manager zarządzający flotą aut. */
    CarManagerPtr carManager;

    /** @brief Manager zarządzający mechanikami. */
    MechanicManagerPtr mechanicManager;

    /** @brief Manager obsługujący procesy napraw. */
    RepairManagerPtr repairManager;

    /** @brief Manager zarządzający zasobami. */
    ResourceManagerPtr resourceManager;

public:
    /**
     * @brief Konstruktor inicjalizujący całą strukturę logiczną systemu.
     * @details Tworzy StorageContainer, a następnie na jego bazie inicjalizuje managerów.
     */
    LogicContainer();

    /** @brief Destruktor zwalniający zasoby. */
    ~LogicContainer();

    /**
     * @brief Pobiera managera klientów.
     * @return ClientManagerPtr Wskaźnik do obiektu ClientManager.
     */
    ClientManagerPtr getClientManager() const;

    /**
     * @brief Pobiera managera samochodów.
     * @return CarManagerPtr Wskaźnik do obiektu CarManager.
     */
    CarManagerPtr getCarManager() const;

    /**
     * @brief Pobiera managera mechaników.
     * @return MechanicManagerPtr Wskaźnik do obiektu MechanicManager.
     */
    MechanicManagerPtr getMechanicManager() const;

    /**
     * @brief Pobiera managera zasobów.
     * @return ResourceManagerPtr Wskaźnik do obiektu ResourceManager.
     */
    ResourceManagerPtr getResourceManager() const;

    /**
     * @brief Pobiera managera napraw.
     * @return RepairManagerPtr Wskaźnik do obiektu RepairManager.
     */
    RepairManagerPtr getRepairManager() const;

    /**
     * @brief Zapisuje aktualny stan całego systemu do pliku.
     * @details Metoda deleguje operację zapisu do obiektu StorageContainer,
     * który zajmuje się serializacją wszystkich repozytoriów (klientów, aut, napraw itd.).
     * @param filename Nazwa lub ścieżka pliku, do którego mają zostać zapisane dane.
     */
    void saveSystem(const std::string& filename) const;
};


#endif //WARSZTATSAMOCHODOWY_LOGICCONTAINER_H