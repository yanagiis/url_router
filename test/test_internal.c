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
