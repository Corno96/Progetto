#include <iostream>
using namespace std;

class Consumo {
public:
    double consumo, medio, minimo, massimo;

    Consumo() : consumo(0), medio(0), minimo(0), massimo(0) {}
    Consumo(double consumo, double medio, double minimo, double massimo) : consumo(consumo), medio(medio), minimo(minimo), massimo(massimo) {}

    void stampa() {
        cout << "Consumo : " << endl;
        cout << "\tconsumo : " << consumo << endl;
        cout << "\tmedio : " << medio << endl;
        cout << "\tminimo : " << minimo << endl;
        cout << "\tmassimo: " << massimo << endl;
    }
};
