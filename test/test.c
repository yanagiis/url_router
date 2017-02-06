#include "test.h"
#include <unity/unity.h>

int main(int argc, char *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_url_tree_insert_match_no_arg);
    RUN_TEST(test_url_tree_insert_match_with_args);
    UNITY_END();
    return 0;
}
