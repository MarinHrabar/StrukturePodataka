#define _CRT_SECURE_NO_WARNINGS
#include "receipt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <time.h>

static PositionReceipt create_receipt_empty(void) {
    PositionReceipt inv = (PositionReceipt)malloc(sizeof(receipt));
    if (!inv) return NULL;
    inv->items = NULL;
    inv->next = NULL;
    inv->date.year = 0; 
    inv->date.month = 0; 
    inv->date.day = 0;//inicijalizacija datuma
    return inv; // vraca pokazivac
}

// ucitavanje racuna iz racuni.txt
PositionReceipt load_all_receipts(const char* list_filename) {
    if (!list_filename) return NULL;// provjera ulaza
    FILE* f = fopen(list_filename, "r");
    if (!f) return NULL;

    PositionReceipt head = NULL; 
    char file_name[260];// buffer za ime datoteke
    while (fscanf(f, "%259s", file_name) == 1) {// citanje naziva datoteke iz liste
        FILE* fr = fopen(file_name , "r");// otvori pojedinacnog racuna
        if (!fr) continue;//ako ne otvori, preskok
        char date_str[64];// buffer za datum u datoteci
        if (fscanf(fr, "%63s", date_str) != 1) { fclose(fr);
        continue; }
        PositionDate parsed = parse_date(date_str);// parsiraj datum iz stringa
        if (!parsed) { 
         fclose(fr); 
        continue; }                          
        // ako parse ne uspije, zatvori datoteku i preskoci

        PositionReceipt inv = create_receipt_empty();
        if (!inv) { delete_date(parsed); 
        fclose(fr); 
        continue; }// provjera alokacije

        inv->date = *parsed;// kopiraj datum u strukturu racuna
        delete_date(parsed);// brisanje privremenog datuma

        // citaj artikle u formatu: name quantity price
        char name[50]; int qty = 0; float price = 0.0f;// pomocne varijable za citanje
        while (fscanf(fr, "%49s %d %f", name, &qty, &price) == 3) {//citaj dok odgovara format
            PositionItem a = newitem(name, qty, price);// kreiraj artikal
            if (!a) continue;// ako ne uspije kreiranje, preskoci
            inv->items = AddAndSort(inv->items, a);// dodaj artikal u listu racuna
        }

       
        inv->next = head;// dodaj na pocetak liste
        head = inv;//novi head

        fclose(fr);
    }

    fclose(f);

    // sortiraj raèune po datumu
    head = sort_receipts(head);// sortiraj i vrati novi head
    return head;// vrati listu racuna
}

// sortiranje raèuna po datumu,vraca head sortirane liste
PositionReceipt sort_receipts(PositionReceipt head) {
    PositionReceipt sorted = NULL;// head sortirane liste
    PositionReceipt current = head;
    while (current) {// prolaz kroz sve elemente
        PositionReceipt next = current->next;
        // ubaci current na odgovarajuæe mjesto u sorted listi
        if (!sorted || compare_dates(&current->date, &sorted->date) < 0) {
            current->next = sorted;// umetni na pocetak
            sorted = current; // novi head sortirane liste
        }
        else {
            PositionReceipt s = sorted;
            while (s->next && compare_dates(&current->date, &s->next->date) > 0)
                s = s->next;
            current->next = s->next;// umetanje nakon s
            s->next = current;// povezivanje
        }
        current = next;// prelazak na sljedeæi spremljeni element
    }
    return sorted;
}

// spajanje dva racuna u novi racun 
PositionReceipt merge_receipts(const PositionReceipt i1, const PositionReceipt i2) {
    if (!i1 && !i2) return NULL;// ako nema nijednog raèuna, vrati NULL
    PositionReceipt new_inv = create_receipt_empty();
    if (!new_inv) return NULL;// provjera alokacije

   
    if (i1) new_inv->date = i1->date; else new_inv->date = i2->date;


    new_inv->items = mergeItems(i1 ? i1->items : NULL, i2 ? i2->items : NULL);
    return new_inv;
}

//brise raèun po tocno odreðenom datumu i vraæa novi head liste
PositionReceipt cancel_receipt(PositionReceipt head, const PositionDate d) {
    if (!head || !d) return head; // ako nema head ili datum, vrati ulaz
   
    if (compare_dates(&head->date, d) == 0) {
        PositionReceipt tmp = head->next;
        clear(head->items); // oslobodi artikle
        free(head);// oslobodi racun
        return tmp;// vrati novi head
    }
    PositionReceipt cur = head;                                                   
    while (cur->next) {// prolaz kroz listu
        if (compare_dates(&cur->next->date, d) == 0) {
            PositionReceipt toremove = cur->next;
            cur->next = toremove->next;// preskoci uklonjeni cvor
            clear(toremove->items); // oslobodi artikle uklonjenog raèuna
            free(toremove);// oslobodi sam raèun
            break;
        }
        cur = cur->next;  
    }
    return head;
}
// ispis raèuna 
int print_receipt(const PositionReceipt rec, const char* cafe_name, const char* operator_name) {
    if (!rec) return -1;                                                   
    char datebuf[16];                                                   
    if (format_date(&rec->date, datebuf, sizeof(datebuf)) != 0)// format datuma
        strncpy(datebuf, "0000-00-00", sizeof(datebuf)); 

    // generiraj kod raèuna pomoæu random + time
    srand((unsigned int)time(NULL));                                       
    int code = rand() % 900000 + 100000; 

    printf("=========================================\n");
    printf("Alojzija Stepinca 3, 21220, Trogir\n");
    printf("             %s\n\n", cafe_name);
    printf("WIFI:'CBCAKULA'\n");
    printf("Sifra:87654321\n");
    printf("Operater: %s\n", operator_name);
    printf("Datum: %s\n", datebuf);
    printf("Receipt code: %06d\n", code);
    printf("-----------------------------------------\n");
    printf("Item                  Qty    Price\n");
    printf("-----------------------------------------\n"); 

    PositionItem a = rec->items;// iterator kroz artikle
    float total = 0.0f;// ukupna cijena
    while (a) { // ispis svakog artikla
        printf("%-20s %-6d %.2f\n", a->name, a->amount, a->price); // formatirani ispis
        total += a->amount * a->price;// zbroji u ukupno
        a = a->next;// idi na sljedeæi artikal
    }

    float PDV = 0.25 * total;//racunanje PDVa i osnovice
    float osn = 0.75 * total;

    printf("-----------------------------------------\n");
    printf("TOTAL: %.2f euro\n", total); // ispiši ukupno
    printf("=========================================\n");
    printf("Vrsta poreza:\n");
    printf("PDV:                  osn    PDV\n");
    printf("0.25                 %.2f    %.2f\n", osn, PDV);
    printf("=========================================\n");
    printf("Hvala Vam!\n"); 
    printf("=================QR CODE=================\n\n");

    printf("                #########\n");
    printf("                #  # # ##\n");
    printf("                #### #  #\n");
    printf("                # # ## ##\n");
    printf("                #########\n\n");

    printf("=========================================\n");

    return 0;
}

// oslobaða sve raèune u listi i vraæa 0 ako je bilo što osloboðeno, -1 ako je lista bila NULL
int delete_receipts(PositionReceipt head) {
    if (!head) return -1; 
    PositionReceipt cur = head;
    while (cur) { // prolaz kroz sve raèune
       PositionReceipt tmp = cur;// privremeni pokazivac
        cur = cur->next;// pomak na sljedeci
       clear(tmp->items);// oslobodi artikle
        free(tmp); // oslobodi racun
    }
    return 0;
}
