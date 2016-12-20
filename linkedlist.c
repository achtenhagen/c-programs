
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 1024

struct clip *append();
struct clip *build_a_lst();
int find_length();
char *replace();
void print_lst();
void split_line();

struct clip {
    int views;
    char *user;
    char *id;
    char *title;
    struct clip *next;
} *head;

int main(int argc, char *argv[]) {
    if (argc == 0) {
        fprintf(stderr, "usage %s file", argv[0]);
        exit(0);
    }
    int n;
    head = build_a_lst(*(argv+1));
    n = find_length(head);
    printf("%d clips\n", n);
    print_lst(head);
    return 0;
}

int find_length(struct clip *hp) {
    int count = 0;
    struct clip *cp = hp;
    while (cp) {
        count++;
        cp = cp->next;
    }
    return count;
}

struct clip *build_a_lst(char *fn) {
    FILE *fp;
    struct clip *hp = NULL;
    char *fields[4];
    char line[LINE_LENGTH];
    if (!(fp = fopen(fn, "r"))) {
        perror("Failed to open file.");
        exit(-1);
    }
    fp = fopen(fn, "r");
    while (fgets(line, sizeof(line), fp)) {
        line[strlen(line) - 1] = '\0';
        split_line(&fields, line);
        append(&hp, fields);
    }
    fclose(fp);
  return hp;
}

/* fields will have four values stored upon return */
void split_line(char **fields, char *line) {
    int i = 0;
    char *delim = ",";
    fields[i] = strtok(line, delim);
    while((fields[++i] = strtok(NULL, delim)));
}

struct clip* append(struct clip **headRef, char **fields) {
    struct clip* current = *headRef;
    struct clip* newNode = malloc(sizeof(struct clip));
    newNode->views = atoi(fields[1]);
    char* usr = malloc(strlen(fields[0]));
    strcpy(usr, fields[0]);
    newNode->user = usr;
    char* id = malloc(strlen(fields[2]));
    strcpy(id, fields[2]);
    newNode->id = id;
    char* title = malloc(strlen(fields[3]));
    strcpy(title, fields[3]);
    newNode->title = replace(title, "COMMA", ",");
    newNode->next = NULL;
    if (current == NULL) {
        *headRef = newNode;
        return *headRef;
    }
    while (current->next) { current = current->next; }
    current->next = newNode;
    return *headRef;
}

void print_lst(struct clip *hp) {
    struct clip *cp = hp;
    while (cp) {
        printf("%d, %s, %s, %s\n", cp->views, cp->user, cp->id, cp->title);
        cp = cp->next;
    }
}

char *replace(char *st, char *orig, char *repl) {
    static char buffer[LINE_LENGTH];
    char *ch;
    if (!(ch = strstr(st, orig))) { return st; }
    strncpy(buffer, st, ch-st);
    buffer[ch-st] = 0;
    sprintf(buffer+(ch-st), "%s%s", repl, ch+strlen(orig));
    return buffer;
}
