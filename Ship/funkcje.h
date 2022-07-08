#ifndef _FUNKCJE_H
#define _FUNKCJE_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// zdefiniowac typ wyliczeniowy: kierunki ruchu : UP RIGHT DOWN LEFT  (wartosci kolejne)
typedef enum{ UP, RIGHT, DOWN, LEFT } ruch;

int move(int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot);
/* pTab - tablica okreslajaca glebokosc w kazdym kwadracie
   nRow, nCol - rozmia pTab,
   nDepth - minimalna glebokosc aby statek przeplynal
   move - kierunek ruchu
   x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
   px, py - nowe wspolrzedne
   pRoot - tablica pamietajaca ruchy o rozm nRow, nCol
*/

int root(int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest);
// rekurencyja
/* pTab tabl glebokosci   o romiarze nRow  i nCol
    dDepth - glebokosc zanurzenia ststku
    x, y - wspol skad robimy kolejny ruch
    pRoot tablica kolejnych ruchow
    x_dest, y_dest - wsporzedne portu
*/

void clearRoot(int** pRoot, int nRow, int nCol);
// zeruje obie tablice 

int setTab(char* sFile, int** pTab, int nRow, int nCol);
// wczytuje dane z pliku
// sFile -  nazwa pliku wejsciowego - parametr main()
// pTab  - tablica glebokosci morza
// nRow, nCol wymiary tej tablicy

#endif