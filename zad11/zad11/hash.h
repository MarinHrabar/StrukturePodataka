#pragma once
#ifndef HASH_H
#define HASH_H

#include "country.h"

typedef struct hashTable* HashPosition;
typedef struct hashTable {
    int size;
    Position* table;
} Table;


HashPosition createHashTable(int size);//funkcija za stvaranje hash tablice
int calculateKey(char countryname[], int size);//funkcija za racunanje kljuceva za tablicu
int insertCountryHash(HashPosition hash, Position country);//dodavanje u tablicu
Position SearchCountryHash(HashPosition hash, char countryname[]);//pretraga po tablici
int printHashTable(HashPosition hash);//ispis hash tablice
int freeHashTable(HashPosition hash);//oslobadanje tablice

#endif
