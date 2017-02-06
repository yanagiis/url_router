#ifndef ARG_LIST_H
#define ARG_LIST_H

#include "str.h"
#include <stdbool.h>

typedef struct Pair {
    String key;
    String value;
} Pair;

typedef struct ArgListImp {
    int len;
    int cap;
    Pair pairs[];
} ArgListImp;

ArgListImp *arg_list_new(int size);
bool arg_list_push(ArgListImp *l, String *key, String *value);
bool arg_list_pop(ArgListImp *l);

#endif /* ARG_LIST_H */
