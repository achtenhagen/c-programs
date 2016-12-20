
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    float f;
    char s[32]; int n=32;
    long x = *(unsigned long *)(&f);
    for (int i=0; i< n; i++) { s[n-1-i] = "01"[x&1]; x = x >> 1; }
    printf("%s\n", s);
}
