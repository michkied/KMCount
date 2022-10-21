#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "operations.h"

const char symbols[MAXBASE] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};


int symbol_to_value(char symbol, int base, int lineNum) {
    if (symbol == '_' || symbol == '\n' || symbol == '\000') {
        return -1;
    }

    int i;
    for (i = 0; i < base; i++) {
        if (symbol == symbols[i]) {
            return i;
        }
    }

    printf("ERROR 130: Character %c in not valid in base %i (line #%i)", symbol, base, lineNum + 1);
    exit(1);
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
		add(targetBase, buf, one, buf);
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

	int i;
	int baseRep[MAXLENGTH] = { 0 };
	baseRep[MAXLENGTH - 1] = currentBase;
	convert_value(targetBase, baseRep);

	int buf1[MAXLENGTH] = { 0 };
	int buf2[MAXLENGTH] = { 0 };
	for (i = 0; i < MAXLENGTH; i++) {
		buf2[MAXLENGTH - 1] = values[i];

		convert_value(targetBase, buf2);
		multiply(targetBase, buf1, baseRep, buf1);
		add(targetBase, buf1, buf2, buf1);

		memset(buf2, 0, sizeof(buf2));
	}

	for (i = 0; i < MAXLENGTH; i++) {
		values[i] = buf1[i];
	}
}
