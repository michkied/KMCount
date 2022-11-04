#define MAX_BASE 16
#define MAX_LENGTH 40
#define MAX_POW_2 (MAX_LENGTH*4)  // mnożnik to log2(MAX_BASE) - w tym przypadku log2(16) = 4

int symbol_to_value(char, int, int);

void values_to_symbols(int*, char*);

void convert_bases(int, int, int*);
