#include "dynamic.h"

char* find_sequence_multi(const char* array, size_t size) {
    // поиск позиций закрывающих скобок
    int count_quotes = 0;
    int *position_quotes = find_closed_quotes(array, size, &count_quotes);
    if (position_quotes == NULL) {
        return ERROR_NOT_FOUND_SEQUENCE;
    }

    // проверка если процессов слишком много
    int count_proc = get_nprocs();
    if (count_quotes > 1 && count_proc >=  count_quotes / 2) {
        count_proc = count_quotes / 2;
    }

    // открытие файловых дескрипторов
    int fd[count_proc][2];
    for (int i = 0; i < count_proc; i++) {
        if (pipe(fd[i]) < 0) {
            free(position_quotes);
            return ERROR_OPEN_DESCRIPTORS;
        }
    }

    // запуск процессов для поиска макс. последовательности
    for (int i = 0; i < count_proc; i++) {
        if (count_quotes == 1) count_quotes++;
        int start = count_quotes * (i) / count_proc;
        int end = (count_quotes * (i+1)) / count_proc;

        int pid = fork();

        if (pid == 0) {
            point_t point = {-1, -1};
            proccess(array,
                     i == 0 ? 0: position_quotes[start],
                     i == (count_proc-1) ? size: position_quotes[end],
                     &point);
            close(fd[i][0]);
            write(fd[i][1], &point, sizeof(point_t));
            close(fd[i][1]);
            free(position_quotes);
            exit(0);
        } else if (pid < 0) {
            free(position_quotes);
            return ERROR_PROCCESS;
        }
    }
    
    free(position_quotes);

    // поиск позиции максимальной последовательности
    int status = 0;
    point_t result_point = {-1, -1};
    for (int i = 0; i < count_proc; i++)
    {
        wait(&status);
        if (!WIFEXITED(status)) {
            return ERROR_PROCCESS;
        }

        point_t point = {-1, -1};
        close(fd[i][1]);
        read(fd[i][0], &point, sizeof(point_t));
        close(fd[i][0]);
        if ( (point.end - point.start) >= (result_point.end - result_point.start) ) {
            result_point = point;
        }
    }

    if (result_point.start == -1 || result_point.end == -1) {
        return ERROR_NOT_FOUND_SEQUENCE;
    }

    int length = result_point.end - result_point.start;

    char* result_sequence = (char*)malloc(sizeof(char) * (length + 2));
    if (result_sequence == NULL) {
        return ERROR_ALLOCATE_MEMORY;
    }

    int k = 0;
    for (int i = result_point.start; i <= result_point.end; i++) {
        result_sequence[k++] = array[i];
    }
    result_sequence[length + 1] = '\0';

    return result_sequence;
}

void proccess(const char* array, int start, int end, point_t* point) {
    int tmp_start = -1;
    for (int i = start; i < end; i++) {
        if (array[i] == '<' && (i+1) < end && is_upper(array[i+1])) {
            tmp_start = i;
        } else if (array[i] == '>') {
            if (tmp_start != -1 && (i - tmp_start) >= (point->end - point->start)) {
                point->start = tmp_start;
                point->end = i;
                tmp_start = -1;
            } else if (tmp_start != -1) {
                tmp_start = -1;
            }
        }
    }
}

int* find_closed_quotes(const char* array, size_t size, int* count_quotes) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if (array[i] == '>') {
            count++;
        }
    }

    if (count == 0) {
        return NULL;
    }

    int* res = (int*)malloc(sizeof(int)*count);

    if (res == NULL) {
        return NULL;
    }

    int k = 0;
    for(int i = 0; i < size; i++) {
        if (array[i] == '>') {
            res[k++] = i;
        }
    }

    *count_quotes = count;
    return res;
}