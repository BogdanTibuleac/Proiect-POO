#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
using namespace std;

#define wait(x) this_thread::sleep_for(chrono::milliseconds(x))

Data::Data()
{
    zi = -1;
    luna = -1;
    an = -1;
}

Data::Data(long long zi, long long luna, long long an)
{
    this->zi = zi;
    this->luna = luna;
    this->an = an;
}

void Data::setZi(long long zi)
{
    this->zi = zi;
    return;
}

void Data::setLuna(long long luna)
{
    this->luna = luna;
    return;
}

void Data::setAn(long long an)
{
    this->an = an;
    return;
}

long long Data::getZi()
{
    return zi;
}

long long Data::getLuna()
{
    return luna;
}

long long Data::getAn()
{
    return an;
}

bool Data::validareData()
{
    if(zi <1 || zi > 31)
        return false;
    if(luna < 1 || luna > 12)
        return false;
    if (an < 0)
        return false;
    if(luna == 2)
    {
        if(zi > 29)
            return false;
        if(zi == 29)
            if(an%4 != 0)
            return false;
    }
    if(luna == 4 || luna == 6 || luna == 9 || luna == 11)
        if(zi > 30)
        return false;
    return true;
}

void Data::input()
{
    cout<<endl;
    cout << "Introduceti data (ZZ/LL/AAAA):\n";
    cout << "\tZi   - (ZZ)  : ", cin >> zi;
    cout << "\tLuna - (LL)  : ", cin >> luna;
    cout << "\tAn   - (AAAA): ", cin >> an;
    cout << "\n";
    while(!validareData())
    {
        cout << "\nData invalida!\n";
        this->input();
    }
    return;
}

void Data::printDetalii()
{
    cout << "Data: " << zi << "/" << luna << "/" << an << endl;
    return;
}

void Data::stringToData(string data)
{
    stringstream ss(data);
    string token;
    getline(ss, token, '/');
    zi = stoll(token);
    getline(ss, token, '/');
    luna = stoll(token);
    getline(ss, token, '/');
    an = stoll(token);
    return;
}

string Data::dataToString()
{
    stringstream ss;
    if (zi < 10)
        ss << "0";
    ss << zi << "/";
    if (luna < 10)
        ss << "0";
    ss << luna << "/";
    if (an < 10)
        ss << "000";
    else if (an < 100)
        ss << "00";
    else if (an < 1000)
        ss << "0";
    ss << an;
    return ss.str();
}

long long Data::value()
{
    return an * 10000 + luna * 100 + zi;
}

Data::~Data()
{
    //dtor
}
