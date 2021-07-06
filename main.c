#include <stdio.h>
#include <string.h>

#include "myalloc.h"

int main(void)
{
	char *x = myalloc(10);
	strncpy(x, "ABCABCABC", 10);
	printf("--> %s\n", x);
	myfree(x);
	
	char *y = myalloc(5);
	strncpy(y, "CCCC", 5);

	char *z = myalloc(30);
	strncpy(z, "ZZZZZZZZZBBBBB", 30);

	printf(">> %s\n>> %s\n", y, z);

	myfree(y);
	myfree(z);
}
