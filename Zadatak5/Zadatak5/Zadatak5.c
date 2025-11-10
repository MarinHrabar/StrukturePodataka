#define _CRT_SECURE_NO_WARNINGS        
#include <stdio.h>                     
#include <stdlib.h>                    
#include <string.h>                    
#include <ctype.h>                     

struct num;                            

typedef struct num* Position;           

typedef struct num {
    double element;                    
    Position next;// Pokazivaè na sljedeæi element u listi
} num;


int push(Position p, double a);// Deklaracija funkcije koja dodaje element u stog
double pop(Position p);// Deklaracija funkcije koja uklanja element iz stoga
int print(Position p);// Deklaracija funkcije koja ispisuje stog
double evaluatePostfix(const char* filename);// Deklaracija funkcije za izraèunavanje izraza iz datoteke

int main() {
    double result = evaluatePostfix("postfix.txt");
    printf("Result is: %.2lf\n", result);// Ispisuje konacni rezultat
    return 0;                                         
}


int push(Position p, double a) {
    Position q = (Position)malloc(sizeof(num));// Dinamicki alocira novi cvor
    if (q == NULL) {// Provjera je li alokacija uspjela
        printf("\nMemory allocation error!\n");
        return -1;
    }
    q->element = a;// Postavlja vrijednost novog cvora
    q->next = p->next;// Novi cvor pokazuje na dosadasnji vrh stoga
    p->next = q;// Novi cvor postaje novi vrh stoga
    return 0;                                         
}

double pop(Position p) {
    Position temp = p->next;                          
    if (temp == NULL) {// Ako je stog prazan
        printf("\nError: Stack is empty.\n");
        return 0;                                     
    }
    double a = temp->element;// Sprema vrijednost s vrha
    p->next = temp->next;// Uklanja cvor iz liste tako sto ga preskace
    free(temp); // Oslobadanje memorije
    return a;// Vraca uklonjenu vrijednost
}

int print(Position p) {
    Position temp = p->next; // Krece od pocetka liste te prolazi kroz svaki cvor
    while (temp != NULL) {                            
        printf("%.2lf ", temp->element);              
        temp = temp->next;                            
    }
    printf("\n");                                     
    return 0;
}

double evaluatePostfix(const char* filename) {
    FILE* fp = fopen(filename, "r");                  
    if (fp == NULL) {// Provjera je li datoteka uspjesno otvorena
        printf("Error opening file!\n");
        return 0;
    }

    num head;                                         
    head.next = NULL;                                

    char buffer[1024];// Privremeni string za citanje broja/operatora

    
    while (fscanf(fp, "%s", buffer) == 1) {//cita jedan po jedan token

        // Ako token pocinje znamenkom ili negativnim brojem
        if (isdigit(buffer[0]) || (buffer[0] == '-' && isdigit(buffer[1]))) {
            push(&head, atof(buffer));// Pretvara string u double i dodaje u stog
        }
        else {
            double a = pop(&head);
            double b = pop(&head);
            double result = 0;

            // Izvršava odgovarajuæu matematièku operaciju
            switch (buffer[0]) {
            case '+':
                result = b + a; break;
            case '-': 
                result = b - a; break;
            case '*': 
                result = b * a; break;
            case '/':
                if (a == 0) {// Provjera dijeljenja nulom
                    printf("\nAttempting to divide by zero.\n");
                    fclose(fp);
                    return 0;
                }
                result = b / a;
                break;
            default:// Ako naide nepoznat operator
                printf("\nUnkown operator: %s\n", buffer);
                fclose(fp);
                return 0;
            }

            push(&head, result);//Vraca rezultat u stog
        }
    }

    fclose(fp);

    double finalResult = pop(&head);// Na kraju, jedini element u stogu je rezultat
    return finalResult;// Vraca konacan rezultat izraza
}
