#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <thread>
#include <chrono>
using namespace std;

#include "GestionareCheltuieli.h"
#include "Data.h"
#include "BunuriServicii.h"
#include "Plata.h"

#define wait(x) this_thread::sleep_for(chrono::milliseconds(x))

map<long long, Plata> GestionareCheltuieli::plati = map<long long, Plata>();
map<long long, string> GestionareCheltuieli::tipuriBS = map<long long, string>();


GestionareCheltuieli::GestionareCheltuieli()
{
    //ctor
}

void GestionareCheltuieli::adaugaPlata(Plata plata)
{
    long long cnt = 0;
    for(auto P: plati)
    {
        if(P.second.getData().value() == plata.getData().value())
            cnt++;
        else if(P.second.getData().value() > plata.getData().value())
            break;
    }
    plata.setId(plata.getData().value() * 1000 + cnt);
    plati[plata.getId()] = plata;
    cout<<"\nPlata adaugata!\n";
    cout<<"Id-ul este: "<<plata.getId()<<endl;
    return;
}

void GestionareCheltuieli::stergePlata(Plata plata)
{
    Data data = plata.getData();
    long long id = plata.getId();
    plati.erase(plata.getId());
    cout<<"Plata cu ID-ul "<<plata.getId()<<" a fost stearsa!\n";

    long long cnt = 0;
    for(auto P: plati)
    {
        if (P.second.getData().value() == data.value() && P.second.getId() > id)
            cnt++;
        else if (P.second.getData().value() > data.value())
            break;
    }
    for(long long i = 0; i < cnt; i++)
        plati[i+id] = plati[i+id+1], plati[i+id].setId(i+id);
    plati.erase(cnt+id);
    return;
}

Plata GestionareCheltuieli::getDetaliiPlata()
{
    long long opt;
    cout << "\n\n-------------------------------------------\n\n";
    cout << "Cauta plata dupa: " << endl;
    cout << "[01] - ID" << endl;
    cout << "[02] - Data" << endl;
    cout << "[03] - Tip bun/serviciu" << endl;
    cout << "[04] - Nume bun/serviciu" << endl;
    cout << "[05] - Pret\n"
         << endl;
    cout << "[-1] - Inapoi\n"
         << endl;
    cout << "-------------------------------------------\n\n";
    cout << "Dati optiunea: ";
    cin >> opt;
    while (opt > 5 || (opt < 1 && opt != -1))
    {
        cout << "\nOptiune invalida ";
        cin >> opt;
    }

    cout << "\n-------------------------------------------\n\n";
    if (opt == -1)
        return Plata();
    else if (opt == 1)
    {

        long long idReq;
        cout << "Dati ID: ";
        cin >> idReq;
        if (plati.find(idReq) != plati.end())
        {
            return plati[idReq];
        }
        else
        {
            cout << "\n\Nu s-au gasit plati cu acest ID: " << idReq << endl;
            cout << "\n\nDoriti sa incercati din nou? ((D)a || N(u)): ";
            char opt;
            cin >> opt;
            while (opt != 'D' && opt != 'N')
            {
                cout << "Introduceti o optiune valida: ";
                cin >> opt;
            }
            return (opt == 'D' || opt == 'd') ? getDetaliiPlata() : Plata();
        }
    }
    else if (opt == 2)
    {

        Data dateReq;
        cout << "\nIntroduceti data: ";
        dateReq.input();
        vector<Plata> matchingExpenses;
        for (auto plata : plati)
            if (plata.second.getData().value() == dateReq.value())
                matchingExpenses.push_back(plata.second);
        if (matchingExpenses.size() == 0)
        {
            cout << "\nNu au fost gasite plati din aceasta data " << dateReq.dataToString() << ".\n"
                 << endl;
            cout << "\n\nDoriti sa incercati din nou? ( (D)a || N(u)): ";
            char opt;
            cin >> opt;
            while (opt != 'D' && opt != 'N')
            {
                cout << "Introduceti o optiune valida: ";
                cin >> opt;
            }
            return (opt == 'D' || opt == 'd') ? getDetaliiPlata() : Plata();
        }
        else
        {
            cout << "\n"
                 << matchingExpenses.size() << " plati cu aceasta data:" << dateReq.dataToString() << ".\n"
                 << endl;
            Plata::printDetalii(matchingExpenses);
            char opt = 'D';
            while (opt == 'D')
            {
                cout << "\nIntroduceti ID-ul platii: ";
                long long idReq;
                cin >> idReq;
                for (auto plata : matchingExpenses)
                    if (plata.getId() == idReq)
                        return plata;
                cout << "\nNicio plata din lista de mai sus nu are acest ID: " << idReq << ".\n"
                     << endl;
                cout << "\n\nDoriti sa incercati din nou? ((D)a || N(u)): ";
                char opt;
                cin >> opt;
                while (opt != 'D' && opt != 'N')
                {
                    cout << "Introduceti o optiune valida: ";
                    cin >> opt;
                }
            }
        }
    }
    else if (opt == 3)
    {
        string tipBSReq;
        cout << "\n";
        printTipuriBS();
        //cout << "\n";
        cout << "Introduceti tipul bunului/serviciului (nu ID-ul): ";
        cin >> tipBSReq;
        vector<Plata> matchingExpenses;
        for (auto plata : plati)
            if (plata.second.getBunServiciu().getTip().find(tipBSReq) != string::npos)
                matchingExpenses.push_back(plata.second);
        if (matchingExpenses.size() == 0)
        {
            cout << "\nNu au fost gasite plati cu acest tip " << tipBSReq << ".\n"
                 << endl;
            cout << "\n\nDoriti sa incercati din nou? ((D)a || N(u)): ";
            char opt;
            cin >> opt;
            while (opt != 'D' && opt != 'N')
            {
                cout << "Introduceti o optiune valida: ";
                cin >> opt;
            }
            return (opt == 'D' || opt == 'd') ? getDetaliiPlata() : Plata();
        }
        else
        {
            cout << "\n"
                 << matchingExpenses.size() << " au fost gasite urmatoarele plati cu acest tip: " << tipBSReq << ".\n"
                 << endl;
            Plata P = Plata();
            Plata::printDetalii(matchingExpenses);
            char opt = 'D';
            while (opt == 'D')
            {
                cout << "\nIntroduceti ID-ul platii: ";
                long long idReq;
                cin >> idReq;
                for (auto plata : matchingExpenses)
                    if (plata.getId() == idReq)
                        return plata;
                cout << "\nNicio plata nu are acest ID " << idReq << ".\n"
                     << endl;
                cout << "\n\nDoriti sa incercati din nou? ((D)a || N(u)): ";
                char opt;
                cin >> opt;
                while (opt != 'D' && opt != 'N')
                {
                    cout << "Introduceti o optiune valida: ";
                    cin >> opt;
                }
            }
        }
    }
    else if (opt == 4)
    {
        string numeBSReq;
        cout << "Introduceti numele bunului sau serviciului: ";
        cin >> numeBSReq;
        vector<Plata> matchingExpenses;
        for (auto plata : plati)
            if (plata.second.getBunServiciu().getNume().find(numeBSReq) != string::npos)
            matchingExpenses.push_back(plata.second);
        if (matchingExpenses.size() == 0)
        {
            cout << "\nNu au fost gasite plati cu acest nume " << numeBSReq << ".\n"
                 << endl;
            cout << "\n\nDoriti sa incercati din nou? ((D)a || N(u)): ";
            char opt;
            cin >> opt;
            while (opt != 'D' && opt != 'N')
            {
                cout << "Introduceti o optiune valida: ";
                cin >> opt;
            }
            return (opt == 'D' || opt == 'd') ? getDetaliiPlata() : Plata();
        }
        else
        {
            cout << matchingExpenses.size() << " au fost gasite urmatoarele plati cu acest nume: " << numeBSReq << ".\n"
                 << endl;
            Plata P = Plata();
            Plata::printDetalii(matchingExpenses);
            char opt = 'D';
            while (opt == 'D')
            {
                cout << "\nIntroduceti ID-ul platii: ";
                long long idReq;
                cin >> idReq;
                for (auto plata : matchingExpenses)
                    if (plata.getId() == idReq)
                        return plata;
                cout << "Nicio plata din lista nu are acest ID " << idReq << ".\n"
                     << endl;
                cout << "\n\nDoriti sa incercati din nou? ((D)a || N(u)): ";
                char opt;
                cin >> opt;
                while (opt != 'D' && opt != 'N')
                {
                    cout << "Introduceti o optiune valida: ";
                    cin >> opt;
                }
            }
        }
    }
    else if (opt == 5)
    {
        long long limita_inf, limita_sup;
        cout << "\n\nDati intervalul pretului:\n";
        cout << " Limita inferioara: ";
        cin >> limita_inf;
        cout << " Limita superioara: ";
        cin >> limita_sup;
        if (limita_inf > limita_sup)
            swap(limita_inf, limita_sup);
        vector<Plata> matchingExpenses;
        for (auto Plata : plati)
            if (Plata.second.getPret() >= limita_inf && Plata.second.getPret() <= limita_sup)
                matchingExpenses.push_back(Plata.second);
        if (matchingExpenses.size() == 0)
        {
            cout << "\nNu au fost gasite plati in acest interval: ( " << limita_inf << " , " << limita_sup << ").\n"
                 << endl;
            cout << "\n\nDoriti sa incercati din nou? ((D)a || N(u)): ";
            char opt;
            cin >> opt;
            while (opt != 'D' && opt != 'N')
            {
                cout << "Introduceti o optiune valida: ";
                cin >> opt;
            }
            return (opt == 'D' || opt == 'd') ? getDetaliiPlata() : Plata();
        }
        else
        {
            cout << matchingExpenses.size() << " au fost gasite urmatoarele plati in intervalul: ( " << limita_inf << ", "
                 << limita_sup << ").\n"
                 << endl;
            Plata P = Plata();
            Plata::printDetalii(matchingExpenses);
            char opt = 'D';
            while (opt == 'D')
            {
                cout << "\nIntroduceti ID-ul platii: ";
                long long idReq;
                cin >> idReq;
                for (auto Plata : matchingExpenses)
                    if (Plata.getId() == idReq)
                        return Plata;
                cout << "Nicio plata nu are acest ID " << idReq << ".\n"
                     << endl;
                cout << "\n\nDoriti sa incercati din nou? ((D)a || N(u)): ";
                char opt;
                cin >> opt;
                while (opt != 'D' && opt != 'N')
                {
                    cout << "Introduceti o optiune valida: ";
                    cin >> opt;
                }
            }
        }
    }
    return Plata();
}

void GestionareCheltuieli::calculTotalPlati()
{
    int choice;
    cout<<"Calculeaza totalul platilor intre 2 date.\n";
    Data startDate, endDate;
    cout << "\nIntroduceti data de inceput:\n";
    startDate.input();
    cout << "\nIntroduceti data finala:\n";
    endDate.input();
    //cout << "Calculeaza suma platilor din perioada " << startDate.dataToString() << " - " << endDate.dataToString() << ": " << endl;
    double total = 0;
    for (auto plata : plati)
        if (plata.second.getData().value() >= startDate.value() && plata.second.getData().value() <= endDate.value())
            total += plata.second.getPret();
    cout << "\nSuma totala a platilor din perioada " << startDate.dataToString() << " - " << endDate.dataToString() << " este " << total <<" RON."<< endl;

}

void GestionareCheltuieli::printPlati()
{
    vector<Plata> allPlati;
    for(auto plata : plati)
        allPlati.push_back(plata.second);
    Plata::printDetalii(allPlati);
    return ;
}

void GestionareCheltuieli::adaugaTipBS(string tip)
{
    for(auto tipBS : tipuriBS)
        if(tipBS.second == tip)
            return;
    tipuriBS[tipuriBS.size()] = tip;
    return;
}

void GestionareCheltuieli::stergeTipBS(string tip)
{
    for(long long i=0; i<tipuriBS.size(); i++)
        if(tipuriBS[i] == tip)
        {
            for(long long j=i; j<tipuriBS.size() - 1; j++)
                tipuriBS[j] = tipuriBS[j+1];
            tipuriBS.erase(tipuriBS.size()-1);
            return;
        }
    return;
}

void GestionareCheltuieli::printTipuriBS()
{
    cout << "\nBunuri si servicii existente:\n\n";
    for (auto tipBS : tipuriBS)
        cout << left << setw(log10((int)(tipuriBS.size() > 1) ? tipuriBS.size() - 1 : 1)) << tipBS.first,
             cout << ": " << tipBS.second << endl;
    cout << endl;
    return;
}

string GestionareCheltuieli::getTipBS()
{
    long long id;
    cout << "\nIntroduceti ID-ul bunului sau serviciului: ";
    cin >> id;
    while (id < 0 || id >= tipuriBS.size())
    {
        cout << "ID invalid. Incercati din nou: ";
        cin >> id;
    }
    return tipuriBS[id];
}

void GestionareCheltuieli::readFromCSV()
{
    ifstream file;
    file.open("./data/Plati.csv");
    string line;
    getline(file, line); // sare peste prima linie
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        long long id;
        Data data;
        BunuriServicii BS;
        double cantitate;
        double pret;
        getline(ss, token, ',');
        id = stoll(token);
        getline(ss, token, ',');
        data.stringToData(token);
        getline(ss, token, ',');
        BS.setNume(token);
        getline(ss, token, ',');
        BS.setTip(token);
        getline(ss, token, ',');
        BS.setRata(stod(token));
        getline(ss, token, ',');
        cantitate = stod(token);
        getline(ss, token, ',');
        pret = stod(token);
        plati[id] = Plata(id, data, BS, cantitate, pret);
    }
    file.close();
    file.open("./data/BunuriServicii.csv");
    getline(file, line); // skip first line
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        getline(ss, token, ',');
        tipuriBS[tipuriBS.size()] = token;
    }
    return;
}
void GestionareCheltuieli::writeToCSV()
{
    ofstream file;
    file.open("./data/temp.csv");
    file << "ID,Data,Nume bun/serviciu,Tip bun/serviciu,Rata,Cantitate,Pret\n";
    for (auto plata : plati)
    {
        file << plata.first << ",";
        file << plata.second.getData().dataToString() << ",";
        file << plata.second.getBunServiciu().getNume() << ",";
        file << plata.second.getBunServiciu().getTip() << ",";
        file << plata.second.getBunServiciu().getRata() << ",";
        file << plata.second.getCantitate() << ",";
        file << plata.second.getPret() << "\n";
    }
    file.close();
    remove("./data/Plati.csv");
    rename("./data/temp.csv", "./data/Plati.csv");

    file.open("./data/temp.csv");
    file << "S.No.,Bunuri/Servicii\n";
    for (auto tipBS : tipuriBS)
    {
        file << tipBS.first << ",";
        file << tipBS.second << "\n";
    }
    file.close();
    remove("./data/BunuriServicii.csv");
    rename("./data/temp.csv", "./data/BunuriServicii.csv");

    return;
}

GestionareCheltuieli::~GestionareCheltuieli()
{
    //dtor
}
