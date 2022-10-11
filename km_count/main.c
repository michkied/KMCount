#include <stdio.h>
#include "operations.h"

int main()
{
    char a[2] = "120";
    char b[1] = "78";
    int answer = add(10, a, b);
    printf("Answer: %i", answer);
    
    return 0;
}