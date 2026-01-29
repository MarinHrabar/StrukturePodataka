#pragma once
#ifndef CITY_H
#define CITY_H

typedef struct city* TreePos;

typedef struct city {
    char cityname[50];
    int population;
    TreePos left;
    TreePos right;
} city;


TreePos createNode(char cityname[], int population);
TreePos insertCity(TreePos root, char cityname[], int population);
int printCityTree(TreePos root);
TreePos SearchTree(TreePos root, int popul);
int freeCityTree(TreePos root);

#endif
