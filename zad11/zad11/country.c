#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "country.h"


Position createCountry(char countryname[]) {
    Position newCountry = (Position)malloc(sizeof(country));
    if (!newCountry) {//alokacija memorije
        printf("Greska pri alokaciji memorije(drzaba)\n");
        return NULL;
    }

    strcpy(newCountry->countryname, countryname);
    newCountry->next = NULL;
    newCountry->root = NULL;
    newCountry->key = 0;

    return newCountry;
}

Position insertCountrySorted(Position head, Position newCountry) {
    Position p = head;
    while (p->next != NULL &&
        strcmp(p->next->countryname, newCountry->countryname) < 0) {//pretraga mjesta gdje treba ubaciti novi element
        p = p->next;
    }
    newCountry->next = p->next;
    p->next = newCountry;//ubacivanje

    return head;
}


int printCountry(Position p) {
    if (!p) return 0;

    printf("%s\n", p->countryname);
    printCityTree(p->root); // inorder ispis gradova

    return 0;
}


Position findCountry(Position p, char countryname[]) {
    while (p) {
        if (strcmp(p->countryname, countryname) == 0)//pretraga po listi
            return p;
        p = p->next;
    }
    return NULL;
}
int freeCountryList(Position p) {//oslobadanje memorije
    Position temp;

    while (p) {
        temp = p;
        p = p->next;

        freeCityTree(temp->root); //oslobadanje gradova
        free(temp);//oslobadanje drzava
    }
    return 0;
}
