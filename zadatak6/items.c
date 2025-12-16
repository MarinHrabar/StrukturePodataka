
#define _CRT_SECURE_NO_WARNINGS
#include "items.h"            
#include <stdlib.h>            
#include <string.h>        
#include <stdio.h> 

PositionItem newitem(const char* name, int amount, float price) { // stvara novi artikal
    PositionItem a = (PositionItem)malloc(sizeof(item));// alociraj memoriju za artikal
    if (!a) return NULL;                                              
    strncpy(a->name, name, sizeof(a->name) - 1);
    a->name[sizeof(a->name) - 1] = '\0'; // null-terminator
    a->amount = amount;// postavi kolicinu
    a->price = price;// postavi cijenu
    a->next = NULL;                                                    
    return a;//pokazivac na novi artikal
}

PositionItem AddAndSort(PositionItem head, PositionItem new_item) {      // dodaj artikal u sortiranu listu
    if (!new_item) return head;// ako nema novog, vrati postojeæi head
    if (!head || strcmp(new_item->name, head->name) < 0) {// ako lista prazna ili ide na poèetak novi postaje head
        new_item->next = head;
        return new_item; // vrati novi head
    }
    PositionItem curr = head;
    while (curr->next && strcmp(new_item->name, curr->next->name) > 0) // trazi mjesto za umetanje
        curr = curr->next; //pomicanje pokazivaca na sljedeci element
    new_item->next = curr->next;
    curr->next = new_item; // povezivanje novog clana u listu
    return head;
}

PositionItem mergeItems(const PositionItem a1, const PositionItem a2) {// spajanje dviju lista u novu
    PositionItem result = NULL;// rezultatna lista
    PositionItem p;
    // kopiraj iz prve liste
    p = a1;                                                              
    while (p) {
        PositionItem copy = newitem(p->name, p->amount, p->price);  // stvaranje kopije cvora
        if (!copy) { clear(result); 
        return NULL;
        }
        result = AddAndSort(result, copy);// dodaj kopiju u sortiranu listu
        p = p->next;//sljedeci cvor
    }
    // kopiraj iz druge liste
    p = a2;                                                              
    while (p) {
        PositionItem copy = newitem(p->name, p->amount, p->price);
        if (!copy) {
            clear(result);
        return NULL; 
        }         
        result = AddAndSort(result, copy);
        p = p->next;//sljedeci cvor
    }
    return result;// vrati spojenu listu
}

int clear(PositionItem head) {// brise listu artikala
    if (!head) return -1;
    PositionItem cur = head;// trenutni pokazivac
    while (cur) {                                                     
        PositionItem tmp = cur;// privremeni pokazivac
        cur = cur->next;// pomak na sljedeci
        free(tmp);// oslobodi trenutni cvor
    }
    return 0;
}
