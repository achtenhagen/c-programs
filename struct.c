#include <stdlib.h>
#include <stdio.h>

struct x { int a,b; struct x *p,*q; };
struct y { int **a,**b; struct y **p,**q; };

int main (int argc, char **argv) {
    printf("%lu\n", sizeof(struct x)); // returns 24
    printf("%lu\n", sizeof(struct y)); // returns 32
}
