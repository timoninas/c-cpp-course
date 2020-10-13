#include "cDate.h"

cDate* sort(cDate* dates, const int number_of_elements, const int buffer_size) {
    for (int i = 1; i < number_of_elements; i++) {
        for (int j = i; j > 0 && greater_date(dates[j-1], dates[j]); j--) {
            cDate tmp = dates[j - 1];
            dates[j - 1] = dates[j];
            dates[j]=tmp;
        }
    }
    return dates;
}

cDate* fill_cDate(cDate *date, uint day, uint month, uint year) {
    if (date != NULL) {
        (*date).day = day;
        (*date).month = month;
        (*date).year = year;
    }

    return date;
}

cDate* add_date(cDate* dates, cDate date, int *number_of_elements, int *buffer_size) {
    if (*number_of_elements >= *buffer_size) {
        dates = grow(dates, *number_of_elements, buffer_size);
    }

    dates[*number_of_elements].day = date.day;
    dates[*number_of_elements].month = date.month;
    dates[*number_of_elements].year = date.year;

    *number_of_elements += 1;

    return dates;
}

cDate* grow(cDate *dates, int number_of_elements, int *buffer_size) {
    size_t size = *buffer_size;
    cDate* new_dates = (cDate*)realloc(dates, sizeof(cDate) * (size * 2));

    if (new_dates != NULL) {
        //for (int i = 0; i < number_of_elements; i++) {
        //    new_dates[i] = dates[i];
        //}
        *buffer_size *= 2;
    }

    return new_dates;
}

int greater_date(cDate day1, cDate day2) {
    int res = 0;

    if (day1.year > day2.year) {
        res = 1;
    } else if (day1.month > day2.month) {
        res = 1;
    } else if (day1.day > day2.day) {
        res = 1;
    } else if (day1.day < day2.day) {
        res = -1;
    }

    return res;
}

void swipeDate(cDate *day1, cDate *day2) {
    cDate tmp = *day1;
    *day1 = *day2;
    *day2 = tmp;
}

void printDate(cDate date) {
    printf("%u.%u.%u\n", date.day, date.month, date.year);
}

int check_valid_date(cDate date) {
    int res = 1;

    // Check valid year
    if (date.year < 1 || date.year > 2077) {
        return 0;
    }

    // check valid month
    if (date.month < 1 || date.month > 12) {
        return 0;
    }

    // Check month with 31 days
    if ( (date.month == 1 || date.month == 3 ||
         date.month == 5 || date.month == 7 ||
         date.month == 8 || date.month == 10 ||
         date.month == 12) && (date.day > 31 && date.day < 1) )
    {
        return 0;
    }

    // Check month with 30 days
    if ((date.month == 6 || date.month == 9 ||
         date.month == 11) && (date.day > 30 && date.day < 1))
    {
        return 0;
    }

    // Check February
    if (date.month == 2 && date.day >= 1 && date.day <= 29) {
        if (date.year % 4 != 0 && date.day == 29) {
            res = 0;
        } else if (date.year % 100 == 0 && date.year % 400 != 0) {
            if (date.day == 29) {
                res = 0;
            }
        } else {
            res = 1;
        }
    }

    return res;
}