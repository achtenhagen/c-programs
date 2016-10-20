#include <stdio.h>
#include <string.h>

void printsep(char *address) {
    if (address) {
        printf("\t+------+------+------+------+ %s\n", address);
    } else {
        printf("\t+------+------+------+------+\n");
    }
}

int main (int argc, char **argv) {

    printsep("0xFFFFFFFF");
    printsep(0);
    printsep(0);
    printsep(0);

    for (int i = 0; i < argc; i++) {
        for (int j = 0; j < strlen(argv[i]); j++) {
            printf("\t|\t%p\t    | %p\n", &argv[i][j], &argv[i][j]);
            printsep(0);
        }
    }

    printsep(0);
    printsep(0);
    printsep(0);

    for (int i = 0; i < argc; i++) {
        printf("argv+%d  |\t%p\t    | %p\n", (argc-1) - i, argv[i], &argv[i]);
        printsep(0);
    }

    printsep(0);
    printsep(0);
    printsep(0);
    printf("argv    |\t%p\t    | %p\n", argv, &argv);
    printf("argc    |--00--+--00--+--00--+--0%d--|\n", argc);
    printsep(0);
    printsep(0);
    printsep(0);
    printsep("0x00000000");

    return 0;
}
