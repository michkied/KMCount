#include <stdio.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"


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


int get_size(int* number) {
    int i;
    for (i=0;i<MAX_LENGTH;i++)
        if (number[i] != 0)
            break;
    return MAX_LENGTH-i;
}


int add(FILE* fpOut, int base, int *aVal, int *bVal, int *result) {
    int carry = 0;
    int i;

	if (aVal[0] + bVal[0] >= base) {
		fprintf(fpOut,"ERROR 200: Overflow (MAX %i)\n\n", MAX_LENGTH);
		return 1;
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
    return 0;
}


int multiply(FILE* fpOut, int base, int* aVal, int* bVal, int* result) {
	int *lVal = minVal(aVal, bVal);
	int *hVal = maxVal(aVal, bVal);
	int temp1[MAX_LENGTH] = { 0 };
    int temp2[MAX_LENGTH] = { 0 };
    int temp3[MAX_LENGTH] = { 0 };
    int temp4[MAX_LENGTH] = { 0 };
    int resultTemp[MAX_LENGTH] = { 0 };
    int powersOfVal[MAX_POW_2][MAX_LENGTH] = {{0} };
    int powersOf2[MAX_POW_2][MAX_LENGTH] = {{0} };
    int topPower, i, i2;

	if (are_equal(temp1, lVal)) return 0;

	temp1[MAX_LENGTH - 1] = 1;
	if (are_equal(temp1, lVal)) {
		for (i = 0; i < MAX_LENGTH; i++)
			result[i] = hVal[i];
		return 0;
	}

    // Ocena rozmiaru wyniku
    if (get_size(aVal) + get_size(bVal) > MAX_LENGTH) {
        fprintf(fpOut, "ERROR 200: Overflow (MAX %i)\n\n", MAX_LENGTH);
        return 1;
    }


	for (i = 0; i < MAX_LENGTH; i++)
		temp2[i] = hVal[i];

	powersOf2[0][MAX_LENGTH - 1] = 1;
	for (i = 0; i < MAX_LENGTH; i++)
		powersOfVal[0][i] = temp2[i];

	for (topPower = 1; lVal != minVal(lVal, temp1); topPower++) {
		if (add(fpOut, base, temp1, temp1, temp1)) return 1;
		for (i = 0; i < MAX_LENGTH; i++)
			powersOf2[topPower][i] = temp1[i];

		if (add(fpOut, base, temp2, temp2, temp2)) return 1;
		for (i = 0; i < MAX_LENGTH; i++)
			powersOfVal[topPower][i] = temp2[i];
	}

	for (i = topPower - 1; i >= 0; i--) {

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp1[i2] = powersOf2[i][i2];

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp2[i2] = powersOfVal[i][i2];

		if (add(fpOut, base, temp1, temp3, temp4)) return 1;

		if (minVal(temp4, lVal) == temp4) {
			if (add(fpOut, base, temp2, resultTemp, resultTemp)) return 1;
			if (add(fpOut, base, temp1, temp3, temp3)) return 1;
		}

		if (are_equal(temp4, lVal)) break;

		memset(temp4, 0, sizeof(temp4));
	}

	for (i = 0; i < MAX_LENGTH; i++)
		result[i] = resultTemp[i];
    return 0;
}


int exponentiate(FILE* fpOut, int base, int* aVal, int* bVal, int* result) {
	int temp1[MAX_LENGTH] = { 0 };
    int temp2[MAX_LENGTH] = { 0 };
    int temp3[MAX_LENGTH] = { 0 };
    int temp4[MAX_LENGTH] = { 0 };
    int resultTemp[MAX_LENGTH] = { 0 };
    int powersOfVal[MAX_POW_2][MAX_LENGTH] = {{0} };
    int powersOf2[MAX_POW_2][MAX_LENGTH] = {{0} };
    int topPower, baseMultiplier, i, i2;
    int aSize = get_size(aVal);


	if (are_equal(temp1, bVal)) {
		result[MAX_LENGTH - 1] = 1;
		return 0;
	}

	temp1[MAX_LENGTH - 1] = 1;
	if (are_equal(temp1, bVal)) {
		for (i = 0; i < MAX_LENGTH; i++)
			result[i] = aVal[i];
		return 0;
	}

    // Ocena rozmiaru wyniku
    baseMultiplier = 1;
    for (i=MAX_LENGTH-1;i>=0;i--) {
        if (bVal[i] * baseMultiplier + aSize > MAX_LENGTH) {
            fprintf(fpOut, "ERROR 200: Overflow (MAX %i)\n\n", MAX_LENGTH);
            return 1;
        }
        baseMultiplier *= base;
    }

	for (i = 0; i < MAX_LENGTH; i++)
		temp2[i] = aVal[i];

	for (topPower = 0; bVal != minVal(bVal, temp1); topPower++) {
		if (add(fpOut, base, temp1, temp1, temp1)) return 1;
		for (i = 0; i < MAX_LENGTH; i++)
			powersOf2[topPower][i] = temp1[i];

		if (multiply(fpOut, base, temp2, temp2, temp2)) return 1;
		for (i = 0; i < MAX_LENGTH; i++) {
			powersOfVal[topPower][i] = temp2[i];
		}
	}

    resultTemp[MAX_LENGTH - 1] = 1;
	for (i = topPower - 1; i >= 0; i--) {

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp1[i2] = powersOf2[i][i2];

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp2[i2] = powersOfVal[i][i2];

		if (add(fpOut, base, temp1, temp3, temp4)) return 1;

		if (minVal(temp4, bVal) == temp4) {
			if (multiply(fpOut, base, temp2, resultTemp, resultTemp)) return 1;
			if (add(fpOut, base, temp1, temp3, temp3)) return 1;
		}

		if (are_equal(temp4, bVal)) break;

		memset(temp4, 0, sizeof(temp4));
	}

	if (!are_equal(bVal, temp3))
		if (multiply(fpOut, base, aVal, resultTemp, resultTemp)) return 1;

	for (i = 0; i < MAX_LENGTH; i++)
		result[i] = resultTemp[i];
    return 0;
}


int subtract(FILE* fpOut, int base, int* aVal, int* bVal, int* result) {
    int temp[MAX_LENGTH] = { 0 };
    int i;

	if (minVal(bVal, aVal) == aVal) {
		fprintf(fpOut, "ERROR 201: Subtraction argument error\n\n");
		return 1;
	}

	for (i = 0; i < MAX_LENGTH; i++)
		temp[i] = aVal[i];

	for (i = MAX_LENGTH - 1; i >= 0; i--) {
		if (temp[i] < bVal[i]) {
			temp[i - 1]--;
			temp[i] += base;
		}
		result[i] = temp[i] - bVal[i];
	}
    return 0;
}


int divide(FILE* fpOut, int base, int* aVal, int* bVal, int* result) {
	int temp1[MAX_LENGTH] = { 0 };
    int temp2[MAX_LENGTH] = { 0 };
    int temp3[MAX_LENGTH] = { 0 };
    int temp4[MAX_LENGTH] = { 0 };
    int resultTemp[MAX_LENGTH] = { 0 };
    int powersOfVal[MAX_POW_2][MAX_LENGTH] = {{0} };
    int powersOf2[MAX_POW_2][MAX_LENGTH] = {{0} };
    int topPower, i, i2;

	if (are_equal(temp1, bVal)) {
		fprintf(fpOut,"ERROR 202: Division by zero\n\n");
		return 1;
	}

	temp1[MAX_LENGTH - 1] = 1;
	if (are_equal(temp1, bVal)) {
		for (i = 0; i < MAX_LENGTH; i++)
			result[i] = aVal[i];
		return 0;
	}

    if (are_equal(aVal, bVal)) {
        for (i = 0; i < MAX_LENGTH; i++)
            result[i] = temp1[i];
        return 0;
    }

    if (minVal(aVal, bVal) == aVal) return 0;

	for (i = 0; i < MAX_LENGTH; i++)
		temp2[i] = bVal[i];

	powersOf2[0][MAX_LENGTH - 1] = 1;
	for (i = 0; i < MAX_LENGTH; i++)
		powersOfVal[0][i] = temp2[i];

	for (topPower = 1; aVal != minVal(aVal, temp2); topPower++) {
		if (add(fpOut, base, temp1, temp1, temp1)) return 1;
		for (i = 0; i < MAX_LENGTH; i++)
			powersOf2[topPower][i] = temp1[i];

		if (add(fpOut, base, temp2, temp2, temp2)) return 1;
		for (i = 0; i < MAX_LENGTH; i++)
			powersOfVal[topPower][i] = temp2[i];
	}

	for (i = topPower - 1; i >= 0; i--) {

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp1[i2] = powersOf2[i][i2];

		for (i2 = 0; i2 < MAX_LENGTH; i2++)
			temp2[i2] = powersOfVal[i][i2];

		if (add(fpOut, base, temp2, temp3, temp4)) return 1;

		if (minVal(temp4, aVal) == temp4) {
			if (add(fpOut, base, temp1, resultTemp, resultTemp)) return 1;
			if (add(fpOut, base, temp2, temp3, temp3)) return 1;
		}

		if (are_equal(temp4, aVal))
			break;

		memset(temp4, 0, sizeof(temp4));
	}

	for (i = 0; i < MAX_LENGTH; i++)
		result[i] = resultTemp[i];
    return 0;
}


int mod(FILE* fpOut, int base, int* aVal, int* bVal, int* result) {
	int temp1[MAX_LENGTH] = { 0 };

	if (are_equal(temp1, bVal)) {
		fprintf(fpOut,"ERROR 202: Modulo by zero\n\n");
		return 1;
	}

	if (divide(fpOut, base, aVal, bVal, result)) return 1;
	if (multiply(fpOut, base, result, bVal, result)) return 1;
	if (subtract(fpOut, base, aVal, result, result)) return 1;
    return 0;
}
