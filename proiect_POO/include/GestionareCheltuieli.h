#ifndef GESTIONARECHELTUIELI_H
#define GESTIONARECHELTUIELI_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

#include "BunuriServicii.h"
#include "Plata.h"


class GestionareCheltuieli
{
    public:
        GestionareCheltuieli();
        static void adaugaPlata(Plata);
        static void stergePlata(Plata);
        static Plata getDetaliiPlata();
        static void printPlati();

        static void adaugaTipBS(string);
        static void stergeTipBS(string);
        static void calculTotalPlati();
        static void printTipuriBS();
        static string getTipBS();

        static void readFromCSV();
        static void writeToCSV();

        virtual ~GestionareCheltuieli();

    protected:

    private:
        static map<long long, Plata> plati;
        static map<long long, string> tipuriBS;
};

#endif // GESTIONARECHELTUIELI_H
