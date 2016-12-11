#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char **argv) {
    char str[] = "?a???b,,,#c";
    printf("%s\n", strtok(str, "?"));
    printf("%s\n", strtok(NULL, ","));
    printf("%s\n", strtok(NULL, "#,"));
    printf("\n");
    char str2[] = "a?,?b,,??c#,,";
    printf("%s\n", strtok(str2, "?"));
    printf("%s\n", strtok(NULL, "?,"));
    printf("%s\n", strtok(NULL, "?#,"));

    return 0;
}
