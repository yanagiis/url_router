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

#ifndef URL_ROUTER_URL_TREE_H
#define URL_ROUTER_URL_TREE_H

#include <stdbool.h>
#include <stdint.h>

#include "url_router.h"

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

URL_ROUTER_ERROR url_tree_init(UrlTree *t);
URL_ROUTER_ERROR url_tree_destroy(UrlTree *t);
URL_ROUTER_ERROR
url_tree_insert(UrlTree *t, const char *url, int len, void *data);
URL_ROUTER_ERROR
url_tree_match(UrlTree *t,
               const char *url,
               const int len,
               Args **arg,
               void **data);

#endif /* URL_ROUTER_URL_TREE_H */
