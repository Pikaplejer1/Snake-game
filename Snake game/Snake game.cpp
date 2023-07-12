// W¹¿ gra.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

bool koniecGry;
int szerokosc = 20;//mozna w int main zmienic zeby byly inne wymiary mapy
int wysokosc = 20;
int x, y, owocX, owocY, wynik, najwiekszy_wynik, szybkosc = 50, ile_ogonek = 1; // wartosci w kolejnosci Glowka, owoca, wyniku, najwiekszego wyniku, szybkosci, i ile doda sie ogonka co owoc
int ogonX[400], ogonY[400];
int nOgon; //OGON ZJEBANY
int opcje; //1 wersja latwa, 2 wersja trudna, 3 wersja customowa
enum eDirestion { STOP = 0, LEFT, RIGHT, UP, DOWN }; //wyliczenie
eDirestion dir;

void poczatek()
{
    system("cls");
    cout << "#######################################################################" << endl;
    cout << "(klikaj na klawiaturze opcje 1-n aby wybrac odpowiadajaca opcje z menu!" << endl;
    cout << "1. Standardowa gra na podstawowych opcjach" << endl;
    cout << "2. Trudniejsza gra na podstawowych opcjach" << endl;
    cout << "3. Gra na opcjach wlasnych (ustawiane w ustawieniach)" << endl;
    cout << "4. Ustawienia gry" << endl;
    cout << "5. Credits" << endl;
    cout << "6. wyswietl najwiekszy wynik of all time" << endl;
    cout << "!Jakikolwiek inny przycisk bedzie skutkowal wyjsciem z gry!" << endl;
    cout << "#######################################################################" << endl;
    cout << "Wcisnij przycisk by kontynuowac..." << endl;
}

void ustawienia()
{
    do
    {
        system("cls");
        cout << "Bazowe ustawienia sa ustawione na standardowego snake'a" << endl;
        cout << "aktualne ustawienia to:" << endl;
        cout << "szerokosc wynosi: " << szerokosc << " kratek (nie ma wplywu na wynik)" << endl;
        cout << "wysokosc wynosi: " << wysokosc << " kratek (nie ma wplywu na wynik)" << endl;
        cout << "szybkosc wynosi: " << szybkosc << " milisekund -> im mniejsza tym wiecej punktow)" << endl;
        cout << "co kazdy owoc doda ci sie " << ile_ogonek << " ogonkow -> im wiecej tym wiecej punktow" << endl;
        cout << endl;
        cout << "1. Zmien ustawienia/zapisz" << endl;
        cout << "2. Wybierz ustawienia z presetu (pliku)" << endl;
        cout << "3. Wyjscie z ustawien" << endl;
        switch (_getch()) //jeszcze glowniejszy switch ktory sie pyta czy chcesz wybra ustawienia z pliku czy je zmienic/zapisac
        {
        case '1': //zmien ustawienia/zapisz
            cout << "wpisz wymazone ustawienia, po zakonczenu zostaniesz zapytany czy chcesz je zapisac..." << endl;
            cout << "szerokosc: ";
            cin >> szerokosc;
            cout << "wysokosc: ";
            cin >> wysokosc;
            cout << "szybkosc (w milisekundach): ";
            cin >> szybkosc;
            cout << "ile owoc doda ci ogonka: ";
            cin >> ile_ogonek;
            cout << endl;
            cout << "czy chcesz zapisac te ustawienia?" << endl;
            cout << "y/n" << endl;
            switch (_getch()) //glowny switch ktory pokazuje czy chczesz zapisac czy nie
            {
            case 'y': //tu jest ze chcesz zapisywac do pliku
                cout << endl;
                cout << "pod jaki preset chcesz je zapisac?" << endl;
                cout << "dostepne presety: 1., 2., 3.," << endl;
                cout << "!uwaga zapisane w n presecie zastapi ustawienia, zapisane w danym presecie!" << endl;
                cout << "kliknij 1,2 lub 3 na klawiaturze, kazde inne spowoduje brak zapisu" << endl;
                //1. linijka to szerokosc
                //2. linijka to wysokosc
                //3. linijka to szybkosc
                //4. linijka to ile_ogonek
                switch (_getch()) //switch do jakiego pliku chcesz to zapisac I TUTAJ MAM ZROBIC ZAPISYWANIE DO PLIKU
                {
                case '1':
                {
                    fstream preset_1;
                    preset_1.open("preset1.txt", ios::out);
                    if (!preset_1.good()) cout << "Blad z plikiem..." << endl;
                    else
                    {
                        preset_1 << szerokosc << endl;
                        preset_1 << wysokosc << endl;
                        preset_1 << szybkosc << endl;
                        preset_1 << ile_ogonek << endl;
                        cout << "pomyslnie zapisano ustawienia do pliku!" << endl;
                        cout << "kliknij dowolny przycisk by kontynuowac!" << endl;
                    }
                    break;
                }
                case '2':
                {
                    fstream preset_2;
                    preset_2.open("preset2.txt", ios::out);
                    if (!preset_2.good()) cout << "Blad z plikiem..." << endl;
                    else
                    {
                        preset_2 << szerokosc << endl;
                        preset_2 << wysokosc << endl;
                        preset_2 << szybkosc << endl;
                        preset_2 << ile_ogonek << endl;
                        cout << "pomyslnie zapisano ustawienia do pliku!" << endl;
                        cout << "kliknij dowolny przycisk by kontynuowac!" << endl;
                    }
                    break;
                }
                case '3':
                {
                    fstream preset_3;
                    preset_3.open("preset1.txt", ios::out);
                    if (!preset_3.good()) cout << "Blad z plikiem..." << endl;
                    else
                    {
                        preset_3 << szerokosc << endl;
                        preset_3 << wysokosc << endl;
                        preset_3 << szybkosc << endl;
                        preset_3 << ile_ogonek << endl;
                        cout << "pomyslnie zapisano ustawienia do pliku!" << endl;
                        cout << "kliknij dowolny przycisk by kontynuowac!" << endl;
                    }
                    break;
                }
                default:
                    cout << "zla opcja zostala wybrana nie zapisje ustawien do pliku..." << endl;
                    Sleep(2000);
                    break;
                }
                break; //break to Y

            case 'n': //tu jest ze nie chce zapisywac do pliku
                cout << "ustawienia pomyslnie zapisane, tym samym nie zapisujac ich do pliku!" << endl;
                cout << "kliknij dowolny przycisk by kontynuowac!" << endl;
                break;
            default: //tu ze jestes debilem i nie potrafisz sluchac polecen
                break;
            }
            break; //break do 1
        case '2':
            cout << "Wybrales opcje wyboru z pliku, na poczatek przygotowalem 3 presety," << endl << "ktore sa ciekawym urozmaiceniem do stnadardowego snake'a ;)" << endl;
            cout << "ktory preset chcesz wybrac? (jak sie rozmysliles/as, kliknij dowolny INNY przycisk" << endl;
            cout << "1., 2. czy 3.?" << endl;
            //1. linijka to szerokosc
            //2. linijka to wysokosc
            //3. linijka to szybkosc
            //4. linijka to ile_ogonek
            switch (_getch()) //TUTAJ MAM ZROBIC ODCZYTYWANIE Z PLIKU
            {
            case '1':
            {
                ifstream preset1("preset1.txt");
                preset1 >> szerokosc >> wysokosc >> szybkosc >> ile_ogonek;
                cout << "Pomyslnie udalo sie wczytac ustawienia z pliku!" << endl;
                cout << "Kliknij dodolny przycisk aby kontynuowac..." << endl;
                break;
            }
            case '2':
            {
                ifstream preset2("preset2.txt");
                preset2 >> szerokosc >> wysokosc >> szybkosc >> ile_ogonek;
                cout << "Pomyslnie udalo sie wczytac ustawienia z pliku!" << endl;
                cout << "Kliknij dodolny przycisk aby kontynuowac..." << endl;
                break;
            }
            case '3':
            {
                ifstream preset3("preset3.txt");
                preset3 >> szerokosc >> wysokosc >> szybkosc >> ile_ogonek;
                cout << "Pomyslnie udalo sie wczytac ustawienia z pliku!" << endl;
                cout << "Kliknij dodolny przycisk aby kontynuowac..." << endl;
                break;
            }
            default: //wyjscie
                cout << "Wychodze do menu..." << endl;
                break;
            }
            break; //break do '2'
        case '3':
            cout << "Wychodze do menu glownego!" << endl;
            Sleep(1500);
            return;
            break; //break do '3'
        default:
            break; //break do default
        }
    } while (_getch() != 3);
}

void credits()
{
    system("cls");
    cout << "program stworzony przez: Marcel Pendyk 3H4..." << endl;
    cout << "i uzytkownika strony stackoverflow pod nickiem: Charleh" << endl << endl;
    cout << "nacisnij dowolny przycisk aby wyjsc do menu!" << endl;
    _getch();
}

void pobierz_wynik()
{
    ifstream wynik_plik("najlepszy_wynik.txt");
    wynik_plik >> najwiekszy_wynik;
    wynik_plik.close();
}

void zapisz_wynik()
{
    fstream wynik_plik;
    wynik_plik.open("najlepszy_wynik.txt", ios::out);
    wynik_plik << wynik;
    wynik_plik.close();
}

void wyswietl_wynik()
{
    /*
    FILE* wyswietlanie;
    //wyswietlanie.open("najlepszy_wynik.txt",ios::in);
    wyswietlanie=fopen("najlepszy_wynik.txt","r");
        char z;
        cout<<"najlepszy wynik (all time) to: ";
        while(z!=EOF)
        {
            z=fgetc(wyswietlanie);
            cout<<z;
        }
        cout<<endl;
    system("pause");
    fclose(wyswietlanie);
    */
    pobierz_wynik();
    system("cls");
    cout << "Najwiekszy wynik all time to: " << najwiekszy_wynik << endl << endl;;
    cout << "kliknij dowolny przycisk aby powrocic do menu glownego!" << endl;
    _getch();
}

void uruchomienie()
{
    koniecGry = false;
    dir = STOP;
    x = szerokosc / 2;
    y = wysokosc / 2;
    owocX = rand() % szerokosc;
    owocY = rand() % wysokosc;
    wynik = 0;
}

void wybiez_opcje()
{
    if (opcje == 1)
    {
        szerokosc = 20;
        wysokosc = 20;
        szybkosc = 50;
        ile_ogonek = 1;
    }
    if (opcje == 2)
    {
        szerokosc = 17;
        wysokosc = 17;
        szybkosc = 20;
        ile_ogonek = 2;
    }
    if (opcje == 3)
    {
        cout << "opcje wczytane z pliku" << endl;
    }
}

void rysowanie()
{
    system("cls");
    for (int i = 0; i < szerokosc + 2; i++)
        cout << "#";
    cout << endl;
    for (int i = 0; i < wysokosc; i++)
    {
        for (int j = 0; j < szerokosc; j++)
        {
            if (j == 0) cout << "#";
            if (i == y && j == x) cout << "O";
            else if (i == owocY && j == owocX) cout << "*"; // jak cos sie spierdoli to pewnie tutaj
            else
            {
                bool ogonek = false;
                for (int k = 0; k < nOgon; k++) //PIERDOL SIE JEBANY OGONIE
                {
                    if (ogonX[k] == j && ogonY[k] == i)
                    {
                        cout << "o";
                        ogonek = true;
                    }
                }
                if (!ogonek) cout << " ";
            }
            if (j == szerokosc - 1) cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < szerokosc + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Wynik: " << wynik; // tutaj nie zapomnij dodac se innych tekstow, np. licznik KOMBO
}
// w
//asd
void klik() // albo tutaj
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'p':
            koniecGry = true; //emergency stop dla testowania byl potrzebny, moze sie przydac jeszcze wiec nie usuwam i nic o nim nie pisalem
            break;
        }
    }
}
/* w gore to y sie zmniejsza w gol sie zwieksza
w lewo x sie zmniejsza w prawo x sie zwieksza
 1 2 3 4 5 6 7 8 9
1
2
3        O
4      O O O
5
*/
void logika()
{
    int wczesniejszyX = ogonX[0];
    int wczesniejszyY = ogonY[0];
    int wczesniejszyX2, wczesniejszyY2;
    ogonX[0] = x;
    ogonY[0] = y;
    for (int i = 1; i < nOgon; i++)
    {
        wczesniejszyX2 = ogonX[i];
        wczesniejszyY2 = ogonY[i];
        ogonX[i] = wczesniejszyX;
        ogonY[i] = wczesniejszyY;
        wczesniejszyX = wczesniejszyX2;
        wczesniejszyY = wczesniejszyY2;
    } // ten caly algorytm jest zjebany ogolnie robi tak ze zamienia wczesniejszy ogon na poprzedni i poprzedni za do glowki
    switch (dir)
    {
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    }
    if (x > szerokosc - 1 || x < 0)
        koniecGry = true;
    if (y > wysokosc - 1 || y < 0)
        koniecGry = true;
    for (int i = 0; i < nOgon; i++)
    {
        if (ogonX[i] == x && ogonY[i] == y)
            koniecGry = true;
    }
    if (x == owocX && y == owocY)
    {
        wynik += (((150 - szybkosc) / 5 + ile_ogonek) + 1) / 2; //komenda na liczenie wyniku
        owocX = rand() % szerokosc;
        owocY = rand() % wysokosc;
        nOgon += ile_ogonek; //tutaj zmiany ile ogonow za jeden owoc
    }
}
//nw gdzie to dodac konkretnie ALE chce zrobic menu gdzie beda rozne opcja, najwazniejsza to bede chcial z rysowaniem
//i zapisywaniem opcji do pliku, ze w pliku beda opcje, ktore mozna wczytac i tez beda presety co bedze kox
int main()
{
    do
    {
        poczatek();
        switch (_getch())
        {
        case '1':
            opcje = 1;
            break;
        case '2':
            opcje = 2;
            break;
        case '3':
            opcje = 3;
            break;
        case '4':
            ustawienia();
            break;
        case '5':
            credits();
            break;
        case '6':
            wyswietl_wynik();
            break;
        default:
            cout << "See you next time!" << endl;
            Sleep(1000);
            return(0);
            break;
        }
    } while (opcje != 1 && opcje != 2 && opcje != 3);
    Sleep(100);
    uruchomienie(); //ustawianie wartosci domyslnych gry
    wybiez_opcje();
    while (!koniecGry)
    {
        rysowanie(); //rysowanie calej planszy ogonka owocow itp.
        klik(); //przechwytywanie klikniecia klawiatury
        logika(); //cala logika ktora idzie za ta gra
        Sleep(szybkosc); //predkasc ustawiana przez gracza w ustawieniach
    }
    pobierz_wynik();
    cout << endl;
    cout << "Koniec gry" << endl;
    cout << "twoj wynik to: ";
    cout << wynik << endl;
    if (wynik > najwiekszy_wynik)
    {
        cout << "Gratulujemy! Wlasnie ustanowiles nowy najwyzszy rekord!" << endl;
        cout << "Zdobyles o " << wynik - najwiekszy_wynik << " punktow wiecej!" << endl;
        zapisz_wynik();
    }
    else if (wynik == najwiekszy_wynik) cout << "Pomimo ze nie udalo ci sie pobic najwyzszego wyniku udalo ci sie jemu dorownac Graulujemy!" << endl;
    else cout << "Niestety nie udalo ci sie pokonac naszego najlepszego gracza :(, zabraklo tobie: " << najwiekszy_wynik - wynik << " punktow!" << endl;
    cout << "Nby wyjsc kliknij dowolny przycisk..." << endl;
    _getch();
}
//3 glowne funkcje
//1. rysowanie
//2. pobieranie klawiatury
//3. wykonywanie algorytmow
//Rysowanie:
//wypisz kratke i dla kazdego pola jednego sprawdza czy jest tam owocek, glowka czy ogonek
//jesli tak jest to go wypisuje
// 1 2 3 4
//1# # # #
//2# *   #
//3#   O #
//4# # # #
//dla 1-4 jest kratka bo to ramka
// dla 2-2  zostal znaleziony owocek wiec go wypisuje if(i==owocY && y==owocekX) cout<<"*";
// dla 3-3 jest pole z glowka -> i==y && j==x
//pobieranie klawiatury:
//sprawdz czy klawiatura jest kliknieta -> jak tak to pobierz klawisz, jezeli jest on ze zbioru "w, s, a, d"
//i ustaw mu dana wartosc up down left right; ew. emergency stop
//wykonywanie algorytmow/logika:
//algorytm ogonka
//przesuniecie x,y jako glowki w zaleznosci od dir
//sprawdzenie czy glowka jest w kratce lub w ogonku
//stworzenie nowych koordynatow owocka i dodanie do wyniku "x" punktu (jezeli zebrany ) -> wypisanie w kategorii "rysowanie"
//main:
//jak !koniecGry wykonuja sie te 3 glowne opcje


