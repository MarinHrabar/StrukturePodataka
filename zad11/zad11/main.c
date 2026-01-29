#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "country.h"
#include "city.h"
#include "hash.h"

int main() {
    char countriesFile[] = "drzave.txt";

    Position head = NULL;
    FILE* fp = fopen(countriesFile, "r");//ucitavanje drzava u listu
    if (!fp) return 1;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = 0;
        char* countryName = strtok(buffer, ",");
        char* cityFile = strtok(NULL, ",");
        if (!countryName || !cityFile) continue;

        Position newCountry = createCountry(countryName);

        FILE* fCity = fopen(cityFile, "r");
        if (!fCity) continue;

        char line[256];
        while (fgets(line, sizeof(line), fCity)) {
            line[strcspn(line, "\n")] = 0;
            char* cityName = strtok(line, ",");
            int pop = atoi(strtok(NULL, ","));
            newCountry->root = insertCity(newCountry->root, cityName, pop);//ucitavanje gradova u listu
        }
        fclose(fCity);

        
        newCountry->next = head;
        head = newCountry;
    }
    fclose(fp);

  
    HashPosition Table = createHashTable(11);
    Position curr = head;
    while (curr != NULL) {
        Position temp = createCountry(curr->countryname);//kreiranje tablice
        temp->root = curr->root;
        insertCountryHash(Table, temp);
        curr = curr->next;
    }

    int option;
    do {
        printf("\n1. Ispisi hash tablicu\n2. Pretrazi drzavu\n3. Exit\nOdabir: ");
        scanf("%d", &option);

        switch (option) {
        case 1:
            printHashTable(Table);
            break;
        case 2: {
            char search[50];
            printf("Unesi ime drzave: ");
            scanf("%s", search);
            Position c = SearchCountryHash(Table, search);
            if (c) printCityTree(c->root);
            else printf("Drzava nije pronadena!\n");
            break;
        }
        case 3:
            break;
        default:
            printf("Invalid option\n");
        }
    } while (option != 3);

    freeHashTable(Table);//oslobadanje memorije

    return 0;
}
