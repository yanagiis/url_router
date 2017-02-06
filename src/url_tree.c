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

#include "arg_list.h"
#include "memory.h"
#include "str.h"
#include "url_tree.h"

#define FOREACH_NODE_EDGE(n, e) for (UrlEdge *e = n->begin; e; e = e->next)

static const char *strnchr(const char *url, const int len, const char c)
{
    for (int i = 0; i < len; ++i) {
        if (url[i] == c) {
            return url + i;
        }
    }

    return url + len;
}

static bool is_url_validated(const String *url)
{
    if (url->len < 1 || url->str[0] != '/') {
        return false;
    }

    return true;
}

static bool
url_get_first_level(const String *url, String *subpath, String *remain)
{
    if (url->len < 1) {
        return false;
    }

    const char *skip_first = url->str + 1;
    const int skip_first_len = url->len - 1;
    const char *end = strnchr(skip_first, skip_first_len, '/');

    const int sublen = end - skip_first;
    if (sublen < 1) {
        return false;
    }

    subpath->str = skip_first;
    subpath->len = sublen;
    remain->str = skip_first + sublen;
    remain->len = skip_first_len - sublen;
    return true;
}

static int url_get_num_of_args(const String *url)
{
    String subpath, remain_path;
    int count = 0;
    while (url_get_first_level(url, &subpath, &remain_path)) {
        if (subpath.str[0] == ':') {
            ++count;
        }
        url = &remain_path;
    }

    return count;
}

static void url_node_init(UrlNode *node)
{
    node->data = NULL;
    node->begin = node->end = NULL;
    node->leaf = false;
}

static UrlEdge *url_edge_new(String *url)
{
    UrlEdge *new_edge = memory_malloc(sizeof(UrlEdge) + url->len);
    if (new_edge == NULL) {
        return NULL;
    }

    strncpy(new_edge->label, url->str, url->len);
    new_edge->len = url->len;
    new_edge->next = NULL;
    url_node_init(&new_edge->node);
    return new_edge;
}

static void url_edge_free(UrlEdge *e)
{
    memory_free(e);
}

URL_ROUTER_ERROR url_tree_init(UrlTree *t)
{
    url_node_init(&t->root);
    t->max_args = 0;
    return URL_ROUTER_E_OK;
}

static URL_ROUTER_ERROR _url_tree_destroy(UrlNode *n)
{
    if (n) {
        for (UrlEdge *e = n->begin; e;) {
            UrlEdge *next = e->next;
            _url_tree_destroy(&e->node);
            url_edge_free(e);
            e = next;
        }
    }
    return URL_ROUTER_E_OK;
}

URL_ROUTER_ERROR url_tree_destroy(UrlTree *t)
{
    return _url_tree_destroy(&t->root);
}

static UrlEdge *url_create_edges(const String *url, void *data)
{
    String subpath, remain_path;
    url_get_first_level(url, &subpath, &remain_path);

    UrlEdge *root_edge = url_edge_new(&subpath);
    if (root_edge == NULL) {
        return NULL;
    }

    UrlEdge *prev_edge = root_edge;
    while (remain_path.len > 0) {
        if (!url_get_first_level(&remain_path, &subpath, &remain_path)) {
            break;
        }

        UrlEdge *edge = url_edge_new(&subpath);
        if (edge == NULL) {
            _url_tree_destroy(&root_edge->node);
            url_edge_free(root_edge);
            return NULL;
        }

        prev_edge->node.begin = prev_edge->node.end = edge;
        prev_edge = edge;
    }

    prev_edge->node.leaf = true;
    prev_edge->node.data = data;
    return root_edge;
}

static URL_ROUTER_ERROR
url_node_add_edge(UrlNode *n, const String *url, void *data)
{
    UrlEdge *new_edge = url_create_edges(url, data);
    if (new_edge == NULL) {
        return URL_ROUTER_E_NO_MEMORY;
    }
    if (n->begin == NULL) {
        n->begin = n->end = new_edge;
    } else {
        if (url->str[0] == ':') {
            n->end->next = new_edge;
            n->end = new_edge;
        } else {
            new_edge->next = n->begin;
            n->begin = new_edge;
        }
    }

    return URL_ROUTER_E_OK;
}

URL_ROUTER_ERROR
_url_tree_insert(UrlNode *n, const String *url, void *data)
{
    if (url->len == 0) {
        if (n->leaf) {
            return URL_ROUTER_E_URL_EXISTED;
        }
        n->data = data;
        n->leaf = true;
        return URL_ROUTER_E_OK;
    }

    FOREACH_NODE_EDGE(n, e)
    {
        String subpath, remain_path;
        if (!url_get_first_level(url, &subpath, &remain_path)) {
            break;
        }
        if (subpath.len != e->len) {
            continue;
        }
        if (strncmp(subpath.str, e->label, e->len) != 0) {
            continue;
        }

        return _url_tree_insert(&e->node, &remain_path, data);
    }

    return url_node_add_edge(n, url, data);
}

URL_ROUTER_ERROR
url_tree_insert(UrlTree *t, const char *url, int len, void *data)
{
    String surl = {.str = url, .len = len};

    if (!is_url_validated(&surl)) {
        return URL_ROUTER_E_WRONG_PARAMETER;
    }

    URL_ROUTER_ERROR err = _url_tree_insert(&t->root, &surl, data);

    if (err == URL_ROUTER_E_OK) {
        int num_args = url_get_num_of_args(&surl);
        if (num_args > t->max_args) {
            t->max_args = num_args;
        }
    }

    return err;
}

static URL_ROUTER_ERROR
_url_tree_match(UrlNode *n, const String *url, ArgListImp *l, void **data)
{
    URL_ROUTER_ERROR err;

    if (url->len == 0) {
        if (!n->leaf) {
            return URL_ROUTER_E_NOT_FOUND;
        }
        *data = n->data;
        return URL_ROUTER_E_OK;
    }

    FOREACH_NODE_EDGE(n, e)
    {
        String subpath, remain_path;
        if (!url_get_first_level(url, &subpath, &remain_path)) {
            break;
        }
        if (e->label[0] == ':') {
            String label;
            label.str = e->label + 1;
            label.len = e->len - 1;
            arg_list_push(l, &label, &subpath);
        } else {
            if (subpath.len != e->len) {
                continue;
            }
            if (strncmp(subpath.str, e->label, e->len) != 0) {
                continue;
            }
        }

        err = _url_tree_match(&e->node, &remain_path, l, data);
        if (err == URL_ROUTER_E_OK) {
            return err;
        }

        if (e->label[0] == ':') {
            arg_list_pop(l);
        }
    }

    return URL_ROUTER_E_NOT_FOUND;
}

URL_ROUTER_ERROR
url_tree_match(UrlTree *t,
               const char *url,
               const int len,
               ArgList **arg,
               void **data)
{
    if (url == NULL || len < 1 || url[0] != '/') {
        return URL_ROUTER_E_WRONG_PARAMETER;
    }

    ArgListImp *l = NULL;
    if (t->max_args > 0) {
        l = arg_list_new(t->max_args);
    }
    *arg = (ArgList *)l;

    String surl = {.str = url, .len = len};
    URL_ROUTER_ERROR err = _url_tree_match(&t->root, &surl, l, data);
    if (err != URL_ROUTER_E_OK) {
        arg_list_free(l);
    }
    return err;
}
