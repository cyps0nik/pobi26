#include <iostream>
#include <model/Engine.h>
using namespace std;

int main() {
    Engine silnik(8000, Diesel);
    cout << silnik.getFuelType();
    return 0;
}