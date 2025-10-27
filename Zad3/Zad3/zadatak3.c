#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_length 30//definiram max duljinu stringova za ime i prezime

struct student;

typedef struct student* Position;//definiram Position kao pokazivac na strukturu student

typedef struct student {
	char name[max_length];
	char surname[max_length];
	int year;
	Position next;//pokazivac na sljedeci element u listi
}Student;

Position createStudent(char*, char*, int);//deklaracija funkcije koja stvara novog studenta s podatcima, a vra?a pokazivac na novog studenta
void printList(Position);//deklaracija funkcije koja ispisuje listu
void inputTop(Position, Position);//deklaracija funkcije koja dodaje novog studenta na pocetak liste
void inputBottom(Position, Position);//deklaracija funkcije koja dodaje novog studenta na kraj liste 
Position searchSurname(Position, char*);//deklaracija funkcije koja omogucava pretraživanje po prezimenu, vraca pokazivac na odredenog studenta
void freeList(Position);//deklaracija funkcije za oslobadanje memorije
Position findPrevious(Position, char*);//deklaracija funkcije koja vraca prethodni element prema prezimenu
void deleteStudent(Position, char*);//deklaracija funkcije koja brise odredenog studenta
void insertBefore(Position, char*);//deklaracija funkcije koja dodaje novog studenta ispred odredenog
void insertAfter(Position, char*);//deklaracija funkcije koja dodaje novog studenta iza odreðenog
void saveToFile(Position);//deklaracija funkcije koja zapisuje listu u datoteku
void loadFromFile(Position);//deklaracija funkcije koja cita listu iz datoteke
void sortList(Position);//deklaracija funkcije koja sortira listu po prezimenima
void toUpperString(char*);//deklaracija funkcije koja pretvori u velika slova za usporedbu stringova

int main() {
	Student head;
	Position p = NULL; //koristi se za privremeno držanje pokazivaca na novog ili pronadenog studenta
	char name[max_length] = { 0 }, surname[max_length] = { 0 };
	int year = 0;
	head.next = NULL;
	int selection = 0;

	printf("\nSelect an action.\n");//korisnik bira radnju tako što unosi ponudenu vrijednost, program odabire radnju na osnovu korisnikova inputa koristeci switch case petlju
	printf("\nTo add a student to the top of the list, enter '1'\nTo add a student to the end of the list, enter '2'\nTo print the list, enter '3'\nTo search by surname, enter '4'\n");
	printf("To delete a student, enter '5'\nTo insert before a student, enter '6'\nTo insert after a student, enter '7'\nTo save the list to file, enter '8'\nTo load the list from file, enter '9'\nTo sort the list alphabetically by surname, enter '10'\nTo end the program, enter '0'\n");

	while (1) {//beskonacna while petlja koja se vrti sve dok korisnik ne odabere '0'
		scanf("%d", &selection);

		switch (selection) {

		case 0:
			freeList(&head);//za oslobadanje memorije kad se program završi
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
		case 5:
			printf("Enter surname of the student you want to delete:\t ");
			scanf("%29s", surname);
			deleteStudent(&head, surname);
			break;

		case 6:
			printf("Enter surname of the student before whom you want to add a new one:\t ");
			scanf("%29s", surname);
			insertBefore(&head, surname);
			break;

		case 7:
			printf("Enter surname of the student after whom you want to add a new one:\t ");
			scanf("%29s", surname);
			insertAfter(&head, surname);
			break;

		case 8:
			saveToFile(&head);
			break;

		case 9:
			loadFromFile(&head);
			printList(&head);
			break;

		case 10:
			printf("List sorted by surname:\n");
			sortList(&head);
			printList(&head);
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

	p = (Position)malloc(sizeof(Student));//dinamicka alokacija memorije

	if (NULL == p) {
		printf("\nMemory allocation error\n");//provjera je li dinamicko alociranje memorije uspjelo
		return NULL;
	}

	strcpy(p->name, name);//kopira ime u polje strukture
	strcpy(p->surname, surname);//kopira prezime u polje strukture
	p->year = year;
	p->next = NULL;//student još nije dodan u listu pa postavljam next pokazivac u NULL

	return p;//vraca pokazivac na novokreiranog studenta
}
void inputTop(Position head, Position p) {
	p->next = head->next;// Novog studenta povezujemo tako da pokazuje na prvi stvarni cvor (ako postoji)
	head->next = p;  // Head pokazuje na novog studenta, student je na vrhu liste

}
void inputBottom(Position head, Position p) {
	Position temp = head;// Privremeni pokazivac 
	while (temp->next != NULL) // Petlja ide dok ne dode do zadnjeg cvora (ciji next pokazuje na NULL)
		temp = temp->next; // Pomicanje pokazivaca na sljedeci cvor
	temp->next = p;// Zadnji cvor sada pokazuje na novog studenta
	p->next = NULL;// Novi student je sada zadnji cvor, next pokazuje na NULL
}

void printList(Position head) {
	Position p = NULL;
	printf("\nList:\n");
	for (p = head->next; p != NULL; p = p->next)//petlja prolazi kroz sve cvorove liste 
		printf("%s %s %d\n", p->name, p->surname, p->year);
}
void toUpperString(char* str) {//funkcija koja omoguæava da se pri trazenju studenata mozemo rabiti velikim i malim slovima
	for (int i = 0; str[i]; i++) {
		str[i] = toupper(str[i]);
	}
}

Position searchSurname(Position head, char* surname) {
	Position p = head->next;// pocinjemo od prvog stvarnog èvora (nakon head)
	char tempSurname[max_length];
	strcpy(tempSurname, surname);// kopiramo korisnièki unos u privremeni string
	toUpperString(tempSurname); // pretvori u velika slova za usporedbu

	while (p != NULL) {
		char nodeSurname[max_length];
		strcpy(nodeSurname, p->surname);// kopiramo prezime trenutnog cvora
		toUpperString(nodeSurname); // isto u velika slova
		if (strcmp(tempSurname, nodeSurname) == 0)
			return p;// vracamo pokazivac na pronaðenog studenta


		p = p->next;// idemo na sljedeæi cvor
	}

	printf("Student with that surname doesn't exist.\n");
	return NULL;
}

Position findPrevious(Position head, char* surname) {
	Position prev = head;
	Position curr = head->next; // trenutni cvor poèinje od prvog stvarnog cvora

	char tempSurname[max_length];
	strcpy(tempSurname, surname); 
	toUpperString(tempSurname);  

	while (curr != NULL) {
		char nodeSurname[max_length];
		strcpy(nodeSurname, curr->surname); // kopiramo prezime trenutnog cvora
		toUpperString(nodeSurname);

		if (strcmp(nodeSurname, tempSurname) == 0) // provjeravamo podudaranje
			return prev; // vraæamo prethodni cvor (za brisanje ili umetanje ispred)

		prev = curr;// pomicemo prethodni cvor
		curr = curr->next; // pomicemo trenutni cvor
	}

	printf("Student not found.\n");
	return NULL;
}


// Briše odreðenog studenta iz liste
void deleteStudent(Position head, char* surname) {
	Position prev = findPrevious(head, surname);
	if (prev == NULL) return;

	Position temp = prev->next;
	prev->next = temp->next;
	free(temp);
	printf("Student deleted successfully.\n");
}

// Dodaje novog studenta ispred odreðenog prezimena
void insertBefore(Position head, char* surname) {
	Position prev = findPrevious(head, surname);
	if (prev == NULL) return;

	char name[max_length], newSurname[max_length];
	int year;

	printf("Enter name: ");
	scanf("%29s", name);
	printf("Enter surname: ");
	scanf("%29s", newSurname);
	printf("Enter year of birth: ");
	scanf("%d", &year);

	Position newNode = createStudent(name, newSurname, year);
	newNode->next = prev->next;// novi pokazuje na trazenog
	prev->next = newNode;// prethodni pokazuje na novog
}


// Dodaje novog studenta iza odreðenog prezimena
void insertAfter(Position head, char* surname) {
	Position curr = searchSurname(head, surname);
	if (curr == NULL) return;

	char name[max_length], newSurname[max_length];
	int year;

	printf("Enter name: ");
	scanf("%29s", name);
	printf("Enter surname: ");
	scanf("%29s", newSurname);
	printf("Enter year of birth: ");
	scanf("%d", &year);

	Position newNode = createStudent(name, newSurname, year);
	newNode->next = curr->next;
	curr->next = newNode;
}


// Sprema listu u datoteku
void saveToFile(Position head) {
	FILE* f = fopen("list.txt", "w");//otvaramo datoteku za pisanje
	if (f == NULL) {//provjera je li datoteka uspjesno otvorena
		printf("Error opening file!\n");
		return;
	}
	Position p = head->next;
	while (p != NULL) {//pocinjemo od prvog i prolazimo kroz sve cvorove liste
		fprintf(f, "%s %s %d\n", p->name, p->surname, p->year);
		p = p->next;
	}
	fclose(f);
	printf("List saved to file.\n");
}

// Ucitava listu iz datoteke
void loadFromFile(Position head) {
	FILE* f = fopen("list.txt", "r");//otvaramo datoteku za citanje
	if (f == NULL) {//provjera
		printf("Error opening file!\n");
		return;
	}

	char name[max_length], surname[max_length];//privremeni stringovi za citanje
	int year;
	Position newNode;

	while (fscanf(f, "%29s %29s %d", name, surname, &year) == 3) {
		newNode = createStudent(name, surname, year);
		inputBottom(head, newNode);//stvaramo novog studenta i dodajemo ga na kraj liste
	}

	fclose(f);
	printf("List loaded from file.\n");
}

// Sortira listu po prezimenima (bubble sort)
void sortList(Position head) {
	Position end = NULL;
	Position prev, curr, temp;

	while (head->next != end) {
		prev = head;
		curr = head->next;

		while (curr->next != end) {
			char currSurname[max_length];
			char nextSurname[max_length];

			strcpy(currSurname, curr->surname);// Kopiramo prezimena i pretvaramo u velika slova za usporedbu
			strcpy(nextSurname, curr->next->surname);
			toUpperString(currSurname);
			toUpperString(nextSurname);

			
			if (strcmp(currSurname, nextSurname) > 0) {// Ako curr prezime > next prezime, zamjena cvorova
				temp = curr->next;
				prev->next = temp;
				curr->next = temp->next;
				temp->next = curr;
				curr = temp;
			}
			prev = curr;
			curr = curr->next;
		}
		end = curr;
	}
}

void freeList(Position head) {
	Position temp;
	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
}