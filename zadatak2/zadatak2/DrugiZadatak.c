#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_length 30//definiram max duljinu stringova za ime i prezime

struct student;

typedef struct student* Position;//definiram Position kao pokaziva� na strukturu student

typedef struct student {
	char name[max_length];
	char surname[max_length];
	int year;
	Position next;//pokaziva� na sljede�i element u listi
}Student;

Position createStudent(char*, char*, int);//deklaracija funkcije koja stvara novog studenta s podatcima, a vra�a pokaziva� na novog studenta
void printList(Position);//deklaracija funkcije koja ispisuje listu
void inputTop(Position, Position);//deklaracija funkcije koja dodaje novog studenta na po�etak liste
void inputBottom(Position, Position);//deklaracija funkcije koja dodaje novog studenta na kraj liste 
Position searchSurname(Position, char*);//deklaracija funkcije koja omogu�ava pretra�ivanje po prezimenu, vra�a pokaziva� na odre�enog studenta
void freeList(Position);//deklaracija funkcije za osloba�anje memorije

int main() {
	Student head;
	Position p = NULL; //koristi se za privremeno dr�anje pokaziva�a na novog ili prona�enog studenta
	char name[max_length] = { 0 }, surname[max_length] = { 0 };
	int year = 0;
	head.next = NULL;
	int selection = 0;

	printf("\nSelect an action.\n");//korisnik bira radnju tako �to unosi ponu�enu vrijednost, program odabire radnju na osnovu korisnikova inputa koriste�i switch case petlju
	printf("\nTo add a student to the top of the list, enter '1'\nTo add a student to the end of the list, enter '2'\nTo print the list, enter '3'\nTo search by surname, enter '4'\nTo end the program, enter '0'\n");
	while (1) {//beskona�na while petlja koja se vrti sve dok korisnik ne odabere '0'
		scanf("%d", &selection);

		switch (selection) {

		case 0: 
			freeList(&head);//za osloba�anje memorije kad se program zavr�i
			return 0;
		case 1:
			printf("\nEnter name:\t ");
			scanf("%29s", name);

			printf("\nEnter surname:\t ");
			scanf("%29s", surname);

			printf("\nEnter the year of birth:\t ");
			scanf("%d", &year);

			printf("\n");
			p = createStudent(name, surname, year);
			inputTop(&head, p);
			break;
		case 2:
			printf("\nEnter name:\t ");
			scanf("%29s", name);

			printf("\nEnter surname:\t ");
			scanf("%29s", surname);

			printf("\nEnter the year of birth:\t ");
			scanf("%d", &year);

			printf("\n");
			p = createStudent(name, surname, year);
			inputBottom(&head, p);
			break;
		case 3:
			printList(&head); 
			break;
		case 4:
			printf("Enter the surname of the student you are looking for:\t ");
			scanf("%29s", surname);
			p = searchSurname(&head, surname);

			if (p != NULL)
				printf("\nStudent:\t %s %s %d\n", p->name, p->surname, p->year);

			break;
		
		default:
			printf("Enter valid selection!\n");
			break;
		}
	}
	return 0;
}
Position createStudent(char* name, char* surname, int year) {

	Position p = NULL;

	p = (Position)malloc(sizeof(Student));//dinami�ka alokacija memorije

	if (NULL == p) {
		printf("\nMemory allocation error\n");//provjera je li dinami�ko alociranje memorije uspjelo
		return NULL;
	}

	strcpy(p->name, name);//kopira ime u polje strukture
	strcpy(p->surname, surname);//kopira prezime u polje strukture
	p->year = year;
	p->next = NULL;//student jo� nije dodan u listu pa postavljam next pokaziva� u NULL

	return p;//vra�a pokaziva� na novokreiranog studenta
}
void inputTop(Position head, Position p) {
	p->next = head->next;// Novog studenta povezujemo tako da pokazuje na prvi stvarni �vor (ako postoji)
	head->next = p;  // Head pokazuje na novog studenta, student je na vrhu liste
	
}
void inputBottom(Position head, Position p) {  
	Position temp = head;                       // Privremeni pokaziva� 
	while (temp->next != NULL)                  // Petlja ide dok ne do�e do zadnjeg �vora (�iji next pokazuje na NULL)
		temp = temp->next;                      // Pomicanje pokaziva�a na sljede�i �vor
	temp->next = p;                             // Zadnji �vor sada pokazuje na novog studenta
	p->next = NULL;                             // Novi student je sada zadnji �vor, next pokazuje na NULL
}

void printList(Position head) {
	Position p = NULL;
	printf("\nList:\n");
	for (p = head->next; p != NULL; p = p->next)//petlja prolazi kroz sve �vorove liste 
		printf("%s %s %d\n", p->name, p->surname, p->year);
}
Position searchSurname(Position head, char* surname) {
	Position p = head->next; // po�inje od prvog stvarnog �vora
	while (p != NULL && strcmp(surname, p->surname) != 0)// Dok p nije NULL i prezime se ne poklapa, ide na sljede�i �vor                                
		p = p->next; // Pomicanje pokaziva�a na sljede�i �vor
		
	if (p == NULL) {
		printf("Student with that surname doesn't exist.\n");//Ukoliko do�e do kraja liste bez pronalaska, funkcija printa poruku da student ne postoji i vra�a nulu.
		return NULL;
	}
	return p;
}
void freeList(Position head) {
	Position temp;
	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
}
