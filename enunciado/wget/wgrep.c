#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }
    
    char *searchterm = argv[1];

    if (argc == 2) {
        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, stdin)) != -1) {
            if (strstr(line, searchterm) != NULL) {
                printf("%s", line);
            }
        }
        free(line);
        return 0;
    }

    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("wgrep: cannot open file\n");
            return 1;
        }

        char *line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1) {
            if (strstr(line, searchterm) != NULL) {
                printf("%s", line);
            }
        }

        free(line);
        fclose(fp);
    }

    return 0;
}
