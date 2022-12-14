#define MAX_LENGTH 150
#define SYMBOLS "0123456789ABCDEF"
#define MAX_POW_2 (MAX_LENGTH*4)  // mnożnik to log2(MAX_BASE) - w tym przypadku log2(16) = 4

int symbol_to_value(char, int);

void values_to_symbols(int*, char*);

int convert_bases(FILE*, int, int, int*);
