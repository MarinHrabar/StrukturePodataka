#define _CRT_SECURE_NO_WARNINGS

#include "dates.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>           

PositionDate parse_date(const char* str) { // parsira string u date strukturu
    if (!str) return NULL; // provjera ulaznog pokazivaca
    PositionDate d = (PositionDate)malloc(sizeof(date));// alociraj memoriju za date
    if (!d) return NULL;// ako alokacija ne uspije vrati NULL
    int y = 0, m = 0, day = 0;
    if (sscanf(str, "%d-%d-%d", &y, &m, &day) != 3) {// parsiranje stringa YYYY-MM-DD
        free(d); 
        return NULL;// ako nije u ispravnom formatu, oslobodi i vrati NULL
    }
    d->year = y; 
    d->month = m; 
    d->day = day; // postavi polja strukture
    return d;// vrati pokazivaè na date
}

int format_date(const PositionDate d, char* buffer, size_t bufsize) {// formatira date u "YYYY-MM-DD"
    if (!d || !buffer || bufsize < 11) return -1;// provjeri ulaze i velièinu buffera (10+1)
    int n = snprintf(buffer, bufsize, "%04d-%02d-%02d", d->year, d->month, d->day); // formatiranje u buffer
    return (n > 0 && (size_t)n < bufsize) ? 0 : -1; // vrati 0 ako je sve ok, inace -1
}

int compare_dates(const PositionDate d1, const PositionDate d2) {// usporeduje dva datuma
    if (!d1 || !d2) return 0;// ako su NULL vraæamo 0
    if (d1->year != d2->year) return (d1->year < d2->year) ? -1 : 1;
    if (d1->month != d2->month) return (d1->month < d2->month) ? -1 : 1;
    if (d1->day != d2->day) return (d1->day < d2->day) ? -1 : 1;  
    return 0;
}

int date_in_range(const PositionDate d, const PositionDate from, const PositionDate to) { // provjerava pripadnost rasponu
    if (!d || !from || !to) return 0;// provjeri pokazivace
    return (compare_dates(d, from) >= 0 && compare_dates(d, to) <= 0) ? 1 : 0; // vraæa 1 ako d u [from,to]
}

int delete_date(PositionDate d) {// briše dinamèki alociran date (ako postoji)
    if (!d) return -1; // ako je NULL vraæamo -1
    free(d);
    return 0;
}
