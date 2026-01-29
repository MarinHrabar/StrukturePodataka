#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "country.h"
#include "city.h"

int loadCitiesIntoRoot(Position country, char* cityFile) {//funkcija za ucitavanje gradova u binarno stablo te drzave
    FILE* fp = fopen(cityFile, "r");
    if (!fp) {//otvaranje filea
        printf("Nije moguce otvoriti %s za drzavu %s\n", cityFile, country->countryname);
        return -1;
    }

    char buffer[256];
    char cityName[50];
    int population;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;//uklanjanje \n iz buffera
        if (sscanf(buffer, "%49[^,],%d", cityName, &population) == 2)//parsiranje u formatu (ime grada, populacija)
        {
            country->root = insertCity(country->root, cityName, population);
        }
    }

    fclose(fp);
    return 0;
}

int main() {
    char countriesFile[]="drzave.txt";
   
    //sortirana lista po nazivu
    Position head = readCountriesFromFile(countriesFile);
    if (!head) return 1;
    //ucitavanje gradova svake drzave
    FILE* fp = fopen(countriesFile, "r");
    if (!fp) return 1;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        char* countryName = strtok(buffer, ",");//parsiranje (drzava,datoteka.txt)
        char* cityFile = strtok(NULL, ",");
        if (!countryName || !cityFile) continue;

        Position curr = head;
        while (curr != NULL && strcmp(curr->countryname, countryName) != 0)
            curr = curr->next;
        if (curr != NULL)
            loadCitiesIntoRoot(curr, cityFile);
    }
    fclose(fp);

    
    CountryTreePos countryRoot = NULL;//stabla drzava
    Position curr = head;
    while (curr != NULL) {
        Position singleCountry = createCountry(curr->countryname); // kreiraj novu drzavu
        singleCountry->root = curr->root; // kopiraj samo BST gradova
        countryRoot = insertCountryTree(countryRoot, singleCountry->countryname, singleCountry);
        curr = curr->next;
    }

    int option = 0;
    do {
        
        printf("1. Ispisi drzave i gradove: (lista)\n");
        printf("2. Ispisi drzave i gradove (stablo)\n");
        printf("3. Pretrazi gradove neke drzave po populciji\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
        case 1:
            printCountryList(head);
            break;

        case 2:
            printCountryTree(countryRoot);
            break;

        case 3: {
            char searchCountry[50];
            int minPop;
            printf("Unesite ime drzave: ");
            scanf("%s", searchCountry);
            printf("Unesite minimalnu populaciju: ");
            scanf("%d", &minPop);
            searchCountryCities(head, searchCountry, minPop);
            break;
        }

        case 4:
            printf("Exiting program...\n");
            break;

        default:
            printf("Pokusajte ponovno.\n");
        }
    } while (option != 4);

    freeCountryTree(countryRoot); //oslobodi i stablo i gradove
    return 0;
}
