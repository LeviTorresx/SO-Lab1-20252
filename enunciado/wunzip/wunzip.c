#include <stdio.h>
#include <stdlib.h>

void decompress_file(FILE *fp) {
    int count;
    char c;

    while (fread(&count, sizeof(int), 1, fp) == 1) {
        c = fgetc(fp);
        for (int i = 0; i < count; i++) {
            fputc(c, stdout);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wunzip: cannot open file\n");
            exit(1);
        }
        decompress_file(fp);
        fclose(fp);
    }

    return 0;
}
