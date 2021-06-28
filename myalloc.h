#ifndef _MYMALLOC_H
#define _MYMALLOC_H

#include <stddef.h>

#define BIG_SIZE (size_t)(1 << 10) // 1024 bytes

struct metadata {
	size_t size;
	unsigned char is_free;

	struct metadata *next;
};

void* myalloc(size_t size);
void myfree(void *ptr);


#endif /* _MYMALLOC_H */
