
#include "static.h"
#include "reader.h"
#include <dlfcn.h>
#include "dynamic.h"


/*
 Вариант 20
 Сравните и выведите в консоль время работы последовательного
 и параллельного с использованием нескольких процессов алгоритмов,
 каждый из которых выделяет в динамической памяти символьный
 массив размером 100 Мб и выполняет поиск в тексте максимальной
 последовательности, заключенной между символами кавычек и
 начинающейся с буквы латинского алфавита в верхнем регистре.
*/

int main(int argc, const char * argv[]) {
    char* filename = "../test_files/test2.txt";
    size_t size = read_file_size(filename);

    if (size == 0) {
        printf(ERROR_EMPTY_FILE_MSG);
        return ERROR_EMPTY_FILE;
    } else if (size < 0) {
        printf(ERROR_OPEN_FILE_MSG);
        return ERROR_OPEN_FILE;
    }

    char* file_content = (char*) malloc(sizeof(char) * size);
    if (file_content == NULL) {
        printf(ERROR_ALLOCATE_MEMORY_MSG);
        return -1;
    }
    if (read_file_data(filename, file_content, &size) < 0) {
        printf(ERROR_OPEN_FILE_MSG);
        free(file_content);
        return ERROR_OPEN_FILE;
    }

    char* finded_sequence = find_sequence(file_content, size);

    if (finded_sequence == NULL) {
        printf("Not found sequence\n");
        free(file_content);
        return 0;
    }

    for (int i = 0; finded_sequence[i] != '\0'; i++) {
        printf("%c", finded_sequence[i]);
        if (finded_sequence[i+1] == '\0') {
            printf("\n");
        }
    }
    
    free(finded_sequence);

    void *library = dlopen("lib_multiproc.so", RTLD_LAZY);
    if (library)
    {
        char* (*func)(const char*, size_t) = NULL;
        *(void **) (&func) = dlsym(library, "find_sequence_multi");
        char* finded_sequence_multi = func(file_content, size);
        if (finded_sequence_multi != NULL) {
            for (int i = 0; finded_sequence_multi[i] != '\0'; i++) {
                printf("%c", finded_sequence_multi[i]);
                if (finded_sequence_multi[i+1] == '\0') {
                    printf("\n");
                }   
            }
            free(finded_sequence_multi);
        }
        dlclose(library);
    } else {
        printf("Error open library\n");
    }

    free(file_content);

    return 0;
}
