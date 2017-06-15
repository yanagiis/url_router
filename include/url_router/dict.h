#ifndef DICT_H
#define DICT_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

struct Dict;
struct DictIterator;

struct Dict *dict_new();
void *dict_get(struct Dict *dict, const char *key);
void *dict_getl(struct Dict *dict, const char *key, int len);
bool dict_add(struct Dict *dict, const char *key, void *value);
bool dict_addl(struct Dict *dict, const char *key, int len, void *value);
void *dict_del(struct Dict *dict, const char *key);
void *dict_dell(struct Dict *dict, const char *key, int len);
void dict_free(struct Dict *dict, void (*free_value_cb)(void *));

struct DictIterator *dict_iter_new(struct Dict *dict);
int dict_iter_next(struct DictIterator *it, const char **key, void **value);
int dict_iter_nextl(struct DictIterator *it, const char **key, int *keylen, void **value);
void dict_iter_free(struct DictIterator *it);

#ifdef __cplusplus
}
#endif

#endif /* DICT_H */

