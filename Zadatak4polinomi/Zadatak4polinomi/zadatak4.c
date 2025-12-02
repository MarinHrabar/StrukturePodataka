#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct polynomial; 
typedef struct polynomial* Position;

typedef struct polynomial {
	int coefficient;
	int exponent;
	Position next;
}poly;

int sort(int, int, Position);//deklaracija funkcije koja dodaje polinom silazno sortiran po velicini
int loadFromFile(char*, Position, Position); // ucitava polinome iz filea u liste
int add(Position, Position, Position);//deklaracija funkcije za zbrajanje
int multiplication(Position, Position, Position);//deklaracija funkcije za mnozenje
int print(Position);//deklaracija funkcije za ispis

int main() {
	poly pHead;
	pHead.next = NULL; //postavljanje headova prvog i drugog polinoma, njihove sume te njihovog umnoska
	poly qHead; 
	qHead.next = NULL; 
	poly sumHead; 
	sumHead.next = NULL; 
	poly prodHead; 
	prodHead.next = NULL;

	loadFromFile("input.txt", &pHead, &qHead);//ucitavanje polinoma iz datoteke
	add(&pHead, &qHead, &sumHead);//zbrajanje polinoma
	multiplication(&pHead, &qHead, &prodHead);//mnozenje polinoma

	
    printf("Polinom p(x)= ");//ispisi polinoma, njihove sume i produkta
    print(&pHead);

    printf("Polinom q(x)= ");
    print(&qHead);

    printf("Zbroj r(x)= ");
    print(&sumHead);

    printf("Umnozak s(x)= ");
    print(&prodHead);

    return 0;
}


int sort(int coef, int exp, Position head) {// funkcija za dodavanje clana u listu silazno po eksponentu
    Position new = (Position)malloc(sizeof(poly));//alokacija memorije
    if (!new) {
        printf("Greska pri alokaciji memorije!\n");//provjera je li alokacija uspjesna
        return -1;
    }

    new->coefficient = coef;//postavljanje koeficijenta i eksponenta
    new->exponent = exp;
    new->next = NULL;

    Position p = head;
    while (p->next != NULL && p->next->exponent > exp)//umetanje eksponenta na odgovarajuce mjesto 
        p = p->next;

   
    if (p->next != NULL && p->next->exponent == exp) {//ukoliko postoji clan polinoma sa istom potencijom, koeficijenti ta dva clana se zbrajaju
        p->next->coefficient += coef;
        free(new);//oslobadanje new cvora
        return 0;
    }

    new->next = p->next;
    p->next = new;//umetanje novog cvora u listu
    return 0;
}


int loadFromFile(char* path, Position p1, Position p2) {//funkcija za ucitavanje dva polinoma iz datoteke
    FILE* f = fopen(path, "r");//otvaranje datoteke
    if (!f) {//provjera
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    int c, e;
    char ch;


    while (fscanf(f, "%d %d", &c, &e) == 2) {
        sort(c, e, p1);// dodavanje clana u listu p1
        ch = fgetc(f);// provjera iduceg znaka
        if (ch == '\n' || ch == EOF)//kada dodemo do kraja polinoma izlazimo iz petlje i krecemo sa dodavanjem clanova u listu p2
            break;
    }


    while (fscanf(f, "%d %d", &c, &e) == 2) {
        sort(c, e, p2);
        ch = fgetc(f);
        if (ch == EOF)//kraj datoteke
            break;
    }

    fclose(f);
    return 0;
}


int add(Position p1, Position p2, Position s) {//funkcija za zbrajanje dva polinoma
    p1 = p1->next;
    p2 = p2->next;

    while (p1 != NULL) {//dodajemo sve clanove oba polinoma te ukoliko se dogodi da clan iz prvog i clan iz drugog polinoma imaju jednak eksponent, njihovi koeficijenti ce se u funkciji sort zbrojiti
        sort(p1->coefficient, p1->exponent, s);
        p1 = p1->next;
    }

    while (p2 != NULL) {
        sort(p2->coefficient, p2->exponent, s);
        p2 = p2->next;
    }

    return 0;
}


int multiplication(Position p1, Position p2, Position res) {//funkcija za mnozenje dva polinoma
    p1 = p1->next;
    Position start = p2->next;//pocetak drugog polinoma

    while (p1 != NULL) {
        Position p2_curr = start;
        while (p2_curr != NULL) {//mnozenje koeficijenata te zbrajanje eksponenata
            sort(p1->coefficient * p2_curr->coefficient, p1->exponent + p2_curr->exponent, res);
            p2_curr = p2_curr->next;
        }
        p1 = p1->next;
    }

    return 0;
}


int print(Position head) {//funkcija za ispis polinoma
    Position p = head->next;
    if (!p) {
        printf("0\n");//ako je lista prazna, onda je polinom 0
        return 0;
    }

    while (p != NULL) {
        printf("%dx^%d", p->coefficient, p->exponent);
        if (p->next != NULL)
            printf(" + ");// '+'izmedu clanova
        p = p->next;
    }
    printf("\n");
    return 0;
}
