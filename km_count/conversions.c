#include <stdio.h>
#include "conversions.h"

const char symbols[MAXBASE] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};

void symbols_to_values(char* expression, int* values, int size) {
	int i1, i2;
	for (i1 = 0; i1 < size; i1++) {
		for (i2 = 0; i2 < MAXBASE; i2++) {
			if (expression[i1] == symbols[i2]) {
				values[MAXLENGTH-size+i1+1] = i2;
				break;
			}
		}
	}
}

void values_to_symbols(int* values, char* resultExpression) {
	int i;
	for (i = 0; i < MAXLENGTH; i++) {
		if (values[i]) {
			resultExpression[i] = symbols[values[i]];
		}
	}
}


/*char convert_bases(int currentBase, int targetBase, char* expression) {

}*/
