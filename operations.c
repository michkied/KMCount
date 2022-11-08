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
	int temp1[MAX_LENGTH] = { 0 };
    int temp2[MAX_LENGTH] = { 0 };
    int temp3[MAX_LENGTH] = { 0 };
    int temp4[MAX_LENGTH] = { 0 };
    int resultBuf[MAX_LENGTH] = { 0 };
    int powersOfVal[MAX_POW_2][MAX_LENGTH] = {{0} };
    int powersOf2[MAX_POW_2][MAX_LENGTH] = {{0} };
    int topPower, i, i2;

	if (are_equal(temp1, lVal)) return;

	temp1[MAX_LENGTH - 1] = 1;
	if (are_equal(temp1, lVal)) {
		for (i = 0; i < MAX_LENGTH; i++)
			result[i] = hVal[i];
		return;
	}

	for (i = 0; i < MAX_LENGTH; i++)
		temp2[i] = hVal[i];

	powersOf2[0][MAX_LENGTH - 1] = 1;
	for (i = 0; i < MAX_LENGTH; i++)
		powersOfVal[0][i] = temp2[i];

	for (topPower = 1; lVal != minVal(lVal, temp1); topPower++) {
		add(base, temp1, temp1, temp1);
		for (i = 0; i < MAX_LENGTH; i++)
			powersOf2[topPower][i] = temp1[i];

		add(base, temp2, temp2, temp2);
		for (i = 0; i < MAX_LENGTH; i++)
			powersOfVal[topPower][i] = temp2[i];
	}

	for (i = topPower - 1; i >= 0; i--) {

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp1[i2] = powersOf2[i][i2];

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp2[i2] = powersOfVal[i][i2];

		add(base, temp1, temp3, temp4);

		if (minVal(temp4, lVal) == temp4) {
			add(base, temp2, resultBuf, resultBuf);
			add(base, temp1, temp3, temp3);
		}

		if (are_equal(temp4, lVal)) break;

		memset(temp4, 0, sizeof(temp4));
	}

	for (i = 0; i < MAX_LENGTH; i++)
		result[i] = resultBuf[i];
}


void exponentiate(int base, int* aVal, int* bVal, int* result) {

	int temp1[MAX_LENGTH] = { 0 };
    int temp2[MAX_LENGTH] = { 0 };
    int temp3[MAX_LENGTH] = { 0 };
    int temp4[MAX_LENGTH] = { 0 };
    int resultBuf[MAX_LENGTH] = { 0 };
    int powersOfVal[MAX_POW_2][MAX_LENGTH] = {{0} };
    int powersOf2[MAX_POW_2][MAX_LENGTH] = {{0} };
    int topPower, i, i2;

	if (are_equal(temp1, bVal)) {
		result[MAX_LENGTH - 1] = 1;
		return;
	}

	temp1[MAX_LENGTH - 1] = 1;
	if (are_equal(temp1, bVal)) {
		for (i = 0; i < MAX_LENGTH; i++)
			result[i] = aVal[i];
		return;
	}

	for (i = 0; i < MAX_LENGTH; i++)
		temp2[i] = aVal[i];

	for (topPower = 0; bVal != minVal(bVal, temp1); topPower++) {
		add(base, temp1, temp1, temp1);
		for (i = 0; i < MAX_LENGTH; i++)
			powersOf2[topPower][i] = temp1[i];

		multiply(base, temp2, temp2, temp2);
		for (i = 0; i < MAX_LENGTH; i++) {
			powersOfVal[topPower][i] = temp2[i];
		}
	}

	resultBuf[MAX_LENGTH - 1] = 1;
	for (i = topPower - 1; i >= 0; i--) {

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp1[i2] = powersOf2[i][i2];

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp2[i2] = powersOfVal[i][i2];

		add(base, temp1, temp3, temp4);

		if (minVal(temp4, bVal) == temp4) {
			multiply(base, temp2, resultBuf, resultBuf);
			add(base, temp1, temp3, temp3);
		}

		if (are_equal(temp4, bVal)) break;

		memset(temp4, 0, sizeof(temp4));
	}

	if (!are_equal(bVal, temp3))
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

	int temp1[MAX_LENGTH] = { 0 };
    int temp2[MAX_LENGTH] = { 0 };
    int temp3[MAX_LENGTH] = { 0 };
    int temp4[MAX_LENGTH] = { 0 };
    int resultBuf[MAX_LENGTH] = { 0 };
    int powersOfVal[MAX_POW_2][MAX_LENGTH] = {{0} };
    int powersOf2[MAX_POW_2][MAX_LENGTH] = {{0} };
    int topPower, i, i2;

	if (are_equal(temp1, bVal)) {
		printf("\nERROR 202: Division by zero\n");
		exit(1);
	}

	temp1[MAX_LENGTH - 1] = 1;
	if (are_equal(temp1, bVal)) {
		for (i = 0; i < MAX_LENGTH; i++)
			result[i] = aVal[i];
		return;
	}

    if (are_equal(aVal, bVal)) {
        for (i = 0; i < MAX_LENGTH; i++)
            result[i] = temp1[i];
        return;
    }

    if (minVal(aVal, bVal) == aVal) return;

	for (i = 0; i < MAX_LENGTH; i++)
		temp2[i] = bVal[i];

	powersOf2[0][MAX_LENGTH - 1] = 1;
	for (i = 0; i < MAX_LENGTH; i++)
		powersOfVal[0][i] = temp2[i];

	for (topPower = 1; aVal != minVal(aVal, temp2); topPower++) {
		add(base, temp1, temp1, temp1);
		for (i = 0; i < MAX_LENGTH; i++)
			powersOf2[topPower][i] = temp1[i];

		add(base, temp2, temp2, temp2);
		for (i = 0; i < MAX_LENGTH; i++)
			powersOfVal[topPower][i] = temp2[i];
	}

	for (i = topPower - 1; i >= 0; i--) {

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp1[i2] = powersOf2[i][i2];

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp2[i2] = powersOfVal[i][i2];

		add(base, temp2, temp3, temp4);

		if (minVal(temp4, aVal) == temp4) {
			add(base, temp1, resultBuf, resultBuf);
			add(base, temp2, temp3, temp3);
		}

		if (are_equal(temp4, aVal))
			break;

		memset(temp4, 0, sizeof(temp4));
	}

	for (topPower = 0; topPower < MAX_LENGTH; topPower++)
		result[topPower] = resultBuf[topPower];
}


void mod(int base, int* aVal, int* bVal, int* result) {

	int temp1[MAX_LENGTH] = { 0 };

	if (are_equal(temp1, bVal)) {
		printf("\nERROR 202: Modulo by zero\n");
		exit(1);
	}

	divide(base, aVal, bVal, result);
	multiply(base, result, bVal, result);
	subtract(base, aVal, result, result);
}
