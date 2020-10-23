//
//  dynamic.h
//  iz_2
//
//  Created by Антон Тимонин on 21.10.2020.
//

#ifndef dynamic_h
#define dynamic_h

#include "errors.h"
#include "header.h"

typedef struct Point {
    int start;
    int end;
} Point;

char* find_sequence_multi(const char* array, const size_t* size);
int proccess(const char* array, int start, int end, Point* point);
int* find_closed_quotes(const char* array, const size_t* size, int* count_quotes);

#endif /* dynamic_h */
