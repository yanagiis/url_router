#ifndef API_ROUTER_MEMORY_H
#define API_ROUTER_MEMORY_H

#include <stdlib.h>

static inline void *memory_malloc(int size)
{
	if (size == 0) {
		return NULL;
	}
	return malloc(size);
}

static inline void memory_free(void *ptr)
{
	free(ptr);
}

#endif /* API_ROUTER_MEMORY_H */
