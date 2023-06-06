#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <thread>
#include <chrono>
using namespace std;

#include "BunuriServicii.h"
#include "GestionareCheltuieli.h"
#include "Data.h"
#include "Plata.h"

#define wait(x) this_thread::sleep_for(chrono::milliseconds(x))


BunuriServicii::BunuriServicii()
{
    nume = " ";
    tip = " ";
    rata = 0.00;
}

BunuriServicii::BunuriServicii(string nume, string tip, double rata)
{
    this->nume = nume;
    this->tip = tip;
    this->rata = rata;
}

void BunuriServicii::setNume(string nume)
{
    this->nume = nume;
    return;
}

void BunuriServicii::setTip(string tip)
{
    this->tip = tip;
    return;
}

void BunuriServicii::setRata(double rata)
{
    this->rata = rata;
    return;
}

string BunuriServicii::getNume()
{
    return nume;
}

string BunuriServicii::getTip()
{
    return tip;
}

double BunuriServicii::getRata()
{
    return rata;
}

void BunuriServicii::input()
{
    cout<<"Numele bunului sau serviciului: ";
    getline(cin >> ws, nume);
    cout<<endl;
    cout<<"Tipul bunului sau serviciului: ";
    GestionareCheltuieli::printTipuriBS();
    cout<<"Optiuni: \n";
    cout << "[01] - Alegeti un bun sau serviciu din lista aceasta\n";
    cout << "[02] - Adaugati un nou tip de bun sau serviciu\n\n";
    cout << "Dati optiunea: : ";
    int optiune;
    cin >> optiune;
    while(optiune != 1 && optiune != 2)
    {
        cout<<"Optiune invalida!";
        cin>>optiune;
    }
    if(optiune == 1)
    {
        tip = GestionareCheltuieli::getTipBS();
    }
    else if(optiune == 2)
    {
        cout<<" Introduceti noul tip: ";
        getline(cin >> ws, tip);
        GestionareCheltuieli::adaugaTipBS(tip);
    }
    return;

}

void BunuriServicii::printDetalii()
{
    cout << "Nume bun/serviciu: " << nume << endl;
    cout << "Tip bun/serviciu: " << tip << endl;
    cout << "Rata bun/serviciu: " << rata << endl;
    return;
}

BunuriServicii::~BunuriServicii()
{
    //dtor
}
