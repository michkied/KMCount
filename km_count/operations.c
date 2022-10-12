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

void add(int base, int size, int *aVal, int *bVal, int *result) {
	int carry = 0;
	int i;
	for (i = size-1; i > 0; i--) {

		printf("%i. ", i - 1);
		printf("%i + %i + %i =  ", aVal[i - 1], bVal[i - 1], carry);


		if (aVal[i - 1] + bVal[i - 1] + carry <= base) {
			result[MAXLENGTH - size + i] = aVal[i - 1] + bVal[i - 1] + carry;
			carry = 0;
		}
		else {
			result[MAXLENGTH - size + i] = aVal[i - 1] + bVal[i - 1] + carry - base;
			carry++;
		}

		printf("%i\n", result[MAXLENGTH - size + i]);
	}

	if (carry) {
		result[MAXLENGTH - size] = carry;
	}
	for (i = MAXLENGTH; i > 0; i--) {
		printf("%i. %i\n", i - 1, result[i - 1]);
	}
}