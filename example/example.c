#include <stdio.h>
#include "url_router.h"

int main(int argc, char *argv[])
{
	char *str1 = "hello world";
	char *str2 = "woooooooooo";
	char *data;

	URL_ROUTER_ERROR err;
	Args *args;
	UrlRouter *r = url_router_new();

	err = url_router_insert(r, "/a/b/c", str1);
	if (err != URL_ROUTER_E_OK) {
		printf("Insert /a/b/c failed\n");
		return -1;
	}

	err = url_router_match(r, "/a/b/c", &args, (void **) &data);
	if (err == URL_ROUTER_E_OK) {
		printf("%s\n", data);
	}
	url_router_args_free(args);

	err = url_router_insert(r, "/r/:var/c", str2);
	if (err != URL_ROUTER_E_OK) {
		printf("Insert /r/:var/c failed\n");
		return -1;
	}

	err = url_router_match(r, "/r/b/c", &args, (void **) &data);
	if (err == URL_ROUTER_E_OK) {
		const char *arg;
		int len;
		if (url_router_args_get(args, "var", 3, &arg, &len)) {
		}
		printf("%s\n", data);
	}
	url_router_args_free(args);

	printf("Done\n");
	return 0;
}
