/* Simple radix sort program
   Created by Maurice Achtenhagen on 10/30/16
*/

#define MAX_BITS 32
#define NUM_ELEMENTS 5

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// void radix_sort(int[], int, int);

int main(int argc, char **argv) {
    int list[NUM_ELEMENTS] = {56, 30, 41, 18, 25};
    int size = sizeof(list) / sizeof(list[0]);
    int group = 4; // 4 bits per pass
    int numbuckets = 1 << group;
    int count[numbuckets], map[numbuckets], move[NUM_ELEMENTS];
    int mask = numbuckets - 1;
    int iterations = MAX_BITS / group;

    return 0;
}

// void radix_sort(int list[], int size, int iterations) {}
