#include <stdio.h>
#include <stdlib.h>

void compress_files(int argc, char *argv[]) {
    int c, prev;
    int count = 0;
    int first_char = 1; // bandera para inicializar prev

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while ((c = fgetc(fp)) != EOF) {
            if (first_char) {
                prev = c;
                count = 1;
                first_char = 0;
            } else if (c == prev) {
                count++;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fputc(prev, stdout);
                prev = c;
                count = 1;
            }
        }

        fclose(fp);
    }

    // Al final, imprimir lo que quedó pendiente
    if (!first_char) {
        fwrite(&count, sizeof(int), 1, stdout);
        fputc(prev, stdout);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    compress_files(argc, argv);
    return 0;
}
