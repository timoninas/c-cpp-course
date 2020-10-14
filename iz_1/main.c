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
    int count;
    printf("Input count of days: ");
    scanf("%d", &count);

    if (count < 1) {
        printf("Incorrect size input\n");
        return ERR_COUNT;
    }

    int curr_num_dates = 0;
    int buff_dates = 1;
    date_t* dates = (date_t*)malloc(sizeof(date_t) * buff_dates);

    for (int i = 0; i < count; i++) {
        int day, month, year;
        printf("\nInput day in format dd.mm.yyyy: ");

        if (scanf("%d.%d.%d", &day, &month, &year) == 3) {
            date_t date = {day, month, year};
            if (check_valid_date(date) == 0) {
                printf("Incorrect data input\n");
                free(dates);
                return ERR_DATA;
            }
            dates = add_date(dates, date, &curr_num_dates, &buff_dates);
        } else {
            printf("Incorrect data input\n");
            free(dates);
            return ERR_DATA;
        }
    }

    dates = sort(dates, curr_num_dates, buff_dates);

    printf("\nSorted dates:\n");
    for (int i = 0; i < curr_num_dates; i++) {
        print_date(dates[i]);
    }

    return 0;
}
