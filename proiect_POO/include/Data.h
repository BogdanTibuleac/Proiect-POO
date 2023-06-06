#ifndef DATA_H
#define DATA_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Data
{
    public:
        Data();
        Data(long long, long long, long long);
        //setters
        void setZi(long long);
        void setLuna(long long);
        void setAn(long long);
        //getters
        long long getZi();
        long long getLuna();
        long long getAn();
        //alte metode
        void input();
        void printDetalii();
        void stringToData(string);
        string dataToString();
        long long value();
        virtual ~Data();

    protected:

    private:
        long long zi;
        long long luna;
        long long an;
        bool validareData();
};

#endif // DATA_H
