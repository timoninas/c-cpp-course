#ifndef UNTITLED_CDATE_H
#define UNTITLED_CDATE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct date date_t;

struct date {
    uint day;
    uint month;
    uint year;
};

date_t* sort(date_t* dates, const int number_of_elements, const int buffer_size);
date_t* fill_date(date_t *date, uint day, uint month, uint year);
date_t* grow(date_t *dates, int number_of_elements, int *buffer_size);
date_t* add_date(date_t* dates, date_t date, int *number_of_elements, int *buffer_size);
int check_valid_date(date_t date);

int greater_date(date_t day1, date_t day2);
void swipe_date(date_t *day1, date_t *day2);
void print_date(date_t date);


#endif //UNTITLED_CDATE_H
