#include <stdio.h>
#include "url_router.h"

int main(int argc, char *argv[])
{
    char *str1 = "hello world";
    char *str2 = "woooooooooo";
    char *arg;
    char *data;

    URL_ROUTER_ERROR err;
    struct Dict *args;
    UrlRouter *r = url_router_new();

    err = url_router_insert(r, "/a/b/c", str1);
    if (err != URL_ROUTER_E_OK) {
        printf("Insert /a/b/c failed\n");
        return -1;
    }

    err = url_router_match(r, "/a/b/c", &args, (void **)&data);
    if (err == URL_ROUTER_E_OK) {
        printf("%s\n", data);
    }
    url_router_dict_free(args);

    err = url_router_insert(r, "/r/:var/c", str2);
    if (err != URL_ROUTER_E_OK) {
        printf("Insert /r/:var/c failed\n");
        return -1;
    }

    err = url_router_match(r, "/r/b/c", &args, (void **)&data);
    if (err == URL_ROUTER_E_OK) {
        char *var = dict_get(args, "var");
        if (var != NULL) {
            printf("Args: %s\n", var);
        }
    }
    url_router_dict_free(args);
    url_router_free(r);

    printf("Done\n");
    return 0;
}
