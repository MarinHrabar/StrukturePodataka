#pragma once

#ifndef RECEIPT_H  
#define RECEIPT_H   
/*Position=item*
Position2=date* 
Position3=receipt* */

#include "dates.h"   
#include "items.h"

typedef struct receipt* PositionReceipt;
typedef struct receipt {
    date date;// datum racuna kao Date struktura
    PositionItem items;// lista artikala na racunu
    PositionReceipt next;// pokazivac na sljedeæi racun u listi
} receipt;

PositionReceipt load_all_receipts(const char* list_filename); // deklaracija funkcije koja ucitava popis naziva datoteka iz "racuni.txt" i vraca head liste racuna 

PositionReceipt sort_receipts(PositionReceipt head); // deklaracija funkcije koja sortira listu racuna po datumu i vraca novi head

PositionReceipt merge_receipts(const PositionReceipt i1, const PositionReceipt i2); // deklaracija funkcije koja spaja dva racuna

PositionReceipt cancel_receipt(PositionReceipt head, const PositionDate d); // deklaracija funkcije koja stornira racun po datumu i vraca novi head liste

int print_receipt(const PositionReceipt inv, const char* cafe_name, const char* operator_name); // deklaracija funkcije koja ispisuje racun


int delete_receipts(PositionReceipt head); // deklaracija funkcije koja oslobada listu racuna

#endif

