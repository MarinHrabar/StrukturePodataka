#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct student {
	char ime[20];
	char prezime[20];
	int bodovi;
};

typedef struct student stud;

int brojac(char* naziv) //funkcija za brojanje redova tj. studenata
{
	int br = 0;
	FILE* dat;
	char s[100];

	dat = fopen(naziv, "r");
	if (dat == NULL) {
		printf("\nGreska pri otvaranju datoteke.\n");
		return -1;
	}
	else {
		printf("\nDatoteka je uspjesno otvorena.\n");
	}

	while (fgets(s, sizeof(s), dat) != NULL) {
		br++;
	}
	fclose(dat);
	return br;
}

int ispis(int n, char* naziv)//funkcija za ispis
{
	int i, max=100;
	double relativan_br_bodova;
	stud* lista;
	FILE* dat;

	dat = fopen(naziv, "r");
	if (dat == NULL) {
		printf("\nGreska pri otvaranju datoteke.\n");
		return -1;
	}
	else {
		printf("\nDatoteka je uspjesno otvorena.\n");
	}

	

	lista = (stud*)malloc(n * sizeof(stud)); //dinamiиka alokacija

	for (i = 0; i < n; i++) {
		fscanf(dat, "%s %s %d", lista[i].ime, lista[i].prezime, &lista[i].bodovi);
		relativan_br_bodova = (double)lista[i].bodovi / max * 100;
		printf("\n%s\t%s\t%d\t%3f\n", lista[i].ime, lista[i].prezime, lista[i].bodovi, relativan_br_bodova);
	}
	fclose(dat);
	free(lista);
	return 0;

}

int main() {
	char* naziv = "popis.txt";
	int red = brojac(naziv);

	ispis(red, naziv);

}
