#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

char *line = NULL;
size_t len = 0;
ssize_t read;

void cleanup() {
    free(line);
}

void print_error_and_exit(const char *msg) {
    printf("%s\n", msg);
    exit(1);
}

void search_in_stream(FILE *fp, const char *searchterm) {
    while ((read = getline(&line, &len, fp)) != -1) {
        if (strstr(line, searchterm) != NULL) {
            printf("%s", line);
        }
    }
}

void process_files(int argc, char *argv[], const char *searchterm) {
    if (argc == 2) {
        
        // rd stdin
        search_in_stream(stdin, searchterm);
        return;
    }

    // rd of files
    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            print_error_and_exit("wgrep: cannot open file");
        }
        search_in_stream(fp, searchterm);
        fclose(fp);
    }
}

int main(int argc, char *argv[]) {
    atexit(cleanup);

    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    char *searchterm = argv[1];
    process_files(argc, argv, searchterm);

    return 0;
}
