#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operations.h"
#include "conversions.h"
#include "file_handling.h"


int main(int argc, char *argv[]) {
    FILE *fpIn, *fpOut;
    int aVal[MAX_LENGTH] = { 0 };
    int bVal[MAX_LENGTH] = { 0 };
    int result[MAX_LENGTH] = { 0 };
    char resultExpression[MAX_LENGTH];
    int base, i, errNum = 0, opNum = 0;
    char opType;

    if (argc < 2) {
        printf("\nCRITICAL ERROR 100: Missing argument - input file\n");
        exit(1);
    }

    get_io_files(argv[1], &fpIn, &fpOut);

    while(1) {
        memset(resultExpression, '0', sizeof(resultExpression));
        memset(result, 0, sizeof(result));
        memset(aVal, 0, sizeof(aVal));
        memset(bVal, 0, sizeof(bVal));

        opNum++;
        opType = get_operation(fpIn, fpOut, &base, aVal, bVal, errNum, opNum);

        switch (opType) {
            case 'b':
                if (convert_bases(fpOut, base, bVal[0], aVal)) {errNum++;continue;}
                for (i = 0; i < MAX_LENGTH; i++)
                    result[i] = aVal[i];
                break;

            case '+':
                if (add(fpOut, base, aVal, bVal, result)) {errNum++;continue;}
                break;

            case '-':
                if (subtract(fpOut, base, aVal, bVal, result)) {errNum++;continue;}
                break;

            case '*' :
                if (multiply(fpOut, base, aVal, bVal, result)) {errNum++;continue;}
                break;

            case '/' :
                if (divide(fpOut, base, aVal, bVal, result)) {errNum++;continue;}
                break;

            case '^' :
                if (exponentiate(fpOut, base, aVal, bVal, result)) {errNum++;continue;}
                break;

            case '%' :
                if (mod(fpOut, base, aVal, bVal, result)) {errNum++;continue;}
                break;


            case 'E' :
                errNum++;
                continue;
            case 1:
                printf("\nFinished with %i non-critical error(s)\n", errNum);
                return 0;
            case 0:
                printf("\nFinished with no errors! :)\n");
                return 0;
        }

        values_to_symbols(result, resultExpression);
        output_result(fpOut, resultExpression);
    }
}