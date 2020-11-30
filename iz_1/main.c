/*
 Создать структуру для хранения информации
 о дате: номере года, номере месяца и числе
 Составить с ее использованием программу
 вывода информации обо всех известных датах,
 начиная с наиболее ранней.
 */

#include "date.h"

#define ERR_COUNT -1
#define ERR_DATA -2

int main(int argc, const char * argv[]) {
    int curr_num_dates = 0;
    int buff_dates = 1;
    date_t* dates = (date_t*)malloc(sizeof(date_t) * buff_dates);

    date_t date1, date2, date3, date4;
    fill_date(&date1, 1, 5, 1999);
    fill_date(&date2, 2, 6, 1998);
    fill_date(&date3, 3, 7, 1997);
    fill_date(&date4, 4, 8, 1996);

    dates = add_date(dates, date1, &curr_num_dates, &buff_dates);
    dates = add_date(dates, date2, &curr_num_dates, &buff_dates);
    dates = add_date(dates, date3, &curr_num_dates, &buff_dates);
    dates = add_date(dates, date4, &curr_num_dates, &buff_dates);

    printf("Before sort:\n");
    for (int i = 0; i < curr_num_dates; i++) {
        print_date(dates[i]);
    }

    dates = sort(dates, curr_num_dates, buff_dates);

    printf("\nAfter sort:\n");
    for (int i = 0; i < curr_num_dates; i++) {
        print_date(dates[i]);
    }

    free(dates);

    return 0;
}
