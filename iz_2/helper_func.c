#include "helper_func.h"

int is_upper(char symb) {
    if ((int) symb >= 65 && (int) symb <= 90) {
        return 1;
    } else {
        return 0;
    }
}