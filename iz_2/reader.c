#include "reader.h"

size_t read_file_size(const char* in_file_name) {
    FILE* file = fopen(in_file_name, "r");
    if (!file) {
        return ERROR_OPEN_FILE;
    }

    size_t size = 0;
    for(char c;;) {
        if (fscanf(file, "%c", &c) != 1) {
            break;
        }
        size++;
    }

    if (size == 0) {
        return ERROR_EMPTY_FILE;
    }

    fclose(file);
    return size;
}

int read_file_data(const char* in_file_name, char* array, const size_t* size) {
    FILE* file = fopen(in_file_name, "r");
    if (!file) {
        return ERROR_OPEN_FILE;
    }

    for(int i = 0; i < *size; i++) {
        char c;
        if (fscanf(file, "%c", &c) != 1) {
            break;
        }

        array[i] = c;
    }

    return 0;
}