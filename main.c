#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "map.h"

int main(void)
{
	map m = newMapFrom(
			"hey", DUP_VAL(7), 
			"bye", DUP_VAL(8), 
			NULL, NULL
	);

	mapRemove(&m, "hey", free);
	const int *x = mapFind(m, "hey");
	if (x) {
		printf("%d\n", *x);
	}

	mapFree(m, free);
}
