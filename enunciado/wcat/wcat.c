#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        return 0; // nothing to do
    }

    for (int i = 1; i < argc; i++)
    {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            return 1; // error
        }
        char buffer[4096]; // buffer
        while (fgets(buffer, sizeof(buffer), fp) != NULL)
        {
            printf("%s", buffer);
        }
        fclose(fp);
    }

    return 0; // melo
}
