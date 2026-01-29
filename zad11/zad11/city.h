#pragma once
#ifndef CITY_H
#define CITY_H

typedef struct city* TreePos;

typedef struct city {//struktura za gradove
    char cityname[50];
    int population;
    TreePos left;
    TreePos right;
} city;

TreePos createCityNode(char cityname[], int population);//za novi cvor
TreePos insertCity(TreePos root, char cityname[], int population);//ubacivanje gradova
int printCityTree(TreePos root);//ispis stabla gradova
int printCityTreeHigher(TreePos root, int min);//ispis gradova sa vecom populacijom od min
int freeCityTree(TreePos root);//oslobadanje memorije

#endif

