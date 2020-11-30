#include "static.h"

void print_seq(const char* array, int start, int end) {
    printf("Finded sequence:\n");
    for (int i = start; i <= end; i++) {
        printf("%c", array[i]);
    }
    printf("\n");
}

char* find_sequence(char* array, size_t size) {
    int final_start = 0, start = -1;
    int final_end = 0;

    for (int i = 0; i < size; i++) {
        switch (array[i]) {
            case '<':
                if (i+1 < size && is_upper(array[i+1])) {
                    start = i;
                }
                break;

            case '>':
                if (start != -1 && (i - start) >= (final_end - final_start)) {
                    final_start = start;
                    final_end = i;
                    start = -1;
                } else if (start != -1) {
                    start = -1;
                }
            default:
                break;
        }
    }

    int length = final_end - final_start;

    if (length < 2) {
        return ERROR_NOT_FOUND_SEQUENCE;
    }

    char* result = malloc(sizeof(char) * (length + 2));

    if (result == NULL) return ERROR_ALLOCATE_MEMORY;

    int k = 0;
    for (int i = final_start; i <= final_end; i++) {
        result[k++] = array[i];
    }

    result[length+1] = '\0';

    return result;
}