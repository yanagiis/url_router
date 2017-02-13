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

#include "url_tree.h"
#include <unity/unity.h>

#define OP_INSERT 1
#define OP_INSERT_CONFLICT 2
#define OP_MATCH 3
#define OP_NOT_MATCH 4

struct Case {
    int op;
    const char *url;
    int len;
    int data;
};

void test_url_tree_insert_match_no_arg()
{
    UrlTree tree;

    struct Case cases[] = {
        {OP_INSERT, "/a/b/c", 6, 1},
        {OP_MATCH, "/a/b/c", 6, 1},

        {OP_INSERT, "/a/b/d", 6, 2},
        {OP_MATCH, "/a/b/c", 6, 1},
        {OP_MATCH, "/a/b/d", 6, 2},

        {OP_INSERT, "/b/c/d", 6, 3},
        {OP_MATCH, "/a/b/c", 6, 1},
        {OP_MATCH, "/a/b/d", 6, 2},
        {OP_MATCH, "/b/c/d", 6, 3},

        {OP_INSERT, "/b/c", 4, 4},
        {OP_MATCH, "/a/b/c", 6, 1},
        {OP_MATCH, "/a/b/d", 6, 2},
        {OP_MATCH, "/b/c/d", 6, 3},
        {OP_MATCH, "/b/c", 4, 4},

        {OP_NOT_MATCH, "/a/b/e", 6, 0},
        {OP_NOT_MATCH, "/a/b", 4, 0},
        {OP_NOT_MATCH, "/a", 2, 0},

        {OP_INSERT_CONFLICT, "/a/b/c", 6, 1},
        {OP_INSERT_CONFLICT, "/a/b/d", 6, 2},
        {OP_INSERT_CONFLICT, "/b/c/d", 6, 3},
        {OP_INSERT_CONFLICT, "/b/c", 4, 4},
    };

    url_tree_init(&tree);

    for (int i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        struct Case *c = &cases[i];
        URL_ROUTER_ERROR err;
        Dict *args;
        int *data;
        switch (c->op) {
            case OP_INSERT:
                err = url_tree_insert(&tree, c->url, c->len, (void *)&c->data);
                TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
                break;
            case OP_INSERT_CONFLICT:
                err = url_tree_insert(&tree, c->url, c->len, (void *)&c->data);
                TEST_ASSERT_EQUAL(URL_ROUTER_E_URL_EXISTED, err);
            case OP_MATCH:
                err = url_tree_match(&tree, c->url, c->len, &args,
                                     (void **)&data);
                TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
                TEST_ASSERT_EQUAL_INT(c->data, *data);
                url_router_dict_free(args);
                break;
            case OP_NOT_MATCH:
                err = url_tree_match(&tree, c->url, c->len, &args,
                                     (void **)&data);
                TEST_ASSERT_EQUAL(URL_ROUTER_E_NOT_FOUND, err);
                break;
        }
    }

    url_tree_destroy(&tree);
}

void test_url_tree_insert_match_with_args()
{
    UrlTree tree;
    Dict *args;
    URL_ROUTER_ERROR err;
    char *var;
    bool is_existed;
    int data;
    int vlen;

    url_tree_init(&tree);

    // insert /a/:var/c
    err = url_tree_insert(&tree, "/a/:var/c", 9, (void *)1);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    // /a/b/c should match /a/:var/c
    err = url_tree_match(&tree, "/a/b/c", 6, &args, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    var = dict_get(args, "var");
    TEST_ASSERT_NOT_NULL(var);
    TEST_ASSERT_EQUAL_STRING("b", var);
    TEST_ASSERT_EQUAL_INT(1, data);
    url_router_dict_free(args);

    // /a/b/d should not match
    err = url_tree_match(&tree, "/a/b/d", 6, &args, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_NOT_FOUND, err);

    // /a/hello/c should match /a/:var/c
    err = url_tree_match(&tree, "/a/hello/c", 10, &args, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_INT(1, data);
    var = dict_get(args, "var");
    TEST_ASSERT_NOT_NULL(var);
    TEST_ASSERT_EQUAL_STRING("hello", var);
    url_router_dict_free(args);

    // insert /a/b/c/:foo/e/:bar
    err = url_tree_insert(&tree, "/a/b/c/:foo/e/:bar", 18, (void *)2);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    // /a/b/c/d/e/f should match /a/b/c/:foo/e/:bar
    err = url_tree_match(&tree, "/a/b/c/d/e/f", 12, &args, (void **)&data);
    TEST_ASSERT_EQUAL_INT(2, data);

    char *foo = dict_get(args, "foo");
    TEST_ASSERT_NOT_NULL(foo);
    TEST_ASSERT_EQUAL_STRING("d", foo);
    char *bar = dict_get(args, "bar");
    TEST_ASSERT_NOT_NULL(bar);
    TEST_ASSERT_EQUAL_STRING("f", bar);
    url_router_dict_free(args);

    url_tree_destroy(&tree);
}

int main(int argc, char *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_url_tree_insert_match_no_arg);
    RUN_TEST(test_url_tree_insert_match_with_args);
    UNITY_END();
    return 0;
}
