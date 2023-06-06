#include "Plata.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <thread>
#include <chrono>

#define PAGE_SIZE 15
using namespace std;

#define wait(x) this_thread::sleep_for(chrono::milliseconds(x)) ///  a delay of x ms

Plata::Plata()
{
    id = -1;
    data = Data();
    BS = BunuriServicii();
    cantitate = -1;
    pret = -1;
}

Plata::Plata(long long id, Data data, BunuriServicii BS, double cantitate, double pret)
{
    this->id = id;
    this->data = data;
    this->BS = BS;
    this->cantitate = cantitate;
    this->pret = pret;
}

void Plata::setId(long long id)
{
    this->id = id;
    return;
}

void Plata::setData(Data data)
{
    this->data = data;
    return;
}

void Plata::setBunServiciu(BunuriServicii BS)
{
    this->BS = BS;
    return;
}

void Plata::setCantitate(double cantitate)
{
    this->cantitate = cantitate;
    return;
}

void Plata::setPret(double pret)
{
    this->pret = pret;
    return;
}

long long Plata::getId()
{
    return id;
}

Data Plata::getData()
{
    return data;
}

BunuriServicii Plata::getBunServiciu()
{
    return BS;
}

double Plata::getCantitate()
{
    return cantitate;
}

double Plata::getPret()
{
    return pret;
}

void Plata::input(bool _data)
{
    cout << "\nIntroduceti detaliile platii: \n";
    cout << "\n";
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

void Plata::printDetalii()
{
    cout << "\nDetalii plata: \n";
    cout << "ID: ";
    if (data.getZi() < 10)
        cout << "0";
    cout << id << endl;
    data.printDetalii();
    BS.printDetalii();
    cout << "Cantitate: " << cantitate << endl;
    cout << "Pret: " << pret << endl;
    return;
}

void Plata::printDetalii(vector<Plata> plati )
{
    int currentPage = 1;
    int pageSize = PAGE_SIZE;
    if (plati.size() == 0)
        return void(cout << "\nNu exista informatii de afisat.\n");

    int totalPages = (plati.size() + pageSize - 1) / pageSize;

    while (true)
    {
        system("cls");

        int startIndex = (currentPage - 1) * pageSize;
        int endIndex = min(startIndex + pageSize, static_cast<int>(plati.size()));

        cout << "\n\n";
        long long sNoSpace = max(5LL, (long long)log10(plati.size())), idSpace = 6, dataSpace = 5, numeBSSpace = 18, tipBSSpace = 10, rataBSSpace = 4, cantitateSpace = 8, pretSpace = 6;
        for (int i = startIndex; i < endIndex; i++)
        {
            auto plata = plati[i];
            if (idSpace < to_string(plata.getId()).length())
                idSpace = to_string(plata.getId()).length();
            if (dataSpace < plata.getData().dataToString().length())
                dataSpace = plata.getData().dataToString().length();
            if (numeBSSpace < plata.getBunServiciu().getNume().length())
                numeBSSpace = plata.getBunServiciu().getNume().length();
            if (tipBSSpace < plata.getBunServiciu().getTip().length())
                tipBSSpace = plata.getBunServiciu().getTip().length();
            if (rataBSSpace < to_string(plata.getBunServiciu().getRata()).length())
                rataBSSpace = to_string(plata.getBunServiciu().getRata()).length();
            if (cantitateSpace < to_string(plata.getCantitate()).length())
                cantitateSpace = to_string(plata.getCantitate()).length();
            if (pretSpace < to_string(plata.getPret()).length())
                pretSpace = to_string(plata.getPret()).length();
        }

        long long totalDash = 22 + idSpace + dataSpace + numeBSSpace + tipBSSpace + rataBSSpace + cantitateSpace + pretSpace;
        cout << " ";
        for (long long i = 0; i < totalDash; i++)
            cout << "-";
        cout << "\n"
             << " | "
             << left << setw(idSpace) << "ID";
        cout << " | ";
        cout << left << setw(dataSpace) << "Data";
        cout << " | ";
        cout << left << setw(numeBSSpace) << "Nume bun/serviciu";
        cout << " | ";
        cout << left << setw(tipBSSpace) << "Tip";
        cout << " | ";
        cout << left << setw(rataBSSpace) << "Pret/buc";
        cout << " | ";
        cout << left << setw(cantitateSpace) << "Cantitate";
        cout << " | ";
        cout << left << setw(pretSpace) << "Pret";
        cout << " |\n";
        cout << " ";

        for (long long i = 0; i < totalDash; i++)
            cout << "-";
        cout << "\n";

        for (int i = startIndex; i < endIndex; i++)
        {
            auto plata = plati[i];
            cout << " | ";
            if (plata.getData().getZi() < 10)
                cout << left << setw(idSpace) << (to_string(plata.getId()));
            else
                cout << left << setw(idSpace) << plata.getId();
            cout << " | ";
            cout << left << setw(dataSpace) << plata.getData().dataToString();
            cout << " | ";
            cout << left << setw(numeBSSpace) << plata.getBunServiciu().getNume();
            cout << " | ";
            cout << left << setw(tipBSSpace) << plata.getBunServiciu().getTip();
            cout << " | ";
            cout << left << setw(rataBSSpace) << plata.getBunServiciu().getRata();
            cout << " | ";
            cout << left << setw(cantitateSpace) << plata.getCantitate();
            cout << " | ";
            cout << left << setw(pretSpace) << plata.getPret();
            cout << " |\n";
        }

        cout << " ";
        for (long long i = 0; i < totalDash; i++)
            cout << "-";
        cout << "\n\n";

        cout << "Pag " << currentPage << " / " << totalPages << endl;
        cout << "[N] Inainte | [P] Inapoi | [Q] Iesire" << endl;
        cout << "Dati optiunea: ";

        char choice;
        cin >> choice;

        switch (choice)
        {
        case 'n':
        case 'N':
            if (currentPage < totalPages)
                currentPage++;
            break;
        case 'p':
        case 'P':
            if (currentPage > 1)
                currentPage--;
            break;
        case 'q':
        case 'Q':
            return; // Exit the function
        default:
            cout << "Optiune invalida. Incercati din nou\n";
            break;
        }
    }
}




Plata::~Plata()
{
    //dtor
}
