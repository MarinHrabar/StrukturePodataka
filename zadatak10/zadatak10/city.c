#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "city.h"


TreePos createNode(char cityname[], int population) {//za stvaranje cvora
    TreePos newCity = (TreePos)malloc(sizeof(city));
    if (!newCity) {//alokacija
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }

    strcpy(newCity->cityname, cityname);
    newCity->population = population;
    newCity->left = NULL;
    newCity->right = NULL;

    return newCity;
}

TreePos insertCity(TreePos root, char cityname[], int population) {
    if (root == NULL) {
        root = createNode(cityname, population);
        return root;
    }

    if (population > root->population) {//ukoliko je populacija grada kojeg ubacujemo veca od populacije roota idemo desno
        root->right = insertCity(root->right, cityname, population);
    }
    else {
        root->left = insertCity(root->left, cityname, population);
    }

    return root;
}


int printCityTree(TreePos root) {
    if (root == NULL) return 0;

    printCityTree(root->left);//lijevo dijete
    printf("    %s (%d)\n", root->cityname, root->population);//ispis trenutnog cvora
    printCityTree(root->right);//desno dijete

    return 0;
}


TreePos SearchTree(TreePos root, int popul) {
    if (!root) return NULL;

    
    SearchTree(root->left, popul); //lijevo dijete

    
    if (root->population > popul)//trenutni cvor
        printf("    %s (%d)\n", root->cityname, root->population);

  
    SearchTree(root->right, popul);//desno dijete

    return root;
}


int freeCityTree(TreePos root) {
    if (root == NULL) return 0;

    freeCityTree(root->left);
    freeCityTree(root->right);

    free(root);
    return 0;
}
