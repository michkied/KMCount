#include <stdio.h>
#include "operations.h"
#include "conversions.h"

/*char convert(int currentBase, int targetBase, char* expression) {
	
}*/


void add(int base, int size, int *aVal, int *bVal, int *result) {
	int carry = 0;
	int i;
	for (i = size-1; i > 0; i--) {
		if (aVal[i - 1] + bVal[i - 1] + carry < base) {
			result[MAXLENGTH - size + i] = aVal[i - 1] + bVal[i - 1] + carry;
			carry = 0;
		}
		else {
			result[MAXLENGTH - size + i] = aVal[i - 1] + bVal[i - 1] + carry - base;
			carry = 1;
		}
	}
	if (carry) {
		result[MAXLENGTH - size] = carry;
	}
}