#ifndef BUNURISERVICII_H
#define BUNURISERVICII_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std;

class BunuriServicii
{
    public:
        BunuriServicii();
        BunuriServicii(string, string, double);
        //setters
        void setNume(string);
        void setTip(string);
        void setRata(double);
        //getters
        string getNume();
        string getTip();
        double getRata();
        //alte metode
        void input();
        void printDetalii();
        virtual ~BunuriServicii();

    protected:

    private:
        string nume;
        string tip;
        double rata;
};

#endif // BUNURISERVICII_H
