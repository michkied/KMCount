/*if (argv[1] == NULL) {
        printf("Error! No filename provided.");
        exit(1);
    }

printf("%s\n\n", argv[0]);


char line[5];
char filepath = argv[0];
strcat(filepath, argv[1]);
printf("%s", filepath);
getchar(); 

FILE* fptr;

if ((fptr = fopen("./test.txt", "r")) == NULL) {
    printf("Error! opening file");

    // Program exits if the file pointer returns NULL.
    exit(1);
}

fgets(line, 5, (FILE*)fptr);
printf("%s", line);

fclose(fptr);
getchar();*/