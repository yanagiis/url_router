#include "url_router.h"
#include "url_tree.h"
#include "memory.h"

#include <string.h>

typedef struct UrlRouterImp {
    UrlTree t;
} UrlRouterImp;

UrlRouter *url_router_new()
{
    UrlRouterImp *r = MALLOC(sizeof(UrlRouterImp));
    url_tree_init(&r->t);
    return (UrlRouter *)r;
}

void url_router_free(UrlRouter *router)
{
    UrlRouterImp *r = (UrlRouter *)router;
    url_tree_destroy(&r->t);
    FREE(r);
}

URL_ROUTER_ERROR url_router_insert(UrlRouter *router,
                                   const char *key,
                                   void *data)
{
    UrlRouterImp *r = (UrlRouter *)router;
    return url_tree_insert(&r->t, key, strlen(key), data);
}

URL_ROUTER_ERROR url_router_insertl(UrlRouter *router,
                                    const char *key,
                                    int klen,
                                    void *data)
{
    UrlRouterImp *r = (UrlRouter *)router;
    return url_tree_insert(&r->t, key, klen, data);
}

URL_ROUTER_ERROR url_router_match(UrlRouter *router,
                                  const char *key,
                                  Args *arg,
                                  void **data)
{
    UrlRouterImp *r = (UrlRouter *)router;
    return url_tree_match(&r->t, key, strlen(key), arg, data);
}

URL_ROUTER_ERROR url_router_matchl(UrlRouter *router,
                                   const char *key,
                                   int klen,
                                   Args *arg,
                                   void **data)
{
    UrlRouterImp *r = (UrlRouter *)router;
    return url_tree_match(&r->t, key, klen, arg, data);
}
