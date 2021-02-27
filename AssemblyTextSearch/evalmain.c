
#include <stdio.h>

#include "lab6.h"

int main()
{
	long G;
	long range = 0;
	char *str = "1 2 3 4 WHO are we fighting FOR?";

	for (range = 0; range <3; range++)
	{
	    G = evaluate(str, range);
printf("evalmain: %d words found using range %d on \"%s\"\n\n", G, range, str);
    	}

	return 0;
}
