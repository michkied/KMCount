#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conversions.h"
#include "operations.h"

const char symbols[MAX_BASE] = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};


int symbol_to_value(char symbol, int base, int lineNum) {
    int i;

    if (symbol == '_' || symbol == '\n' || symbol == '\000') return -1;

    for (i = 0; i < base; i++)
        if (symbol == symbols[i]) return i;

    printf("ERROR 130: Character %c in not valid in base %i (line #%i)", symbol, base, lineNum + 1);
    exit(1);
}


void values_to_symbols(int* values, char* resultExpression) {
	int i;
	for (i = 0; i < MAX_LENGTH; i++) {
		if (values[i])
			resultExpression[i] = symbols[values[i]];
	}
}


void convert_value(int targetBase, int* value) {

    int i = targetBase - 1;
    int temp[MAX_LENGTH] = { 0 };
    int one[MAX_LENGTH] = { 0 };

	if (targetBase > value[MAX_LENGTH - 1]) return;

	temp[MAX_LENGTH - 1] = targetBase - 1;
	one[MAX_LENGTH - 1] = 1;

	while (value[MAX_LENGTH - 1] != i) {
		add(targetBase, temp, one, temp);
		i++;
	}

	for (i = 0; i < MAX_LENGTH; i++)
		value[i] = temp[i];
}


void convert_bases(int currentBase, int targetBase, int* values) {
    int i;
    int baseRep[MAX_LENGTH] = { 0 };
    int temp1[MAX_LENGTH] = { 0 };
    int temp2[MAX_LENGTH] = { 0 };

	if (targetBase == currentBase) return;

	baseRep[MAX_LENGTH - 1] = currentBase;
	convert_value(targetBase, baseRep);

	for (i = 0; i < MAX_LENGTH; i++) {
		temp2[MAX_LENGTH - 1] = values[i];

		convert_value(targetBase, temp2);
		multiply(targetBase, temp1, baseRep, temp1);
		add(targetBase, temp1, temp2, temp1);

		memset(temp2, 0, sizeof(temp2));
	}

	for (i = 0; i < MAX_LENGTH; i++)
		values[i] = temp1[i];
}
