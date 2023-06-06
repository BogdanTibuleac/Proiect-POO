#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ios>    //used to get stream size
#include <limits> //used to get numeric limits
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
using namespace std;

#include "Plata.h"
#include "GestionareCheltuieli.h"
#include "Data.h"
#include "BunuriServicii.h"

#ifdef WIN32
#define clrscr() system("cls")
#define pause() system("pause")
#endif
#ifdef __linux__
#define clrscr() system("clear")
#define pause() cout << "Apasa orice tasta pentru a continua...", cin.get()
#endif

void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

int main()
{
    GestionareCheltuieli::readFromCSV();

    int choice = 1;
    int num_options = 9;
    bool done = false;
    string name;

    string options[] = {"  Adauga plata noua\n",
                        "  Cautare plata\n",
                        "  Sterge plata\n",
                        "  Afisare plati\n",
                        "  Calcul total plati\n\n",
                        "  Adauga un nou bun/serviciu\n",
                        "  Afisare bun/serviciu\n",
                        "  Sterge bun/serviciu\n\n",
                        "  IESIRE\n",
                       };

    while (!done)
    {
        clrscr();
        cout<<"______________________________________________________\n\n";
        cout << "               GESTIONARE CHELTUIELI\n";
        cout<<"______________________________________________________\n\n";

        for (int i = 1; i <= num_options; i++)
        {
            if (i == choice)
            {
                setColor(2);
            }
            cout <<" " << i << ". " << options[i-1] << endl;
            setColor(7);
        }
        //cout << "\n Help!\n";
        cout << "\n Foloseste tastele \"up arrow\" \"down arrow\" pentru a naviga intre optiuni.\n";
        cout << " Apasa Enter pentru a intra intr-o optiune.\n\n";

        int input = getch();
        if (input == 224)   // check for arrow keys
        {
            input = getch(); // read the second char of the arrow key input
            if (input == 72)   // up arrow
            {
                choice--;
                if (choice < 1)
                {
                    choice = num_options;
                }
            }
            else if (input == 80)   // down arrow
            {
                choice++;
                if (choice > num_options)
                {
                    choice = 1;
                }
            }
        }
        else if (input == 13)   // Enter key
        {
            switch (choice)
            {
            case 1:
            {
                clrscr();
                Plata plata;
                plata.input(1);
                GestionareCheltuieli::adaugaPlata(plata);
                cout << "\n\nDoriti sa adaugati o noua plata din aceasta zi? ( (D)a || N(u)): ";
                char optiune;
                cin >> optiune;
                while (optiune != 'D' && optiune != 'N')
                {
                    cout << "\nOptiune invalida. Incercati din nou: ";
                    cin >> optiune;
                }
                cout << "\n\n";
                while (optiune == 'D')
                {
                    Data _data = plata.getData();
                    plata.input(0);
                    plata.setData(_data);
                    GestionareCheltuieli::adaugaPlata(plata);
                    cout << "\n\nDoriti sa adaugati o noua plata din aceasta zi? ( (D)a || N(u)): ";
                    cin >> optiune;
                    while (optiune != 'D' && optiune != 'N')
                    {
                        cout << "\nOptiune invalida. Incercati din nou: ";
                        cin >> optiune;
                    }
                    cout << "\n\n";
                }
                break;

            }
            case 2:
            {
                clrscr();
                Plata plata = GestionareCheltuieli::getDetaliiPlata();
                if (plata.getId() != -1)
                    plata.printDetalii();
                break;
            }
            case 3:
            {
                clrscr();
                Plata plata = GestionareCheltuieli::getDetaliiPlata();
                if (plata.getId() != -1)
                    GestionareCheltuieli::stergePlata(plata);
                break;
            }
            case 4:
            {
                GestionareCheltuieli::printPlati();
                break;
            }
            case 5:
            {
                clrscr();
                GestionareCheltuieli::calculTotalPlati();
                break;
            }
            case 6:
            {
                clrscr();
                string tipBS;
                cout << "Introduceti tipul bunului/serviciului: ";
                getline(cin >> ws, tipBS);
                GestionareCheltuieli::adaugaTipBS(tipBS);
                break;
            }
            case 7:
            {
                clrscr();
                GestionareCheltuieli::printTipuriBS();
                break;
            }
            case 8:
            {
                clrscr();
                GestionareCheltuieli::printTipuriBS();
                GestionareCheltuieli::stergeTipBS(GestionareCheltuieli::getTipBS());
                break;
            }
            case 9:
            {
                exit(0);
            }

            default:
                cout<<"Optiune invalida\n";
            }
            pause();

        }
        GestionareCheltuieli::writeToCSV();

    }

    clrscr();
    return 0;
}

