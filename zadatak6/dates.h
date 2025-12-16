#pragma once
#ifndef DATES_H   
#define DATES_H 
#include <stddef.h>

typedef struct date* PositionDate;
typedef struct date { 
    int year;                   
    int month;
    int day;
} date;

PositionDate parse_date(const char* str);    // deklaracija funkcije koja parsira string formata "YYYY-MM-DD" u Date strukturu, vraæa pokazivaè na dinamèki alociranu strukturu

int format_date(const PositionDate d, char* buffer, size_t bufsize); // deklaracija funkcije koja formatira datum

int compare_dates(const PositionDate d1, const PositionDate d2); // deklaracija funkcije koja usporeduje dva datuma


int date_in_range(const PositionDate d, const PositionDate from, const PositionDate to); // deklaracija funkcije koja provjerava rang datuma 

int delete_date(PositionDate d); // deklaracija funkcije koja oslobada Position2

#endif
