#include "Plati.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <thread>
#include <chrono>
using namespace std;

#define wait(x) this_thread::sleep_for(chrono::milliseconds(x)) /// provide a delay of x ms

Plati::Plati()
{
    id = -1;
    data = Data();
    BS = BunuriServicii();
    cantitate = -1;
    pret = -1;
}

Plati::Plati(long long id, Data data, BunuriServicii BS, double cantitate, double pret)
{
    this->id = id;
    this->data = data;
    this->BS = BS;
    this->cantitate = cantitate;
    this->pret = pret;
}

void Plati::setId(long long id)
{
    this->id = id;
    return;
}

void Plati::setData(Data data)
{
    this->data = data;
    return;
}

void Plati::setBunServiciu(BunuriServicii BS)
{
    this->BS = BS;
    return;
}

void Plati::setCantitate(double cantitate)
{
    this->cantitate = cantitate;
    return;
}

void Plati::setPret(double pret)
{
    this->pret = pret;
    return;
}

long long Plati::getId()
{
    return id;
}

Data Plati::getData()
{
    return data;
}

BunuriServicii Plati::getBunServiciu()
{
    return BS;
}

double Plati::getCantitate()
{
    return cantitate;
}

double Plati::getPret()
{
    return pret;
}

void Plati::input(bool _data)
{
    cout << "Introduceti detaliile platii: \n";
    cout << "\n\n";
    if (_data)
        data.input(), cout << "\n";
        BS.input();
    cout << "\n";
    cout << "Cantitate (kg/l/buc): ";
    cin >> cantitate;
    while (cantitate <= 0)
    {
        cout << "Introduceti o cantitate valida: ";
        cin >> cantitate;
    }
    cout << "Pret: ";
    cin >> pret;
    BS.setRata( pret / cantitate );
    cout << "\n\n";
    return;
}

void Plati::printDetalii()
{
    cout << "\nDetalii plata: \n";
    cout << "ID: ";
    if (data.getZi() < 10)
        cout << "0";
    cout << id << endl;
    data.printDetalii();
    commodity.printDetalii();
    cout << "Cantitate: " << cantitate << endl;
    cout << "Pret: " << pret << endl;
    return;
}

void Plati::printDetalii(vector<Plati> plata)
{

}


Plati::~Plati()
{
    //dtor
}
