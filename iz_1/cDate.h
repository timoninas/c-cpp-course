#ifndef UNTITLED_CDATE_H
#define UNTITLED_CDATE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Date cDate;

struct Date {
    uint day;
    uint month;
    uint year;
};

cDate* sort(cDate* dates, const int number_of_elements, const int buffer_size);
cDate* fill_cDate(cDate *date, uint day, uint month, uint year);
cDate* grow(cDate *dates, int number_of_elements, int *buffer_size);
cDate* add_date(cDate* dates, cDate date, int *number_of_elements, int *buffer_size);
int check_valid_date(cDate date);
int greater_date(cDate day1, cDate day2);
void swipeDate(cDate *day1, cDate *day2);
void printDate(cDate date);

#endif //UNTITLED_CDATE_H
