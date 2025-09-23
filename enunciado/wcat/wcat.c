#include <stdio.h>
#include <stdlib.h>

// impresion
int print_file(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("wcat: cannot open file\n");
        return 1; // error
    }

    char buffer[4096]; // buffer 
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);
    return 0; // success
}


int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0; // nothing to do
    }

    for (int i = 1; i < argc; i++) {
        if (print_file(argv[i]) != 0) {
            return 1; // error
        }
    }

    return 0; // success
}
