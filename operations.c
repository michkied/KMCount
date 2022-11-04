#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"

int add_num = 0;


int* minVal(int* aVal, int* bVal) {
	int i;
	for (i = 0; i < MAX_LENGTH; i++) {
		if (aVal[i] == bVal[i]) continue;
		if (aVal[i] > bVal[i]) return bVal;
		if (aVal[i] < bVal[i]) return aVal;
	}
	return aVal;
}


int* maxVal(int* aVal, int* bVal) {
	int i;
	for (i = 0; i < MAX_LENGTH; i++) {
		if (aVal[i] == bVal[i]) continue;
		if (aVal[i] > bVal[i]) return aVal;
		if (aVal[i] < bVal[i]) return bVal;
	}
	return aVal;
}


int are_equal(int* aVal, int* bVal) {
	int i;
	for (i = MAX_LENGTH - 1; i >= 0; i--) {
		if (aVal[i] == bVal[i]) continue;
		else return 0;
	}
	return 1;
}


void add(int base, int *aVal, int *bVal, int *result) {

    int carry = 0;
    int i;

	if (aVal[0] + bVal[0] >= base) {
		printf("\nERROR 200: Overflow (MAX %i)\n", MAX_LENGTH);
		exit(1);
	}

	for (i = MAX_LENGTH - 1; i >= 0; i--) {
		if (aVal[i] + bVal[i] + carry < base) {
			result[i] = aVal[i] + bVal[i] + carry;
			carry = 0;
		}
		else {
			result[i] = aVal[i] + bVal[i] + carry - base;
			carry = 1;
		}
	}
	if (carry)
		result[0] = carry;

	add_num++;
}


void multiply(int base, int* aVal, int* bVal, int* result) {

	int *lVal = minVal(aVal, bVal);
	int *hVal = maxVal(aVal, bVal);
	int buf1[MAX_LENGTH] = { 0 };
    int buf2[MAX_LENGTH] = { 0 };
    int buf3[MAX_LENGTH] = { 0 };
    int buf4[MAX_LENGTH] = { 0 };
    int resultBuf[MAX_LENGTH] = { 0 };
    int powersOfVal[MAX_POW_2][MAX_LENGTH] = {{0} };
    int powersOf2[MAX_POW_2][MAX_LENGTH] = {{0} };
    int i, i2, i3;

	if (are_equal(buf1, lVal)) return;

	buf1[MAX_LENGTH - 1] = 1;
	if (are_equal(buf1, lVal)) {
		for (i = 0; i < MAX_LENGTH; i++)
			result[i] = hVal[i];
		return;
	}

	for (i = 0; i < MAX_LENGTH; i++)
		buf2[i] = hVal[i];

	powersOf2[0][MAX_LENGTH - 1] = 1;
	for (i = 0; i < MAX_LENGTH; i++)
		powersOfVal[0][i] = buf2[i];

	for (i = 1; 1; i++) {
		if (lVal == minVal(lVal, buf1)) break;

		add(base, buf1, buf1, buf1);
		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			powersOf2[i][i2] = buf1[i2];

		add(base, buf2, buf2, buf2);
		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			powersOfVal[i][i2] = buf2[i2];
	}

	for (i2 = i-1; i2 >= 0; i2--) {

		for (i3 = 0; i3 < MAX_LENGTH; i3++)
			buf1[i3] = powersOf2[i2][i3];

		for (i3 = 0; i3 < MAX_LENGTH; i3++)
			buf2[i3] = powersOfVal[i2][i3];

		add(base, buf1, buf3, buf4);

		if (minVal(buf4, lVal) == buf4) {
			add(base, buf2, resultBuf, resultBuf);
			add(base, buf1, buf3, buf3);
		}

		if (are_equal(buf4, lVal)) break;

		memset(buf4, 0, sizeof(buf4));
	}

	for (i = 0; i < MAX_LENGTH; i++)
		result[i] = resultBuf[i];
}


void exponentiate(int base, int* aVal, int* bVal, int* result) {

	int buf1[MAX_LENGTH] = { 0 };
    int buf2[MAX_LENGTH] = { 0 };
    int buf3[MAX_LENGTH] = { 0 };
    int buf4[MAX_LENGTH] = { 0 };
    int resultBuf[MAX_LENGTH] = { 0 };
    int powersOfVal[MAX_POW_2][MAX_LENGTH] = {{0} };
    int powersOf2[MAX_POW_2][MAX_LENGTH] = {{0} };
    int i, i2, i3;

	if (are_equal(buf1, bVal)) {
		result[MAX_LENGTH - 1] = 1;
		return;
	}

	buf1[MAX_LENGTH - 1] = 1;
	if (are_equal(buf1, bVal)) {
		for (i = 0; i < MAX_LENGTH; i++)
			result[i] = aVal[i];
		return;
	}

	for (i = 0; i < MAX_LENGTH; i++)
		buf2[i] = aVal[i];

	for (i = 0; 1; i++) {
		if (bVal == minVal(bVal, buf1)) break;

		add(base, buf1, buf1, buf1);
		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			powersOf2[i][i2] = buf1[i2];

		multiply(base, buf2, buf2, buf2);
		for (i2 = 0; i2 < MAX_LENGTH; i2++) {
			powersOfVal[i][i2] = buf2[i2];
		}
	}

	resultBuf[MAX_LENGTH - 1] = 1;
	for (i2 = i - 1; i2 >= 0; i2--) {

		for (i3 = 0; i3 < MAX_LENGTH; i3++)
			buf1[i3] = powersOf2[i2][i3];

		for (i3 = 0; i3 < MAX_LENGTH; i3++)
			buf2[i3] = powersOfVal[i2][i3];

		add(base, buf1, buf3, buf4);

		if (minVal(buf4, bVal) == buf4) {
			multiply(base, buf2, resultBuf, resultBuf);
			add(base, buf1, buf3, buf3);
		}

		if (are_equal(buf4, bVal)) break;

		memset(buf4, 0, sizeof(buf4));
	}

	if (!are_equal(bVal, buf3))
		multiply(base, aVal, resultBuf, resultBuf);

	for (i = 0; i < MAX_LENGTH; i++)
		result[i] = resultBuf[i];
}


void subtract(int base, int* aVal, int* bVal, int* result) {

    int buf[MAX_LENGTH] = { 0 };
    int i;

	if (minVal(bVal, aVal) == aVal) {
		printf("\nERROR 201: Subtraction argument error\n");
		exit(1);
	}

	for (i = 0; i < MAX_LENGTH; i++)
		buf[i] = aVal[i];

	for (i = MAX_LENGTH - 1; i >= 0; i--) {
		if (buf[i] < bVal[i]) {
			buf[i - 1]--;
			buf[i] += base;
		}
		result[i] = buf[i] - bVal[i];
	}
}


void divide(int base, int* aVal, int* bVal, int* result) {

	int buf1[MAX_LENGTH] = { 0 };
    int buf2[MAX_LENGTH] = { 0 };
    int buf3[MAX_LENGTH] = { 0 };
    int buf4[MAX_LENGTH] = { 0 };
    int resultBuf[MAX_LENGTH] = { 0 };
    int powersOfVal[MAX_POW_2][MAX_LENGTH] = {{0} };
    int powersOf2[MAX_POW_2][MAX_LENGTH] = {{0} };
    int i, i2, i3;

	if (are_equal(buf1, bVal)) {
		printf("\nERROR 202: Division by zero\n");
		exit(1);
	}

	if (minVal(aVal, bVal) == aVal) {
		printf("\nERROR 201: Division argument error\n");
		exit(1);
	}

	buf1[MAX_LENGTH - 1] = 1;
	if (are_equal(buf1, bVal)) {
		for (i = 0; i < MAX_LENGTH; i++)
			result[i] = aVal[i];
		return;
	}

	for (i = 0; i < MAX_LENGTH; i++)
		buf2[i] = bVal[i];

	powersOf2[0][MAX_LENGTH - 1] = 1;
	for (i = 0; i < MAX_LENGTH; i++)
		powersOfVal[0][i] = buf2[i];

	for (i = 1; 1; i++) {
		if (aVal == minVal(aVal, buf2)) break;

		add(base, buf1, buf1, buf1);
		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			powersOf2[i][i2] = buf1[i2];

		add(base, buf2, buf2, buf2);
		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			powersOfVal[i][i2] = buf2[i2];
	}

	for (i2 = i - 1; i2 >= 0; i2--) {

		for (i3 = 0; i3 < MAX_LENGTH; i3++)
			buf1[i3] = powersOf2[i2][i3];

		for (i3 = 0; i3 < MAX_LENGTH; i3++)
			buf2[i3] = powersOfVal[i2][i3];

		add(base, buf2, buf3, buf4);

		if (minVal(buf4, aVal) == buf4) {
			add(base, buf1, resultBuf, resultBuf);
			add(base, buf2, buf3, buf3);
		}

		if (are_equal(buf4, aVal))
			break;

		memset(buf4, 0, sizeof(buf4));
	}

	for (i = 0; i < MAX_LENGTH; i++)
		result[i] = resultBuf[i];
}


void mod(int base, int* aVal, int* bVal, int* result) {

	int buf1[MAX_LENGTH] = { 0 };

	if (are_equal(buf1, bVal)) {
		printf("\nERROR 202: Modulo by zero\n");
		exit(1);
	}

	if (minVal(aVal, bVal) == aVal) {
		printf("\nERROR 201: Modulo argument error\n");
		exit(1);
	}

	divide(base, aVal, bVal, result);
	multiply(base, result, bVal, result);
	subtract(base, aVal, result, result);
}
