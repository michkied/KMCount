#define MAXBASE 16
#define MAXLENGTH 40
#define MAXPOWOF2 (MAXLENGTH*2)  // mnożnik to podzielony na pół log2(MAXBASE) - w tym przypadku (log2(16))/2 = 2

int symbol_to_value(char, int, int);

void values_to_symbols(int*, char*);

void convert_bases(int, int, int*);
