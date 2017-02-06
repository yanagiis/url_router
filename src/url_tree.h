#ifndef URL_TREE_H
#define URL_TREE_H

#include <stdbool.h>
#include <stdint.h>

#include "api_router.h"

#define POINTER_SIZE (sizeof(void *))

struct UrlEdge;
struct UrlNode;

typedef struct UrlNode {
    struct UrlEdge *begin;
    struct UrlEdge *end;
    void *data;
    bool leaf;
} UrlNode;

typedef struct UrlEdge {
    struct UrlNode node;
    struct UrlEdge *next;
    uint32_t len;
    char label[];
} UrlEdge;

typedef struct UrlTree {
    struct UrlNode root;
    int max_args;
} UrlTree;

API_ROUTER_ERROR url_tree_init(UrlTree *t);
API_ROUTER_ERROR url_tree_destroy(UrlTree *t);
API_ROUTER_ERROR
url_tree_insert(UrlTree *t, const char *url, int len, void *data);
API_ROUTER_ERROR
url_tree_match(UrlTree *t,
               const char *url,
               const int len,
               ArgList **arg,
               void **data);

#endif /* URL_TREE_H */
