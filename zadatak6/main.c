#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h>  
#include <string.h> 
#include <time.h> 

#include "receipt.h"
#include "items.h"
#include "dates.h"

#define MAX_WORKERS 50

// ucitavanje radnika iz datoteke radnici.txt, vraca broj procitanih ili -1 na gresku
int load_workers(char workers[][50], int max_workers) {
    if (!workers || max_workers <= 0) return -1;
    FILE* f = fopen("radnici.txt", "r");
    if (!f) return -1;
    int count = 0;// brojac radnika
    while (count < max_workers && fscanf(f, "%49s", workers[count]) == 1) { 
        count++; 
    }
    fclose(f);
    return count;
}

PositionReceipt create_receipt_manual(const char* operator_name) {
    PositionReceipt inv = (PositionReceipt)malloc(sizeof(receipt));
    if (!inv) return NULL;
    inv->items = NULL;
    inv->next = NULL;

    // postavi trenutni datum
    time_t t = time(NULL);
    struct tm tm = *localtime(&t); // lokalno vrijeme u struct tm
    inv->date.year = tm.tm_year + 1900;// postavi godinu
    inv->date.month = tm.tm_mon + 1;// postavi mjesec
    inv->date.day = tm.tm_mday;// postavi dan

    printf("Unesite artikle (unesite 'end' za kraj):\n");
    while (1) {
        char name[50]; int qty = 0; float price = 0.0f; 
        printf("Naziv artikla: ");                                
        if (scanf("%49s", name) != 1) break;                  
        if (strcmp(name, "end") == 0) break;// izlazni trik (unesi end)
        printf("Kolicina: "); scanf("%d", &qty);// uèitaj kolièinu
        printf("Cijena: "); scanf("%f", &price); // uèitaj cijenu
        PositionItem a = newitem(name, qty, price);// kreiraj artikal
        if (!a) continue;// ako ne uspije, preskok
        inv->items = AddAndSort(inv->items, a);// dodaj u listu artikala
    }
    return inv;// vrati kreirani racun
}

int main(void) {
    char workers[MAX_WORKERS][50];
    int n_workers = load_workers(workers, MAX_WORKERS);
    if (n_workers < 0) {
        printf("Nije moguce otvoriti 'radnici.txt', nastavljamo bez popisa radnika.\n");
        n_workers = 0;
    }

    PositionReceipt receipt = load_all_receipts("racuni.txt");
    if (!receipt) {
        printf("Nema dodanih racuna u racuni.txt.\n");
    }
    else {
        printf("Racuni su se uspjesno ucitali.\n");
    }


    while (1) {
        printf("\n=== MENU ===\n");
        printf("1) Ispis racuna \n");
        printf("2) Spojite dva racuna (po datumu) \n");
        printf("3) Stornirajte racun (po datumu) \n");
        printf("4) Stvorite racun \n");
        printf("5) Izlaz i oslobadanje memorije \n");
        printf("izaberite opciju: ");
        int opt;
        if (scanf("%d", &opt) != 1)
            break;
        if (opt == 1) {
            if (!receipt) {
                printf("Nema dostupnih racuna.\n");
                continue;
            }
            PositionReceipt curr = receipt;
            while (curr) {
                print_receipt(curr, "Cafe Bar Cakula", (n_workers > 0 ? workers[0] : "Unknown"));
                printf("\n\n");
                curr = curr->next;
            }
        }
        else if (opt == 2) {
            if (!receipt || !receipt->next) { printf("Potrebno je minimalno dva racuna za spajanje.\n"); continue; }

            PositionReceipt merged = merge_receipts(receipt, receipt->next);
            if (merged) {
                print_receipt(merged, "Cafe Bar Cakula", "Merged");
                delete_receipts(merged);// ocisti spojeni raèun nakon ispisa
            }
            else printf("Neuspjeh pri spajanju racuna.\n");
        }
        else if (opt == 3) {
            char ds[16]; printf("Odaberite datum racuna kojeg zelite stornirati (YYYY-MM-DD): ");
            if (scanf("%15s", ds) != 1) continue;
            PositionDate d = parse_date(ds);
            if (!d) { printf("Neispravan format.\n"); continue; }
            receipt = cancel_receipt(receipt, d);
            delete_date(d); // oslobodi privremeni datum
            printf("Cancel operation attempted.\n");
        }
        else if (opt == 4) {
            if (n_workers == 0) {
                printf("Nema ucitanih radnika, unesite ime operatera: "); char tmp[50]; scanf("%49s", tmp); PositionReceipt inv = create_receipt_manual(tmp); if (inv) {
                    print_receipt(inv, "Cafe Bar Cakula", tmp);
                    delete_receipts(inv);
                }
            }
            else {
                printf("Odaberite operatera:\n");
                for (int i = 0; i < n_workers; ++i) printf("%d) %s\n", i + 1, workers[i]);
                int sel;
                scanf("%d", &sel);
                if (sel < 1 || sel > n_workers) { printf("Bad selection.\n"); continue; }
                PositionReceipt inv = create_receipt_manual(workers[sel - 1]);
                if (inv) {
                    print_receipt(inv, "Cafe Bar Cakula", workers[sel - 1]);
                    delete_receipts(inv);
                }
            }
        }
        else if (opt == 5) {
            break;
        }
        else {
            printf("Error.\n");
        }
    }

    // ciscenje prije izlaza
    if (receipt) delete_receipts(receipt);
    printf("Exiting program. Memory cleaned.\n");
    return 0;
}