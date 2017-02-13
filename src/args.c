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

#include <string.h>

#include "args.h"
#include "memory.h"
#include "str.h"
#include "url_router.h"

void url_router_arg_free(char *arg)
{
	url_router_free(arg);
}

ArgsImp *url_router_args_new(int size)
{
    ArgsImp *l = url_router_malloc(sizeof(ArgsImp) + sizeof(Pair) * size);
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

    return (Args *)l;
}

void url_router_args_free(Args *l)
{
    if (l != NULL) {
        url_router_free(l);
    }
}

bool url_router_args_push(ArgsImp *l, String *key, String *value)
{
    if (l->len == l->cap) {
        return false;
    }

    Pair *pair = &l->pairs[l->len++];
    pair->key = *key;
    pair->value = *value;

    return true;
}

bool url_router_args_pop(ArgsImp *l)
{
    if (l->len == 0) {
        return false;
    }

    --l->len;
    return true;
}

bool url_router_args_get(Args *al, const char *key, char **val)
{
    const char *value;
    int len;

    bool ret = url_router_args_getl(al, key, strlen(key), &value, &len);
    if (ret) {
        *val = url_router_malloc(len + 1);
        if (*val == NULL) {
            return false;
        }
        strncpy(*val, value, len);
        (*val)[len] = 0;
    }
    return ret;
}

bool url_router_args_get_as_long(Args *al, const char *key, long *val)
{
    char *sval;
    bool ret = url_router_args_get(al, key, &sval);
    if (ret) {
        *val = strtol(sval, NULL, 10);
        url_router_arg_free(sval);
    }
    return ret;
}

bool url_router_args_getl(Args *al,
                          const char *key,
                          const int klen,
                          const char **val,
                          int *vlen)
{
    ArgsImp *l = (ArgsImp *)al;
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
