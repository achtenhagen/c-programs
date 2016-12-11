#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void split_line();

int main (int argc, char **argv) {
    char fields[256];
    char line[] = "hello,world,this,works";
    split_line(fields, line);
    return 0;
}

void split_line(char **fields, char *line) {
    int i = 0;
    char *token, *delim;
    delim = ",";
    token = strtok(line, delim);
    while(token != NULL) {
        fields[i] = malloc(strlen(token));
        strcpy(fields[i], token);
        printf("%s\n", token);
        token = strtok(NULL, delim);
        i++;
    }
}
