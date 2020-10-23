#ifndef reader_h
#define reader_h

#include "errors.h"
#include "header.h"

size_t read_file_size(const char* in_file_name);

int read_file_data(const char* in_file_name, char* array, const size_t* size);

#endif /* reader_h */
