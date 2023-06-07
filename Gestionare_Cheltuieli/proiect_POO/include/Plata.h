#ifndef PLATA_H
#define PLATA_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

#include "Data.h"
#include "BunuriServicii.h"
class Plata
{
    public:
        Plata();
        Plata(long long, Data, BunuriServicii, double, double);
        //setters
        void setId(long long);
        void setData(Data);
        void setBunServiciu(BunuriServicii);
        void setCantitate(double);
        void setPret(double);
        //getters
        long long getId();
        Data getData();
        BunuriServicii getBunServiciu();
        double getCantitate();
        double getPret();
        //alte metode
        void input(bool);
        void printDetalii();
        static void printDetalii(vector<Plata>);
        virtual ~Plata();

    protected:

    private:
        long long id;
        Data data;
        BunuriServicii BS;
        double cantitate;
        double pret;
};

#endif // PLATA_H
