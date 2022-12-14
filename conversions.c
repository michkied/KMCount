#include <stdio.h>
#include <string.h>
#include "conversions.h"
#include "operations.h"


int symbol_to_value(char symbol, int base) {
    int i;
    if (symbol == '_' || symbol == '\n' || symbol == '\000') return -1;
    for (i = 0; i < base; i++)
        if (symbol == SYMBOLS[i]) return i;
    return -2;
}


void values_to_symbols(int* values, char* resultExpression) {
	int i;
	for (i = 0; i < MAX_LENGTH; i++)
		if (values[i])
			resultExpression[i] = SYMBOLS[values[i]];
}


int convert_value(FILE* fpOut, int targetBase, int* value) {
    int i = targetBase - 1;
    int temp[MAX_LENGTH] = { 0 };
    int one[MAX_LENGTH] = { 0 };

	if (targetBase > value[MAX_LENGTH - 1]) return 0;

	temp[MAX_LENGTH - 1] = targetBase - 1;
	one[MAX_LENGTH - 1] = 1;

	while (value[MAX_LENGTH - 1] != i) {
        if (add(fpOut, targetBase, temp, one, temp)) return 1;
		i++;
	}

	for (i = 0; i < MAX_LENGTH; i++)
		value[i] = temp[i];
    return 0;
}


int convert_bases(FILE* fpOut, int currentBase, int targetBase, int* values) {
    int i;
    int baseRep[MAX_LENGTH] = { 0 };
    int temp1[MAX_LENGTH] = { 0 };
    int temp2[MAX_LENGTH] = { 0 };

	if (targetBase == currentBase) return 0;

	baseRep[MAX_LENGTH - 1] = currentBase;
	if (convert_value(fpOut, targetBase, baseRep)) return 1;

	for (i = 0; i < MAX_LENGTH; i++) {
		temp2[MAX_LENGTH - 1] = values[i];

		if (convert_value(fpOut, targetBase, temp2)) return 1;
        if (multiply(fpOut, targetBase, temp1, baseRep, temp1)) return 1;
        if (add(fpOut, targetBase, temp1, temp2, temp1)) return 1;

		memset(temp2, 0, sizeof(temp2));
	}

	for (i = 0; i < MAX_LENGTH; i++)
		values[i] = temp1[i];
    return 0;
}
