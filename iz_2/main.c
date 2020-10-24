
#include "static.h"
#include "reader.h"
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

void tests() {
    // TEST READER
    {
        char* filename = "../test_files/file-1.txt";
        size_t rc = read_file_size(filename);
        assert(rc == ERROR_OPEN_FILE);
    }
    {
        char* filename = "../test_files/empty.txt";
        size_t rc = read_file_size(filename);
        assert(rc == ERROR_EMPTY_FILE);
    }
    {
        char* filename = "../test_files/empty.txt";
        size_t rc = read_file_size(filename);
        assert(rc == ERROR_EMPTY_FILE);
    }
    {
        char *filename = "../test_files/file-1.txt";
        int rc = read_file_data(filename, NULL, 0);
        assert(rc == ERROR_OPEN_FILE);
    }
    {
        // Arrange
        char* filename = "../test_files/test1.txt";
        char* expected = "abcdef123\n ";
        size_t size = read_file_size(filename);
        char* file_content = (char*) malloc(sizeof(char) * size);

        // Act
        int rc = read_file_data(filename, file_content, &size);

        // Assert
        assert(size == 10);
        assert(file_content != NULL);
        assert(rc == 0);
        assert(strncmp(file_content, expected, size) == 0);

        free(file_content);
    }
    {
        // Arrange
        char *filename = "../test_files/test1.txt";
        size_t size = read_file_size(filename);
        char *file_content = (char *) malloc(sizeof(char) * size);
        read_file_data(filename, file_content, &size);

        // Act
        char *finded_sequence = find_sequence(file_content, &size);

        // Assert
        assert(size != 0);
        assert(file_content != NULL);
        assert(finded_sequence == ERROR_NOT_FOUND_SEQUENCE);

        free(file_content);
    }
    {
        // Arrange
        char* filename = "../test_files/test2.txt";
        char* expected = "<Ebbb>";
        size_t size = read_file_size(filename);
        char* file_content = (char*) malloc(sizeof(char) * size);
        read_file_data(filename, file_content, &size);

        // Act
        char* finded_sequence = find_sequence(file_content, &size);

        // Assert
        assert(size != 0);
        assert(file_content != NULL);
        assert(finded_sequence != NULL);
        assert(strcmp(expected, finded_sequence) == 0);

        free(file_content);
        free(finded_sequence);
    }
    {
        // Arrange
        char *filename = "../test_files/test1.txt";
        size_t size = read_file_size(filename);
        char *file_content = (char *) malloc(sizeof(char) * size);
        read_file_data(filename, file_content, &size);

        // Act
        char *finded_sequence = find_sequence_multi(file_content, &size);

        // Assert
        assert(size != 0);
        assert(file_content != NULL);
        assert(finded_sequence == ERROR_NOT_FOUND_SEQUENCE);

        free(file_content);
    }
    {
        // Arrange
        char* filename = "../test_files/test2.txt";
        char* expected = "<Ebbb>";
        size_t size = read_file_size(filename);
        char* file_content = (char*) malloc(sizeof(char) * size);
        read_file_data(filename, file_content, &size);

        // Act
        char* finded_sequence = find_sequence_multi(file_content, &size);

        // Assert
        assert(size != 0);
        assert(file_content != NULL);
        assert(finded_sequence != NULL);
        assert(strcmp(expected, finded_sequence) == 0);

        free(file_content);
        free(finded_sequence);
    }
    {
        // Arrange
        char *filename = "../test_files/test4.txt";
        size_t size = read_file_size(filename);
        char *file_content = (char *) malloc(sizeof(char) * size);
        read_file_data(filename, file_content, &size);

        // Act
        char *finded_sequence = find_sequence(file_content, &size);
        char *finded_sequence_multi = find_sequence_multi(file_content, &size);

        // Assert
        assert(size != 0);
        assert(file_content != NULL);
        assert(strcmp(finded_sequence, finded_sequence_multi) == 0);

        //free
        free(file_content);
    }
}

int main(int argc, const char * argv[]) {
    tests();

    char* filename = "../test_files/test2.txt";
    size_t size = read_file_size(filename);

    if (size == 0) {
        printf(ERROR_EMPTY_FILE_MSG);
        return ERROR_EMPTY_FILE;
    } else if (size < 0) {
        printf(ERROR_OPEN_FILE_MSG);
        return ERROR_OPEN_FILE;
    }

    char* file_content = (char*) malloc(sizeof(char*) * size);
    if (file_content == NULL) {
        printf(ERROR_ALLOCATE_MEMORY_MSG);
        return -1;
    }
    if (read_file_data(filename, file_content, &size) < 0) {
        printf(ERROR_OPEN_FILE_MSG);
        return ERROR_OPEN_FILE;
    }

    char* finded_sequence = find_sequence(file_content, &size);

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

    char* result = malloc(sizeof(char*)*5);

    char* finded_sequence_multi = find_sequence_multi(file_content, &size);

    if (finded_sequence_multi == NULL) {
        return -1;
    }

    for (int i = 0; finded_sequence_multi[i] != '\0'; i++) {
        printf("%c", finded_sequence_multi[i]);
        if (finded_sequence_multi[i+1] == '\0') {
            printf("\n");
        }
    }

    free(result);
    free(file_content);
    free(finded_sequence);
    return 0;
}
