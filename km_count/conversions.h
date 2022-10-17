#define MAXBASE 16
#define MAXLENGTH 40
#define MAXPOWOF2 MAXLENGTH*2  // mno¿nik to podzielony na pó³ log2(MAXBASE) - w tym przypadku (log2(16))/2 = 2

void symbols_to_values(char*, int*, int);

void values_to_symbols(int*, char*);

void convert_bases(int, int, int*);
