#define FILENAME_LEN 12
#define OPERATORS "+-*/^%"

void get_io_files(char*, FILE**, FILE**);

char get_operation(FILE*, FILE*, int*, int*, int*, int, int);

void output_result(FILE*, char*);

void skip_lines(FILE*, FILE*, int);
