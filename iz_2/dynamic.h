#ifndef dynamic_h
#define dynamic_h

#include "errors.h"
#include "header.h"
#include "helper_func.h"

typedef struct point_t {
    int start;
    int end;
} point_t;

char* find_sequence_multi(const char* array, size_t size);
void proccess(const char* array, int start, int end, point_t* point);
int* find_closed_quotes(const char* array, size_t size, int* count_quotes);

#endif /* dynamic_h */
