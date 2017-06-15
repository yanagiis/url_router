/* BSD 3-Clause License

Copyright (c) 2017, yanagiis@gmail.com
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "memory.h"
#include "url_router/dict.h"
#include "url_router/url_router.h"
#include "url_tree.h"

#include <string.h>

typedef struct UrlRouterImp {
    UrlTree t;
} UrlRouterImp;

UrlRouter *url_router_new()
{
    UrlRouterImp *r = malloc(sizeof(UrlRouterImp));
    url_tree_init(&r->t);
    return (UrlRouter *)r;
}

void url_router_free(UrlRouter *router)
{
    UrlRouterImp *r = (UrlRouter *)router;
    url_tree_destroy(&r->t);
    free(r);
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
                                  struct Dict **args,
                                  void **data)
{
    UrlRouterImp *r = (UrlRouter *)router;
    return url_tree_match(&r->t, key, strlen(key), args, data);
}

URL_ROUTER_ERROR url_router_matchl(UrlRouter *router,
                                   const char *key,
                                   int klen,
                                   struct Dict **args,
                                   void **data)
{
    UrlRouterImp *r = (UrlRouter *)router;
    return url_tree_match(&r->t, key, klen, args, data);
}

void url_router_dict_free(struct Dict *dict)
{
    if (dict != NULL) {
        dict_free(dict, free);
    }
}
