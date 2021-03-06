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

#include "url_router/url_router.h"
#include <unity.h>

static void test_url_router_insert_match_no_arg()
{
    char *abc = "hello";
    char *data;
    URL_ROUTER_ERROR err;

    UrlRouter *r = url_router_new();
    err = url_router_insert(r, "/a/b/c", (void *)abc);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    err = url_router_match(r, "/a/b/c", NULL, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abc, data);

    err = url_router_match(r, "/a/b/d", NULL, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_NOT_FOUND, err);
    TEST_ASSERT_EQUAL_PTR(abc, data);

    url_router_free(r);
}

static void test_url_router_insert_match_mix()
{
    char *abc = "hello";
    char *data;
    struct Dict *args;
    URL_ROUTER_ERROR err;

    UrlRouter *r = url_router_new();
    err = url_router_insert(r, "/a/b/c", (void *)abc);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    err = url_router_match(r, "/a/b/c", NULL, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abc, data);

    err = url_router_insert(r, "/a/:var/d", (void *)abc);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    err = url_router_insert(r, "/a/:foo/b/:bar", (void *)abc);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    err = url_router_match(r, "/a/b/d", NULL, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abc, data);

    err = url_router_match(r, "/a/hello/b/world", &args, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abc, data);

    data = dict_get(args, "foo");
    TEST_ASSERT_EQUAL_STRING("hello", data);

    data = dict_get(args, "bar");
    TEST_ASSERT_EQUAL_STRING("world", data);

    url_router_dict_free(args);
    url_router_free(r);
}


static void test_url_router_remove_match()
{
    char *ab = "ab";
    char *abc = "abc";
    char *abcd = "abcd";
    char *abce = "abce";
    char *abcf = "abcf";
    char *data;
    URL_ROUTER_ERROR err;

    UrlRouter *r = url_router_new();

    err = url_router_insert(r, "/a/b/c", (void *)abc);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    err = url_router_insert(r, "/a/b/c/d", (void *)abcd);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    err = url_router_insert(r, "/a/b/c/e", (void *)abce);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    err = url_router_insert(r, "/a/b/c/f", (void *)abcf);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    err = url_router_insert(r, "/a/b", (void *)ab);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);

    err = url_router_remove(r, "/a/b/c", (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abc, data);

    err = url_router_remove(r, "/a/b/c", (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_NOT_FOUND, err);

    err = url_router_match(r, "/a/b/c", NULL, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_NOT_FOUND, err);

    err = url_router_match(r, "/a/b", NULL, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(ab, data);

    err = url_router_match(r, "/a/b/c/d", NULL, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abcd, data);

    err = url_router_match(r, "/a/b/c/e", NULL, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abce, data);

    err = url_router_match(r, "/a/b/c/f", NULL, (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abcf, data);

    err = url_router_remove(r, "/a/b/c/e", (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abce, data);

    err = url_router_remove(r, "/a/b/c/d", (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abcd, data);

    err = url_router_remove(r, "/a/b/c/f", (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(abcf, data);

    err = url_router_remove(r, "/a/b", (void **)&data);
    TEST_ASSERT_EQUAL(URL_ROUTER_E_OK, err);
    TEST_ASSERT_EQUAL_PTR(ab, data);

    url_router_free(r);
}

int main(int argc, char *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_url_router_insert_match_no_arg);
    RUN_TEST(test_url_router_insert_match_mix);
    RUN_TEST(test_url_router_remove_match);
    UNITY_END();
    return 0;
}
