#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"


HashPosition createHashTable(int size) {
    HashPosition ht = (HashPosition)malloc(sizeof(Table));
    if (!ht) return NULL;

    ht->size = size;
    ht->table = (Position*)malloc(size * sizeof(Position));
    if (!ht->table) return NULL;

    for (int i = 0; i < size; i++)
        ht->table[i] = NULL;

    return ht;
}

int calculateKey(char countryname[], int size) {
    int sum = 0;

    for (int i = 0; i < 5 && countryname[i] != '\0'; i++)
        sum += (int)countryname[i];

    return sum % size;
}
int insertCountryHash(HashPosition ht, Position country) {
    int key = calculateKey(country->countryname, ht->size);
    country->key = key;

    if (!ht->table[key]) {
        ht->table[key] = country;
    }
    else {
        ht->table[key] = insertCountrySorted(ht->table[key], country);
    }

    return 0;
}

Position SearchCountryHash(HashPosition ht, char countryname[]) {
    int key = calculateKey(countryname, ht->size);//pretraga po tablici
    return findCountry(ht->table[key], countryname);
}


int printHashTable(HashPosition ht) {
    for (int i = 0; i < ht->size; i++) {
        Position p = ht->table[i];
        while (p) {//ispis cijele tablice
            printCountry(p);
            p = p->next;
        }
    }
    return 0;
}


int freeHashTable(HashPosition ht) {
    for (int i = 0; i < ht->size; i++)
        freeCountryList(ht->table[i]);

    free(ht->table);//oslobadanje tablice
    free(ht);
    return 0;
}
