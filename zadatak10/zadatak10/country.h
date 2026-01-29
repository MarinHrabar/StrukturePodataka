#pragma once
#ifndef COUNTRY_H
#define COUNTRY_H

#include "city.h"

typedef struct country* Position;
typedef struct countryTree* CountryTreePos;
typedef struct country {
    char countryname[50];
    Position next;
    TreePos root;
} country;
typedef struct countryTree {
    char countryname[50];
    Position cityListHead;// pokazuje na listu drzava s njihovim BST gradova
    CountryTreePos left;
    CountryTreePos right;
} countryTree;

Position createCountry(char name[]);
Position insertCountryListSorted(Position head, char name[]);
Position readCountriesFromFile(char* filename);
int printCountryList(Position head);
int searchCountryCities(Position head, char name[], int min);
int freeCountryList(Position head);

CountryTreePos createCountryTreeNode(char name[], Position cityHead);
CountryTreePos insertCountryTree(CountryTreePos root, char name[], Position cityHead);
int printCountryTree(CountryTreePos root);
int freeCountryTree(CountryTreePos root);

#endif
