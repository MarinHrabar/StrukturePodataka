#pragma once
#ifndef COUNTRY_H
#define COUNTRY_H

#include "city.h"

typedef struct country* Position;


typedef struct country {//struktura za drzave
    char countryname[50];
    int key;//kljuc za hash

    Position next;
    TreePos root;
} country;


Position createCountry(char countryname[]);//stvaranje drzave
Position insertCountrySorted(Position head, Position newCountry);//dodavanje drzave
int printCountry(Position p);//ispis
Position findCountry(Position p, char countryname[]);//pretraga
int freeCountryList(Position p);//oslobadanje liste

#endif
