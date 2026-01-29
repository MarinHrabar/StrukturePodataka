#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city.h"


TreePos createCityNode(char cityname[], int population) {
    TreePos newCity = (TreePos)malloc(sizeof(city)); // alokacija memorije
    if (!newCity) { // provjera uspješnosti alokacije
        printf("Neuspjela alokacija memorije %s\n", cityname);
        return NULL;
    }
    strcpy(newCity->cityname, cityname);// postavi ime grada
    newCity->population = population;// postavi broj stanovnika
    newCity->left = newCity->right = NULL; // inicijalizacija djece na NULL
    return newCity;
}


TreePos insertCity(TreePos root, char cityname[], int population) {
    if (!root)
        return createCityNode(cityname, population); // ako je stablo prazno  kreira se novi root

    
    if (population < root->population || (population == root->population && strcmp(cityname, root->cityname) < 0)) {
        root->left = insertCity(root->left, cityname, population); // ide lijevo
    }
    else {
        root->right = insertCity(root->right, cityname, population); // ide desno
    }

    return root; // vraæamo root da se poveze sa roditeljskim cvorom
}


int printCityTree(TreePos root) {//inorder ispis
    if (!root) return 0;
    printCityTree(root->left);
    printf("    %s (%d)\n", root->cityname, root->population); // ispis trenutnog grada
    printCityTree(root->right);
    return 0;
}


int printCityTreeHigher(TreePos root, int min) {
    if (!root) return 0;
    printCityTreeHigher(root->left, min); //lijevo podstablo
    if (root->population > min)
        printf("    %s (%d)\n", root->cityname, root->population);
    printCityTreeHigher(root->right, min); //desno podstablo
    return 0;
}


int freeCityTree(TreePos root) {//oslobadanje memorije
    if (!root) return 0;
    freeCityTree(root->left);
    freeCityTree(root->right); 
    free(root); 
    return 0;
}
