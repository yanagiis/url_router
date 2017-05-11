#include <stdio.h>
#include "url_router.h"
#include "bench.h"

int main(int argc, char *argv[])
{
    float t1_wall, t2_wall;
    float t1_cpu, t2_cpu;

    UrlRouter *r = url_router_new();
    if (r == NULL) {
        fprintf(stderr, "New UrlRouter failed\n");
        return 1;
    }

    t1_cpu = cpu();

    url_router_insert(r, "/foo/bar", NULL);
    url_router_insert(r, "/foo/bar/baz", NULL);
    url_router_insert(r, "/foo/bar/qux", NULL);
    url_router_insert(r, "/foo/bar/quux", NULL);
    url_router_insert(r, "/foo/bar/corge", NULL);
    url_router_insert(r, "/foo/bar/grault", NULL);
    url_router_insert(r, "/foo/bar/garply", NULL);
    url_router_insert(r, "/foo/baz/bar", NULL);
    url_router_insert(r, "/foo/baz/qux", NULL);
    url_router_insert(r, "/foo/baz/quux", NULL);
    url_router_insert(r, "/foo/baz/corge", NULL);
    url_router_insert(r, "/foo/baz/grault", NULL);
    url_router_insert(r, "/foo/baz/garply", NULL);
    url_router_insert(r, "/foo/qux/bar", NULL);
    url_router_insert(r, "/foo/qux/baz", NULL);
    url_router_insert(r, "/foo/qux/quux", NULL);
    url_router_insert(r, "/foo/qux/corge", NULL);
    url_router_insert(r, "/foo/qux/grault", NULL);
    url_router_insert(r, "/foo/qux/garply", NULL);
    url_router_insert(r, "/foo/quux/bar", NULL);
    url_router_insert(r, "/foo/quux/baz", NULL);
    url_router_insert(r, "/foo/quux/qux", NULL);
    url_router_insert(r, "/foo/quux/corge", NULL);
    url_router_insert(r, "/foo/quux/grault", NULL);
    url_router_insert(r, "/foo/quux/garply", NULL);
    url_router_insert(r, "/foo/corge/bar", NULL);
    url_router_insert(r, "/foo/corge/baz", NULL);
    url_router_insert(r, "/foo/corge/qux", NULL);
    url_router_insert(r, "/foo/corge/quux", NULL);
    url_router_insert(r, "/foo/corge/grault", NULL);
    url_router_insert(r, "/foo/corge/garply", NULL);
    url_router_insert(r, "/foo/grault/bar", NULL);
    url_router_insert(r, "/foo/grault/baz", NULL);
    url_router_insert(r, "/foo/grault/qux", NULL);
    url_router_insert(r, "/foo/grault/quux", NULL);
    url_router_insert(r, "/foo/grault/corge", NULL);
    url_router_insert(r, "/foo/grault/garply", NULL);
    url_router_insert(r, "/foo/garply/bar", NULL);
    url_router_insert(r, "/foo/garply/baz", NULL);
    url_router_insert(r, "/foo/garply/qux", NULL);
    url_router_insert(r, "/foo/garply/quux", NULL);
    url_router_insert(r, "/foo/garply/corge", NULL);
    url_router_insert(r, "/foo/garply/grault", NULL);
    url_router_insert(r, "/bar/foo/baz", NULL);
    url_router_insert(r, "/bar/foo/qux", NULL);
    url_router_insert(r, "/bar/foo/quux", NULL);
    url_router_insert(r, "/bar/foo/corge", NULL);
    url_router_insert(r, "/bar/foo/grault", NULL);
    url_router_insert(r, "/bar/foo/garply", NULL);
    url_router_insert(r, "/bar/baz/foo", NULL);
    url_router_insert(r, "/bar/baz/qux", NULL);
    url_router_insert(r, "/bar/baz/quux", NULL);
    url_router_insert(r, "/bar/baz/corge", NULL);
    url_router_insert(r, "/bar/baz/grault", NULL);
    url_router_insert(r, "/bar/baz/garply", NULL);
    url_router_insert(r, "/bar/qux/foo", NULL);
    url_router_insert(r, "/bar/qux/baz", NULL);
    url_router_insert(r, "/bar/qux/quux", NULL);
    url_router_insert(r, "/bar/qux/corge", NULL);
    url_router_insert(r, "/bar/qux/grault", NULL);
    url_router_insert(r, "/bar/qux/garply", NULL);
    url_router_insert(r, "/bar/quux/foo", NULL);
    url_router_insert(r, "/bar/quux/baz", NULL);
    url_router_insert(r, "/bar/quux/qux", NULL);
    url_router_insert(r, "/bar/quux/corge", NULL);
    url_router_insert(r, "/bar/quux/grault", NULL);
    url_router_insert(r, "/bar/quux/garply", NULL);
    url_router_insert(r, "/bar/corge/foo", NULL);
    url_router_insert(r, "/bar/corge/baz", NULL);
    url_router_insert(r, "/bar/corge/qux", NULL);
    url_router_insert(r, "/bar/corge/quux", NULL);
    url_router_insert(r, "/bar/corge/grault", NULL);
    url_router_insert(r, "/bar/corge/garply", NULL);
    url_router_insert(r, "/bar/grault/foo", NULL);
    url_router_insert(r, "/bar/grault/baz", NULL);
    url_router_insert(r, "/bar/grault/qux", NULL);
    url_router_insert(r, "/bar/grault/quux", NULL);
    url_router_insert(r, "/bar/grault/corge", NULL);
    url_router_insert(r, "/bar/grault/garply", NULL);
    url_router_insert(r, "/bar/garply/foo", NULL);
    url_router_insert(r, "/bar/garply/baz", NULL);
    url_router_insert(r, "/bar/garply/qux", NULL);
    url_router_insert(r, "/bar/garply/quux", NULL);
    url_router_insert(r, "/bar/garply/corge", NULL);
    url_router_insert(r, "/bar/garply/grault", NULL);
    url_router_insert(r, "/baz/foo/bar", NULL);
    url_router_insert(r, "/baz/foo/qux", NULL);
    url_router_insert(r, "/baz/foo/quux", NULL);
    url_router_insert(r, "/baz/foo/corge", NULL);
    url_router_insert(r, "/baz/foo/grault", NULL);
    url_router_insert(r, "/baz/foo/garply", NULL);
    url_router_insert(r, "/baz/bar/foo", NULL);
    url_router_insert(r, "/baz/bar/qux", NULL);
    url_router_insert(r, "/baz/bar/quux", NULL);
    url_router_insert(r, "/baz/bar/corge", NULL);
    url_router_insert(r, "/baz/bar/grault", NULL);
    url_router_insert(r, "/baz/bar/garply", NULL);
    url_router_insert(r, "/baz/qux/foo", NULL);
    url_router_insert(r, "/baz/qux/bar", NULL);
    url_router_insert(r, "/baz/qux/quux", NULL);
    url_router_insert(r, "/baz/qux/corge", NULL);
    url_router_insert(r, "/baz/qux/grault", NULL);
    url_router_insert(r, "/baz/qux/garply", NULL);
    url_router_insert(r, "/baz/quux/foo", NULL);
    url_router_insert(r, "/baz/quux/bar", NULL);
    url_router_insert(r, "/baz/quux/qux", NULL);
    url_router_insert(r, "/baz/quux/corge", NULL);
    url_router_insert(r, "/baz/quux/grault", NULL);
    url_router_insert(r, "/baz/quux/garply", NULL);
    url_router_insert(r, "/baz/corge/foo", NULL);
    url_router_insert(r, "/baz/corge/bar", NULL);
    url_router_insert(r, "/baz/corge/qux", NULL);
    url_router_insert(r, "/baz/corge/quux", NULL);
    url_router_insert(r, "/baz/corge/grault", NULL);
    url_router_insert(r, "/baz/corge/garply", NULL);
    url_router_insert(r, "/baz/grault/foo", NULL);
    url_router_insert(r, "/baz/grault/bar", NULL);
    url_router_insert(r, "/baz/grault/qux", NULL);
    url_router_insert(r, "/baz/grault/quux", NULL);
    url_router_insert(r, "/baz/grault/corge", NULL);
    url_router_insert(r, "/baz/grault/garply", NULL);
    url_router_insert(r, "/baz/garply/foo", NULL);
    url_router_insert(r, "/baz/garply/bar", NULL);
    url_router_insert(r, "/baz/garply/qux", NULL);
    url_router_insert(r, "/baz/garply/quux", NULL);
    url_router_insert(r, "/baz/garply/corge", NULL);
    url_router_insert(r, "/baz/garply/grault", NULL);
    url_router_insert(r, "/qux/foo/bar", NULL);
    url_router_insert(r, "/qux/foo/baz", NULL);
    url_router_insert(r, "/qux/foo/quux", NULL);
    url_router_insert(r, "/qux/foo/corge", NULL);
    url_router_insert(r, "/qux/foo/grault", NULL);
    url_router_insert(r, "/qux/foo/garply", NULL);
    url_router_insert(r, "/qux/bar/foo", NULL);
    url_router_insert(r, "/qux/bar/baz", NULL);
    url_router_insert(r, "/qux/bar/quux", NULL);
    url_router_insert(r, "/qux/bar/corge", NULL);
    url_router_insert(r, "/qux/bar/grault", NULL);
    url_router_insert(r, "/qux/bar/garply", NULL);
    url_router_insert(r, "/qux/baz/foo", NULL);
    url_router_insert(r, "/qux/baz/bar", NULL);
    url_router_insert(r, "/qux/baz/quux", NULL);
    url_router_insert(r, "/qux/baz/corge", NULL);
    url_router_insert(r, "/qux/baz/grault", NULL);
    url_router_insert(r, "/qux/baz/garply", NULL);
    url_router_insert(r, "/qux/quux/foo", NULL);
    url_router_insert(r, "/qux/quux/bar", NULL);
    url_router_insert(r, "/qux/quux/baz", NULL);
    url_router_insert(r, "/qux/quux/corge", NULL);
    url_router_insert(r, "/qux/quux/grault", NULL);
    url_router_insert(r, "/qux/quux/garply", NULL);
    url_router_insert(r, "/qux/corge/foo", NULL);
    url_router_insert(r, "/qux/corge/bar", NULL);
    url_router_insert(r, "/qux/corge/baz", NULL);
    url_router_insert(r, "/qux/corge/quux", NULL);
    url_router_insert(r, "/qux/corge/grault", NULL);
    url_router_insert(r, "/qux/corge/garply", NULL);
    url_router_insert(r, "/qux/grault/foo", NULL);
    url_router_insert(r, "/qux/grault/bar", NULL);
    url_router_insert(r, "/qux/grault/baz", NULL);
    url_router_insert(r, "/qux/grault/quux", NULL);
    url_router_insert(r, "/qux/grault/corge", NULL);
    url_router_insert(r, "/qux/grault/garply", NULL);
    url_router_insert(r, "/qux/garply/foo", NULL);
    url_router_insert(r, "/qux/garply/bar", NULL);
    url_router_insert(r, "/qux/garply/baz", NULL);
    url_router_insert(r, "/qux/garply/quux", NULL);
    url_router_insert(r, "/qux/garply/corge", NULL);
    url_router_insert(r, "/qux/garply/grault", NULL);
    url_router_insert(r, "/quux/foo/bar", NULL);
    url_router_insert(r, "/quux/foo/baz", NULL);
    url_router_insert(r, "/quux/foo/qux", NULL);
    url_router_insert(r, "/quux/foo/corge", NULL);
    url_router_insert(r, "/quux/foo/grault", NULL);
    url_router_insert(r, "/quux/foo/garply", NULL);
    url_router_insert(r, "/quux/bar/foo", NULL);
    url_router_insert(r, "/quux/bar/baz", NULL);
    url_router_insert(r, "/quux/bar/qux", NULL);
    url_router_insert(r, "/quux/bar/corge", NULL);
    url_router_insert(r, "/quux/bar/grault", NULL);
    url_router_insert(r, "/quux/bar/garply", NULL);
    url_router_insert(r, "/quux/baz/foo", NULL);
    url_router_insert(r, "/quux/baz/bar", NULL);
    url_router_insert(r, "/quux/baz/qux", NULL);
    url_router_insert(r, "/quux/baz/corge", NULL);
    url_router_insert(r, "/quux/baz/grault", NULL);
    url_router_insert(r, "/quux/baz/garply", NULL);
    url_router_insert(r, "/quux/qux/foo", NULL);
    url_router_insert(r, "/quux/qux/bar", NULL);
    url_router_insert(r, "/quux/qux/baz", NULL);
    url_router_insert(r, "/quux/qux/corge", NULL);
    url_router_insert(r, "/quux/qux/grault", NULL);
    url_router_insert(r, "/quux/qux/garply", NULL);
    url_router_insert(r, "/quux/corge/foo", NULL);
    url_router_insert(r, "/quux/corge/bar", NULL);
    url_router_insert(r, "/quux/corge/baz", NULL);
    url_router_insert(r, "/quux/corge/qux", NULL);
    url_router_insert(r, "/quux/corge/grault", NULL);
    url_router_insert(r, "/quux/corge/garply", NULL);
    url_router_insert(r, "/quux/grault/foo", NULL);
    url_router_insert(r, "/quux/grault/bar", NULL);
    url_router_insert(r, "/quux/grault/baz", NULL);
    url_router_insert(r, "/quux/grault/qux", NULL);
    url_router_insert(r, "/quux/grault/corge", NULL);
    url_router_insert(r, "/quux/grault/garply", NULL);
    url_router_insert(r, "/quux/garply/foo", NULL);
    url_router_insert(r, "/quux/garply/bar", NULL);
    url_router_insert(r, "/quux/garply/baz", NULL);
    url_router_insert(r, "/quux/garply/qux", NULL);
    url_router_insert(r, "/quux/garply/corge", NULL);
    url_router_insert(r, "/quux/garply/grault", NULL);
    url_router_insert(r, "/corge/foo/bar", NULL);
    url_router_insert(r, "/corge/foo/baz", NULL);
    url_router_insert(r, "/corge/foo/qux", NULL);
    url_router_insert(r, "/corge/foo/quux", NULL);
    url_router_insert(r, "/corge/foo/grault", NULL);
    url_router_insert(r, "/corge/foo/garply", NULL);
    url_router_insert(r, "/corge/bar/foo", NULL);
    url_router_insert(r, "/corge/bar/baz", NULL);
    url_router_insert(r, "/corge/bar/qux", NULL);
    url_router_insert(r, "/corge/bar/quux", NULL);
    url_router_insert(r, "/corge/bar/grault", NULL);
    url_router_insert(r, "/corge/bar/garply", NULL);
    url_router_insert(r, "/corge/baz/foo", NULL);
    url_router_insert(r, "/corge/baz/bar", NULL);
    url_router_insert(r, "/corge/baz/qux", NULL);
    url_router_insert(r, "/corge/baz/quux", NULL);
    url_router_insert(r, "/corge/baz/grault", NULL);
    url_router_insert(r, "/corge/baz/garply", NULL);
    url_router_insert(r, "/corge/qux/foo", NULL);
    url_router_insert(r, "/corge/qux/bar", NULL);
    url_router_insert(r, "/corge/qux/baz", NULL);
    url_router_insert(r, "/corge/qux/quux", NULL);
    url_router_insert(r, "/corge/qux/grault", NULL);
    url_router_insert(r, "/corge/qux/garply", NULL);
    url_router_insert(r, "/corge/quux/foo", NULL);
    url_router_insert(r, "/corge/quux/bar", NULL);
    url_router_insert(r, "/corge/quux/baz", NULL);
    url_router_insert(r, "/corge/quux/qux", NULL);
    url_router_insert(r, "/corge/quux/grault", NULL);
    url_router_insert(r, "/corge/quux/garply", NULL);
    url_router_insert(r, "/corge/grault/foo", NULL);
    url_router_insert(r, "/corge/grault/bar", NULL);
    url_router_insert(r, "/corge/grault/baz", NULL);
    url_router_insert(r, "/corge/grault/qux", NULL);
    url_router_insert(r, "/corge/grault/quux", NULL);
    url_router_insert(r, "/corge/grault/garply", NULL);
    url_router_insert(r, "/corge/garply/foo", NULL);
    url_router_insert(r, "/corge/garply/bar", NULL);
    url_router_insert(r, "/corge/garply/baz", NULL);
    url_router_insert(r, "/corge/garply/qux", NULL);
    url_router_insert(r, "/corge/garply/quux", NULL);
    url_router_insert(r, "/corge/garply/grault", NULL);
    url_router_insert(r, "/grault/foo/bar", NULL);
    url_router_insert(r, "/grault/foo/baz", NULL);
    url_router_insert(r, "/grault/foo/qux", NULL);
    url_router_insert(r, "/grault/foo/quux", NULL);
    url_router_insert(r, "/grault/foo/corge", NULL);
    url_router_insert(r, "/grault/foo/garply", NULL);
    url_router_insert(r, "/grault/bar/foo", NULL);
    url_router_insert(r, "/grault/bar/baz", NULL);
    url_router_insert(r, "/grault/bar/qux", NULL);
    url_router_insert(r, "/grault/bar/quux", NULL);
    url_router_insert(r, "/grault/bar/corge", NULL);
    url_router_insert(r, "/grault/bar/garply", NULL);
    url_router_insert(r, "/grault/baz/foo", NULL);
    url_router_insert(r, "/grault/baz/bar", NULL);
    url_router_insert(r, "/grault/baz/qux", NULL);
    url_router_insert(r, "/grault/baz/quux", NULL);
    url_router_insert(r, "/grault/baz/corge", NULL);
    url_router_insert(r, "/grault/baz/garply", NULL);
    url_router_insert(r, "/grault/qux/foo", NULL);
    url_router_insert(r, "/grault/qux/bar", NULL);
    url_router_insert(r, "/grault/qux/baz", NULL);
    url_router_insert(r, "/grault/qux/quux", NULL);
    url_router_insert(r, "/grault/qux/corge", NULL);
    url_router_insert(r, "/grault/qux/garply", NULL);
    url_router_insert(r, "/grault/quux/foo", NULL);
    url_router_insert(r, "/grault/quux/bar", NULL);
    url_router_insert(r, "/grault/quux/baz", NULL);
    url_router_insert(r, "/grault/quux/qux", NULL);
    url_router_insert(r, "/grault/quux/corge", NULL);
    url_router_insert(r, "/grault/quux/garply", NULL);
    url_router_insert(r, "/grault/corge/foo", NULL);
    url_router_insert(r, "/grault/corge/bar", NULL);
    url_router_insert(r, "/grault/corge/baz", NULL);
    url_router_insert(r, "/grault/corge/qux", NULL);
    url_router_insert(r, "/grault/corge/quux", NULL);
    url_router_insert(r, "/grault/corge/garply", NULL);
    url_router_insert(r, "/grault/garply/foo", NULL);
    url_router_insert(r, "/grault/garply/bar", NULL);
    url_router_insert(r, "/grault/garply/baz", NULL);
    url_router_insert(r, "/grault/garply/qux", NULL);
    url_router_insert(r, "/grault/garply/quux", NULL);
    url_router_insert(r, "/grault/garply/corge", NULL);
    url_router_insert(r, "/garply/foo/bar", NULL);
    url_router_insert(r, "/garply/foo/baz", NULL);
    url_router_insert(r, "/garply/foo/qux", NULL);
    url_router_insert(r, "/garply/foo/quux", NULL);
    url_router_insert(r, "/garply/foo/corge", NULL);
    url_router_insert(r, "/garply/foo/grault", NULL);
    url_router_insert(r, "/garply/bar/foo", NULL);
    url_router_insert(r, "/garply/bar/baz", NULL);
    url_router_insert(r, "/garply/bar/qux", NULL);
    url_router_insert(r, "/garply/bar/quux", NULL);
    url_router_insert(r, "/garply/bar/corge", NULL);
    url_router_insert(r, "/garply/bar/grault", NULL);
    url_router_insert(r, "/garply/baz/foo", NULL);
    url_router_insert(r, "/garply/baz/bar", NULL);
    url_router_insert(r, "/garply/baz/qux", NULL);
    url_router_insert(r, "/garply/baz/quux", NULL);
    url_router_insert(r, "/garply/baz/corge", NULL);
    url_router_insert(r, "/garply/baz/grault", NULL);
    url_router_insert(r, "/garply/qux/foo", NULL);
    url_router_insert(r, "/garply/qux/bar", NULL);
    url_router_insert(r, "/garply/qux/baz", NULL);
    url_router_insert(r, "/garply/qux/quux", NULL);
    url_router_insert(r, "/garply/qux/corge", NULL);
    url_router_insert(r, "/garply/qux/grault", NULL);
    url_router_insert(r, "/garply/quux/foo", NULL);
    url_router_insert(r, "/garply/quux/bar", NULL);
    url_router_insert(r, "/garply/quux/baz", NULL);
    url_router_insert(r, "/garply/quux/qux", NULL);
    url_router_insert(r, "/garply/quux/corge", NULL);
    url_router_insert(r, "/garply/quux/grault", NULL);
    url_router_insert(r, "/garply/corge/foo", NULL);
    url_router_insert(r, "/garply/corge/bar", NULL);
    url_router_insert(r, "/garply/corge/baz", NULL);
    url_router_insert(r, "/garply/corge/qux", NULL);
    url_router_insert(r, "/garply/corge/quux", NULL);
    url_router_insert(r, "/garply/corge/grault", NULL);
    url_router_insert(r, "/garply/grault/foo", NULL);
    url_router_insert(r, "/garply/grault/bar", NULL);
    url_router_insert(r, "/garply/grault/baz", NULL);
    url_router_insert(r, "/garply/grault/qux", NULL);
    url_router_insert(r, "/garply/grault/quux", NULL);
    url_router_insert(r, "/garply/grault/corge", NULL);

    t2_cpu = cpu();
    printf("Insert time (cpu) %f\n", t2_cpu - t1_cpu);

    void *ptr;

    t1_cpu = cpu();
    url_router_match(r, "/garply/corge/qux", NULL, &ptr);
    t2_cpu = cpu();

    printf("Match time (cpu) %f\n", t2_cpu - t1_cpu);

    url_router_free(r);
    return 0;
}