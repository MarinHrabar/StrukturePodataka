#pragma once

#ifndef DIR_H
#define DIR_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct dir* Position;
typedef struct dir {
	char name[50];
	Position parent;//pokazivac na roditeljski direktorij
	Position child;//pokazivac na pod-direktorij
	Position next;//pokazuvac na sljedeci direktorij na istom nivou
}dir;

Position createDir(char* name, Position parent);//deklaracija funkcije za kreiranje novog direktorija
Position mkDir(Position curr, char* name);//deklaracija funkcije za stvaranje novog direktorija
Position cd(Position curr, char* name);//deklaracija funkcije za ulazak u pod-direktorij
Position cd_return(Position curr);//deklaracija funkcije za povratak u roditeljski direktorij
Position listDir(Position curr);//deklaracija funkcije za ispis sadrzaja direktorija
Position rd(Position curr, char* name);//deklaracija funkcije za uklanjanje direktorija
Position freeAll(Position root);//deklaracija funkcije za oslobadanje memorije
#endif
