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

#include "arg_list.c"
#include "url_tree.c"
#include <unity/unity.h>

#define STR(s, v)              \
    do {                       \
        s.str = v;             \
        s.len = sizeof(v) - 1; \
    } while (0)

static void test_url_create_edges()
{
    UrlEdge *e;
    String s;

    int data1 = 0;
    int data2 = 0;
    int data3 = 0;
    STR(s, "/a");
    e = url_create_edges(&s, (void *)&data1);
    TEST_ASSERT_NOT_NULL(e);
    TEST_ASSERT_EQUAL_PTR(&data1, e->node.data);
    TEST_ASSERT_EQUAL_INT(1, e->len);
    TEST_ASSERT_EQUAL_STRING_LEN("a", e->label, 1);
    _url_tree_destroy(&e->node);
    url_edge_free(e);

    STR(s, "/a/b");
    e = url_create_edges(&s, (void *)&data2);
    TEST_ASSERT_NOT_NULL(e);
    TEST_ASSERT_EQUAL_INT(1, e->len);
    TEST_ASSERT_EQUAL_STRING_LEN("a", e->label, 1);
    TEST_ASSERT_EQUAL_PTR(&data2, e->node.begin->node.data);
    TEST_ASSERT_EQUAL_INT(1, (int)e->node.begin->len);
    TEST_ASSERT_EQUAL_STRING_LEN("b", e->node.begin->label, 1);
    _url_tree_destroy(&e->node);
    url_edge_free(e);

    STR(s, "/a/b/c");
    e = url_create_edges(&s, (void *)&data3);
    TEST_ASSERT_NOT_NULL(e);
    TEST_ASSERT_EQUAL_INT(1, e->len);
    TEST_ASSERT_EQUAL_STRING_LEN("a", e->label, 1);

    TEST_ASSERT_EQUAL_INT(1, (int)e->node.begin->len);
    TEST_ASSERT_EQUAL_STRING_LEN("b", e->node.begin->label, 1);

    TEST_ASSERT_EQUAL_INT(1, (int)e->node.begin->node.begin->len);
    TEST_ASSERT_EQUAL_STRING_LEN("c", e->node.begin->node.begin->label, 1);
    TEST_ASSERT_EQUAL_PTR(&data3, e->node.begin->node.begin->node.data);
    _url_tree_destroy(&e->node);
    url_edge_free(e);
}

int main(int argc, char *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_url_create_edges);
    UNITY_END();
    return 0;
}
