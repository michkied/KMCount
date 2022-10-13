#include <stdio.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"

int add_num = 0;

int* minVal(int* aVal, int* bVal) {
	int i;
	for (i = 0; i < MAXLENGTH; i++) {
		if (aVal[i] == bVal[i]) {
			continue;
		}
		if (aVal[i] > bVal[i]) {
			return bVal;
		}
		if (aVal[i] < bVal[i]) {
			return aVal;
		}
	}
	return aVal;
}

int* maxVal(int* aVal, int* bVal) {
	int i;
	for (i = 0; i < MAXLENGTH; i++) {
		if (aVal[i] == bVal[i]) {
			continue;
		}
		if (aVal[i] > bVal[i]) {
			return aVal;
		}
		if (aVal[i] < bVal[i]) {
			return bVal;
		}
	}
	return aVal;
}

int are_equal(int* aVal, int* bVal) {
	int i;
	for (i = MAXLENGTH-1; i > 0; i--) {
		if (aVal[i] == bVal[i]) {
			continue;
		}
		else {
			return 0;
		}
	}
	return 1;
}

void add(int base, int size, int *aVal, int *bVal, int *result) {
	int carry = 0;
	int i;

	for (i = 1; i <= size; i++) {

		if (aVal[MAXLENGTH - i] + bVal[MAXLENGTH - i] + carry < base) {
			result[MAXLENGTH - i] = aVal[MAXLENGTH - i] + bVal[MAXLENGTH - i] + carry;
			carry = 0;
		}
		else {
			result[MAXLENGTH - i] = aVal[MAXLENGTH - i] + bVal[MAXLENGTH - i] + carry - base;
			carry = 1;
		}
	}
	if (carry) {
		result[MAXLENGTH - size] = carry;
	}
	add_num++;
}

void multiply(int base, int size, int* aVal, int* bVal, int* result) {
	int* lVal = minVal(aVal, bVal);
	int* hVal = maxVal(aVal, bVal);

	int buf1[MAXLENGTH] = { 0 };
	if (are_equal(buf1, lVal)) {
		return;
	}

	buf1[MAXLENGTH-1] = 1;
	int i;
	if (are_equal(buf1, lVal)) {
		for (i = 0; i < MAXLENGTH; i++) {
			result[i] = hVal[i];
		}
		return;
	}

	int buf2[MAXLENGTH] = { 0 };
	for (i = 0; i < MAXLENGTH; i++) {
		buf2[i] = hVal[i];
	}

	int* powersOfVal[MAXPOWOF2][MAXLENGTH] = { {0} };
	int* powersOf2[MAXPOWOF2][MAXLENGTH] = { {0} };
	int i2, i3;
	for (i = 0; 1; i++) {
		add(base, MAXLENGTH, buf1, buf1, buf1);
		if (lVal == minVal(lVal, buf1)) {
			break;
		}
		else {
			for (i2 = 0; i2 < MAXLENGTH; i2++)
				powersOf2[i][i2] = buf1[i2];

			add(base, MAXLENGTH, buf2, buf2, buf2);
			for (i2 = 0; i2 < MAXLENGTH; i2++)
				powersOfVal[i][i2] = buf2[i2];
		}
	}

	int buf3[MAXLENGTH] = { 0 };
	int buf4[MAXLENGTH] = { 0 };
	for (i2 = i-1; i2 > 0; i2--) {

		for (i3 = 0; i3 < MAXLENGTH; i3++) {
			buf1[i3] = powersOf2[i2][i3];
		}

		for (i3 = 0; i3 < MAXLENGTH; i3++) {
			buf2[i3] = powersOfVal[i2][i3];
		}

		add(base, MAXLENGTH, buf1, buf3, buf4);

		if (minVal(buf4, lVal) == buf4) {
			add(base, MAXLENGTH, buf2, result, result);
			add(base, MAXLENGTH, buf1, buf3, buf3);
		}

		memset(buf4, 0, sizeof(buf4));
	}

	if (!are_equal(lVal, buf3)) {
		add(base, MAXLENGTH, hVal, result, result);
	}


	printf("\nMade %i additions\n\n", add_num);
}

