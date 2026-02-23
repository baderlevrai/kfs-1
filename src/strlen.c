#include "kernel.h"

size_t	strlen(const char* str)
{
	size_t len = 0;
	if (!str)
		return 0;
	while (str[len])
		len++;
	return len;
}