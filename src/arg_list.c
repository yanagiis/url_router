#include <string.h>

#include "api_router.h"
#include "arg_list.h"
#include "memory.h"
#include "str.h"

ArgListImp *arg_list_new(int size)
{
    ArgListImp *l = memory_malloc(sizeof(ArgListImp) + sizeof(Pair) * size);
    if (l == NULL) {
        return NULL;
    }

    l->len = 0;
    l->cap = size;
    for (int i = 0; i < l->cap; ++i) {
        l->pairs[i].key.str = NULL;
        l->pairs[i].key.len = 0;
        l->pairs[i].value.str = NULL;
        l->pairs[i].value.len = 0;
    }

    return (ArgList *)l;
}

void arg_list_free(ArgList *l)
{
    if (l != NULL) {
        memory_free(l);
    }
}

bool arg_list_push(ArgListImp *l, String *key, String *value)
{
    if (l->len == l->cap) {
        return false;
    }

    Pair *pair = &l->pairs[l->len++];
    pair->key = *key;
    pair->value = *value;

    return true;
}

bool arg_list_pop(ArgListImp *l)
{
    if (l->len == 0) {
        return false;
    }

    --l->len;
    return true;
}

bool arg_list_get(ArgList *al,
                  const char *key,
                  const int klen,
                  const char **val,
                  int *vlen)
{
    ArgListImp *l = (ArgListImp *)al;
    for (int i = 0; i < l->len; ++i) {
        String *skey = &l->pairs[i].key;
        if (skey->len != klen) {
            continue;
        }
        if (strncmp(skey->str, key, klen) != 0) {
            continue;
        }

        String *sval = &l->pairs[i].value;
        *val = sval->str;
        *vlen = sval->len;
        return true;
    }

    return false;
}
