#include <iostream>
#include <model/Engine.h>
using namespace std;

int main() {
    Engine silnik(8000, Diesel);
    cout << silnik.getFuelType() << endl << "działa:D";
    cout << endl << "Siema" << endl;
    return 0;
}