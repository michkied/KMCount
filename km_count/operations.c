#include <stdio.h>
#include "operations.h"

#define MAXSIZE 16

char symbols[MAXSIZE] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

/*char convert(int currentBase, int targetBase, char* expression) {
	
}*/

int* translate_into_values(int *values, char *expression, int expressionSize) {
	int i1, i2;
	for (i1 = 0; i1 < expressionSize; i1++) {
		for (i2 = 0; i2 < MAXSIZE; i2++) {
			if (expression[i1] == symbols[i2]) {
				values[i1] = i2;
				break;
			}
		}
	}

	return values;
}

int add(int base, char *a, char *b) {
	char expression[4] = {'A', '3', 'F', 'D'};
	int values[sizeof(expression) / sizeof(expression[0])];
	translate_into_values(
		values,
		expression,
		sizeof(expression) / sizeof(expression[0])
	);

	/*int _ = sizeof(values) / sizeof(values[0]);
	printf("%i\n", _);

	int i;
	for (i = 0; i < sizeof(values) / sizeof(values[0]); i++) {
		printf("%i\n", values[i]);
	}*/


	
	return base;
}