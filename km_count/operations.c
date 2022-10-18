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


void add(int base, int *aVal, int *bVal, int *result) {

	if (aVal[0] + bVal[0] >= base) {
		printf("\nERROR 200: Overflow (MAX %i)\n", MAXLENGTH);
		exit(1);
	}

	int carry = 0;
	int i;

	for (i = MAXLENGTH-1; i > 0; i--) {
		if (aVal[i] + bVal[i] + carry < base) {
			result[i] = aVal[i] + bVal[i] + carry;
			carry = 0;
		}
		else {
			result[i] = aVal[i] + bVal[i] + carry - base;
			carry = 1;
		}
	}
	if (carry) {
		result[0] = carry;
	}
	add_num++;
}


void multiply(int base, int* aVal, int* bVal, int* result) {
	int *lVal = minVal(aVal, bVal);
	int *hVal = maxVal(aVal, bVal);

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

	int *powersOfVal[MAXPOWOF2][MAXLENGTH] = { {0} };
	int *powersOf2[MAXPOWOF2][MAXLENGTH] = { {0} };
	powersOf2[0][MAXLENGTH - 1] = 1;
	for (i = 0; i < MAXLENGTH; i++) {
		powersOfVal[0][i] = buf2[i];
	}

	int i2, i3;
	for (i = 1; 1; i++) {
		if (lVal == minVal(lVal, buf1)) {
			break;
		}

		add(base, buf1, buf1, buf1);

		for (i2 = 0; i2 < MAXLENGTH; i2++)
			powersOf2[i][i2] = buf1[i2];

		add(base, buf2, buf2, buf2);
		for (i2 = 0; i2 < MAXLENGTH; i2++)
			powersOfVal[i][i2] = buf2[i2];
	}

	int buf3[MAXLENGTH] = { 0 };
	int buf4[MAXLENGTH] = { 0 };
	int resultBuf[MAXLENGTH] = { 0 };
	for (i2 = i-1; i2 >= 0; i2--) {

		for (i3 = 0; i3 < MAXLENGTH; i3++) {
			buf1[i3] = powersOf2[i2][i3];
		}

		for (i3 = 0; i3 < MAXLENGTH; i3++) {
			buf2[i3] = powersOfVal[i2][i3];
		}

		add(base, buf1, buf3, buf4);

		if (minVal(buf4, lVal) == buf4) {
			add(base, buf2, resultBuf, resultBuf);
			add(base, buf1, buf3, buf3);
		}

		if (are_equal(buf4, lVal)) {
			break;
		}

		memset(buf4, 0, sizeof(buf4));
	}

	for (i = 0; i < MAXLENGTH; i++) {
		result[i] = resultBuf[i];
	}
}


void exponentiate(int base, int* aVal, int* bVal, int* result) {

	int buf1[MAXLENGTH] = { 0 };
	if (are_equal(buf1, bVal)) {
		result[MAXLENGTH-1] = 1;
		return;
	}

	buf1[MAXLENGTH - 1] = 1;
	int i;
	if (are_equal(buf1, bVal)) {
		for (i = 0; i < MAXLENGTH; i++) {
			result[i] = aVal[i];
		}
		return;
	}

	int buf2[MAXLENGTH] = { 0 };
	for (i = 0; i < MAXLENGTH; i++) {
		buf2[i] = aVal[i];
	}

	int* powersOfVal[MAXPOWOF2][MAXLENGTH] = { {0} };
	int* powersOf2[MAXPOWOF2][MAXLENGTH] = { {0} };
	int i2, i3;
	for (i = 0; 1; i++) {
		if (bVal == minVal(bVal, buf1)) {
			break;
		}

		add(base, buf1, buf1, buf1);
		for (i2 = 0; i2 < MAXLENGTH; i2++)
			powersOf2[i][i2] = buf1[i2];

		multiply(base, buf2, buf2, buf2);
		for (i2 = 0; i2 < MAXLENGTH; i2++) {
			powersOfVal[i][i2] = buf2[i2];
		}
	}

	int buf3[MAXLENGTH] = { 0 };
	int buf4[MAXLENGTH] = { 0 };
	int resultBuf[MAXLENGTH] = { 0 };
	resultBuf[MAXLENGTH - 1] = 1;
	for (i2 = i - 1; i2 >= 0; i2--) {

		for (i3 = 0; i3 < MAXLENGTH; i3++) {
			buf1[i3] = powersOf2[i2][i3];
		}

		for (i3 = 0; i3 < MAXLENGTH; i3++) {
			buf2[i3] = powersOfVal[i2][i3];
		}

		add(base, buf1, buf3, buf4);

		if (minVal(buf4, bVal) == buf4) {
			multiply(base, buf2, resultBuf, resultBuf);
			add(base, buf1, buf3, buf3);
		}

		if (are_equal(buf4, bVal)) {
			break;
		}

		memset(buf4, 0, sizeof(buf4));
	}

	if (!are_equal(bVal, buf3)) {
		multiply(base, aVal, resultBuf, resultBuf);
	}

	for (i = 0; i < MAXLENGTH; i++) {
		result[i] = resultBuf[i];
	}
}


void subtract(int base, int* aVal, int* bVal, int* result) {

	if (minVal(aVal, bVal) == bVal) {
		printf("\nERROR 211: Subtraction argument error\n");
		exit(1);
	}

	int i;
	int buf[MAXLENGTH] = { 0 };
	for (i = 0; i < MAXLENGTH; i++) {
		buf[i] = aVal[i];
	}

	for (i = MAXLENGTH - 1; i > 0; i--) {
		if (buf[i] < bVal[i]) {
			buf[i - 1]--;
			buf[i] += base;
		}
		result[i] = buf[i] - bVal[i];
	}
}


void divide(int base, int* aVal, int* bVal, int* result) {

	int buf1[MAXLENGTH] = { 0 };
	if (are_equal(buf1, bVal)) {
		printf("\nERROR 220: Division by zero\n");
		exit(1);
	}

	if (minVal(aVal, bVal) == bVal) {
		printf("\nERROR 221: Division argument error\n");
		exit(1);
	}

	buf1[MAXLENGTH - 1] = 1;
	int i;
	if (are_equal(buf1, bVal)) {
		for (i = 0; i < MAXLENGTH; i++) {
			result[i] = aVal[i];
		}
		return;
	}

	int buf2[MAXLENGTH] = { 0 };
	for (i = 0; i < MAXLENGTH; i++) {
		buf2[i] = bVal[i];
	}

	int* powersOfVal[MAXPOWOF2][MAXLENGTH] = { {0} };
	int* powersOf2[MAXPOWOF2][MAXLENGTH] = { {0} };
	powersOf2[0][MAXLENGTH - 1] = 1;
	for (i = 0; i < MAXLENGTH; i++) {
		powersOfVal[0][i] = buf2[i];
	}

	int i2, i3;
	for (i = 1; 1; i++) {
		if (aVal == minVal(aVal, buf2)) {
			break;
		}

		add(base, buf1, buf1, buf1);

		for (i2 = 0; i2 < MAXLENGTH; i2++)
			powersOf2[i][i2] = buf1[i2];

		add(base, buf2, buf2, buf2);
		for (i2 = 0; i2 < MAXLENGTH; i2++)
			powersOfVal[i][i2] = buf2[i2];
	}

	int buf3[MAXLENGTH] = { 0 };
	int buf4[MAXLENGTH] = { 0 };
	int resultBuf[MAXLENGTH] = { 0 };
	for (i2 = i - 1; i2 >= 0; i2--) {

		for (i3 = 0; i3 < MAXLENGTH; i3++) {
			buf1[i3] = powersOf2[i2][i3];
		}

		for (i3 = 0; i3 < MAXLENGTH; i3++) {
			buf2[i3] = powersOfVal[i2][i3];
		}

		add(base, buf2, buf3, buf4);

		if (minVal(buf4, aVal) == buf4) {
			add(base, buf1, resultBuf, resultBuf);
			add(base, buf2, buf3, buf3);
		}

		if (are_equal(buf4, aVal)) {
			break;
		}

		memset(buf4, 0, sizeof(buf4));
	}

	for (i = 0; i < MAXLENGTH; i++) {
		result[i] = resultBuf[i];
	}
}


void mod(int base, int* aVal, int* bVal, int* result) {

	int buf1[MAXLENGTH] = { 0 };
	if (are_equal(buf1, bVal)) {
		printf("\nERROR 230: Modulo by zero\n");
		exit(1);
	}

	if (minVal(aVal, bVal) == bVal) {
		printf("\nERROR 231: Modulo argument error\n");
		exit(1);
	}

	divide(base, aVal, bVal, result);
	multiply(base, result, bVal, result);
	subtract(base, aVal, result, result);
}
