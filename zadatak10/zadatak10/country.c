#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "country.h"
#include "city.h"

Position createCountry(char name[]) {//stvaranje drzave
    Position newCountry = (Position)malloc(sizeof(country));
    if (!newCountry) { printf("Memory allocation failed for country!\n"); 
    return NULL;
    }
    strcpy(newCountry->countryname, name);
    newCountry->next = NULL;
    newCountry->root = NULL;
    return newCountry;
}

Position insertCountryListSorted(Position head, char name[]) {
    Position newCountry = createCountry(name);//dodavanje drzave u listu
    if (!newCountry) return head;

    if (!head || strcmp(newCountry->countryname, head->countryname) < 0) {
        newCountry->next = head;
        return newCountry;
    }

    Position p = head;
    while (p->next != NULL && strcmp(newCountry->countryname, p->next->countryname) >= 0)
        p = p->next;

    newCountry->next = p->next;
    p->next = newCountry;

    return head;
}

Position readCountriesFromFile(char* filename) {//iscitavanje drzava iz filea
    FILE* fp = fopen(filename, "r");
    if (!fp) { printf("Nije moguce otvoriti file %s\n", filename); 
    return NULL; }

    char buffer[1024];
    Position head = NULL;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        char* countryName = strtok(buffer, ",");
        if (!countryName) continue;
        head = insertCountryListSorted(head, countryName);
    }

    fclose(fp);
    return head;
}

int printCountryList(Position head) {
    Position p = head;//ispis liste drzava
    while (p != NULL) {
        printf("%s\n", p->countryname);
        printCityTree(p->root);
        p = p->next;
    }
    return 0;
}

int searchCountryCities(Position head, char name[], int min) {
    Position p = head;
    while (p != NULL) {
        if (strcmp(p->countryname, name) == 0) {
            printf("Country: %s\n", p->countryname);
            SearchTree(p->root, min);
            return 0;//pretraga po stablu gradova
        }
        p = p->next;
    }
    printf("Country %s not found.\n", name);
    return -1;
}

int freeCountryList(Position head) {
    Position temp;//oslobadanje memorije
    while (head != NULL) {
        temp = head;
        head = head->next;
        freeCityTree(temp->root);
        free(temp);
    }
    return 0;
}


CountryTreePos createCountryTreeNode(char name[], Position cityHead) {//za stvaranje cvora za stabla drzava
    CountryTreePos newNode = (CountryTreePos)malloc(sizeof(countryTree));
    if (!newNode) return NULL;
    strcpy(newNode->countryname, name);
    newNode->cityListHead = cityHead;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

CountryTreePos insertCountryTree(CountryTreePos root, char name[], Position cityHead) {
    if (!root) return createCountryTreeNode(name, cityHead);
    if (strcmp(name, root->countryname) < 0)
        root->left = insertCountryTree(root->left, name, cityHead);
    else
        root->right = insertCountryTree(root->right, name, cityHead);
    return root;
}

int printCountryTree(CountryTreePos root) {// Pronalazak drzave po imenu u listi
    if (!root) return 0;
    printCountryTree(root->left);
    printf("%s\n", root->countryname);
    Position p = root->cityListHead;
    while (p != NULL) {
        printCityTree(p->root);
        p = p->next;
    }
    printCountryTree(root->right);
    return 0;
}

int freeCountryTree(CountryTreePos root) {// Oslobadanje memorije liste drzava i njihovih BST gradova
    if (!root) return 0;
    freeCountryTree(root->left);
    freeCountryTree(root->right);

    Position p = root->cityListHead;
    while (p != NULL) {
        Position temp = p;
        p = p->next;
        freeCityTree(temp->root);
        free(temp);
    }
    free(root);
    return 0;
}
