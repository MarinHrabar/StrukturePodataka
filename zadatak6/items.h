#pragma once

#ifndef ITEMS_H   
#define ITEMS_H 


typedef struct item* PositionItem;

typedef struct item {
	char name[50];
	int amount;
	float price;
	PositionItem next;
}item;

PositionItem newitem(const char* name, int amount, float price);/*deklaracija funkcije koja kreira novi artikal*/


PositionItem AddAndSort(PositionItem head, PositionItem new_item);/*deklaracija funkcije koja dodaje artikal u sortiranom poretku i vraca novi head */

/* Briše i oslobaða sve èlanke u listi; vraæa 1 ako uspješno */
int clear(PositionItem head);/**/

/* Spoji dvije liste artikala tako da rezultat bude sortirana lista (novi alokati) */
PositionItem mergeItems(const PositionItem a1, const PositionItem a2);

#endif
