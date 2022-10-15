#include <stdio.h>
#include <string.h>
#include "conversions.h"
#include "operations.h"

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


void convert_value(int targetBase, int* value) {

	if (targetBase > value[MAXLENGTH - 1]) {
		return;
	}

	int i = targetBase - 1;
	int buf[MAXLENGTH] = {0};
	int one[MAXLENGTH] = { 0 };
	buf[MAXLENGTH - 1] = targetBase - 1;
	one[MAXLENGTH - 1] = 1;

	while (value[MAXLENGTH-1] != i) {
		add(targetBase, MAXLENGTH, buf, one, buf);
		i++;
	}

	for (i = 0; i < MAXLENGTH; i++) {
		value[i] = buf[i];
	}
}


void convert_bases(int currentBase, int targetBase, int* values) {
	if (targetBase == currentBase) {
		return;
	}

	int i, i2;
	int baseRep[MAXLENGTH] = { 0 };
	baseRep[MAXLENGTH - 1] = currentBase;
	convert_value(targetBase, baseRep);

	int buf1[MAXLENGTH] = { 0 };
	int buf2[MAXLENGTH] = { 0 };
	for (i = 0; i < MAXLENGTH; i++) {
		buf2[MAXLENGTH - 1] = values[i];

		convert_value(targetBase, buf2);
		multiply(targetBase, MAXLENGTH, buf1, baseRep, buf1);
		add(targetBase, MAXLENGTH, buf1, buf2, buf1);

		memset(buf2, 0, sizeof(buf2));
	}

	for (i = 0; i < MAXLENGTH; i++) {
		values[i] = buf1[i];
	}
}
