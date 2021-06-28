#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <assert.h>

#include "myalloc.h"

void *head = NULL;

static struct metadata* _alloc(struct metadata *last, size_t size) {
	struct metadata *block = NULL;
	
	(size >= BIG_SIZE) ? block = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0) : NULL;
	
	if (!block) {
		block = sbrk(0);
		if (!block) return NULL;
		sbrk(size);
	}

	if (last) last->next = block;

	block->is_free = 0;
	block->next = NULL;
	block->size = size - sizeof(struct metadata);

	return block;
}

static struct metadata* find_free_block(struct metadata **last, size_t size) {
	struct metadata *curr = head;

	while (curr)
	{
		if (curr->is_free && curr->size >= size) {
			*last = curr;
			return curr;
		}
		curr = curr->next;
	}
	*last = curr;
	return curr;
}

void* myalloc(size_t size) {
	if (size <= 0) return NULL;
	struct metadata *block;
	size_t _size = size + sizeof(struct metadata);

	if (!head) {
		block = _alloc(NULL, _size);
		if (!block) return NULL;
		head = block;
	} else {
		struct metadata *last = head;
		block = find_free_block(&last, size);
		if (!block) {
			block = _alloc(last, _size);
			if (!block) return NULL;
		}
	}

	return (block+1);
}

void myfree(void *ptr)
{
	if (!ptr) return;
	
	struct metadata *block = (struct metadata*)ptr - 1;
	#ifdef NDEBUG
		printf("Freeing %p with length %zu!\n", ptr, block->size);
	#endif
	if (block->is_free == 0) block->is_free = 1;
}