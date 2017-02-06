#ifndef API_ROUTER_H
#define API_ROUTER_H

#include <stdbool.h>

typedef void ArgList;

typedef enum API_ROUTER_ERROR {
    API_ROUTER_E_OK = 0,
    API_ROUTER_E_NO_MEMORY = 1,
    API_ROUTER_E_WRONG_PARAMETER = 2,
    API_ROUTER_E_URL_EXISTED = 3,
    API_ROUTER_E_NOT_FOUND = 4
} API_ROUTER_ERROR;

void arg_list_free(ArgList *l);
bool arg_list_get(ArgList *l,
                  const char *key,
                  const int klen,
                  const char **val,
                  int *vlen);

#endif /* API_ROUTER_H */
