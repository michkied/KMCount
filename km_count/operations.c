#include <stdio.h>
#include "operations.h"

char symbols[MAXBASE] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

/*char convert(int currentBase, int targetBase, char* expression) {
	
}*/

void symbols_to_values(char *expression, int *values, int size) {
	int i1, i2;
	for (i1 = 0; i1 < size; i1++) {
		for (i2 = 0; i2 < MAXBASE; i2++) {
			if (expression[i1] == symbols[i2]) {
				values[i1] = i2;
				break;
			}
		}
	}
}

int add(int base, int size, int *aVal, int *bVal) {

	/*int _ = sizeof(values) / sizeof(values[0]);
	printf("%i\n", _);*/

	int i;
	for (i = 0; i < size-1; i++) {
		if (aVal[i] != NULL) {
			printf("%i\n", aVal[i]);
		}
	}

	
	
	return base;
}