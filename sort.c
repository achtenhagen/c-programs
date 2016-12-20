
/* HW6 read cafefully and follow all the instructions/comments
   this program compiles and runs as is although it's not doing much.
   DO NOT CHANGE THE SEED. Changing seed gives a different sequence of
   numbers but we want the same numbers for comparison purposes.

   FLOATING point radix sort requires some substantial changes to this code
   float n, lst[N],tmp[N];
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define NELM 100  /* default 100 elements */
#define N 1048576 /* 2^30 or 1 meg elements  */
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
//#define N 33554432

void selection_sort();
void swap();

void merge_sort();
void msort_recursive();

void int_radix_sort();
void float_radix_sort();
void swap();
void self_check();

int rand(void);
void srand();
int rand_r();
void init_lst();
void print_lst();
void gettimeofday();

void sort();

int n, lst[N], tmp[N];

int main(int argc, char *argv[]) {
    long int del_sec, del_msec;
    struct timeval tv_s, tv_e;
    if (argc > 1) {
      n = atoi(argv[1]);
    } else {
      n = NELM;
    }
    init_lst(lst, n);
    printf("Selection sort:\n");
    clock_t begin = clock();
    selection_sort(lst, n);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f seconds\n", time_spent);
    printf("%f milliseconds\n\n", time_spent * 1000);
    printf("Merge sort:\n");
    begin = clock();
    msort_recursive(0, n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f seconds\n", time_spent);
    printf("%f milliseconds\n\n", time_spent * 1000);
    printf("Radix sort:\n");
    begin = clock();
    int_radix_sort(lst, tmp, n);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("%f seconds\n", time_spent);
    printf("%f milliseconds\n\n", time_spent * 1000);
    self_check(lst, n);

  return 0;
}

/* -- Selection Sort -- */

void selection_sort (int list[], int n) {
    int i,j;
    for (j = 0; j < n-1; j++) {
        int min = j;
        for (i = j+1; i < n; i++) {
            if (list[min] > list[i]) {
                min = i;
            }
        }
        if (min != j) {
            swap(list, j, min);
        }
    }
}

void swap (int *list, int a, int b) {
    int tmp = list[a];
    list[a] = list[b];
    list[b] = tmp;
}

/* -- Merge Sort -- */

void merge_sort (int list[], int temp[], int low, int mid, int high) {
   int l1, l2, i;
   for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
      if(list[l1] <= list[l2])
         temp[i] = list[l1++];
      else
         temp[i] = list[l2++];
   }
   while(l1 <= mid)
      temp[i++] = list[l1++];

   while(l2 <= high)
      temp[i++] = list[l2++];

   for(i = low; i <= high; i++)
      list[i] = temp[i];
}

void msort_recursive (int low, int high) {
   int mid;
   if (low < high) {
      mid = (low + high) / 2;
      msort_recursive(low, mid);
      msort_recursive(mid+1, high);
      merge_sort(lst, tmp, low, mid, high);
   } else {
      return;
   }
}

/* -- Radix Sort -- */

void int_radix_sort(int *list, int *tmp, int n) {
    int mx = list[0];
    for (int i = 1; i < n; i++) {
        if (list[i] > mx) {
            mx = list[i];
        }
    }
    for (int exp = 1; mx / exp > 0; exp *= 10) {
        int tmp[n];
        int i, count[10] = {0};
        for (i = 0; i < n; i++) {
            count[ (list[i]/exp)%10 ]++;
        }
        for (i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        for (i = n - 1; i >= 0; i--) {
            tmp[count[ (list[i]/exp)%10 ] - 1] = list[i];
            count[ (list[i]/exp)%10 ]--;
        }
        for (i = 0; i < n; i++) {
            list[i] = tmp[i];
        }
    }
}

//fix the bucket size to 256. run 4 passes where each pass processes 8 bits
//use lst and tmp only. do not use any more memory of size n.
void radix_sort(int ii) {
  int group=8;            /* 8 bits per pass (or round) */
  int bucket = 1 << group;    /* number of buckets = 256 */
  // fill here
}

void print_lst (int *l, int n) {
    int i;
    for (i = 0; i < n; i++) { printf("%d\n", l[i]); }
    printf("\n");
}

void init_lst (int *l, int n) {
    int i;
    int seed = time(0) % 100; /* seconds since 1/1/1970 */
    // printf ("seed=%d\n", seed);
    srand(1234); /* SEED */
    for (i = 0; i < n; i++) {
        l[i] = rand();
    }
}

void self_check (int *list, int n) {
    int i, j, flag=OK, *listp;
    listp = list;
    for (i = 0; i < n-1; i++) {
        if (listp[i] > listp[i+1]) {
            flag = NOK;
            break;
        }
    }
    if (flag == OK) printf("sorted\n");
    else printf("NOT sorted at %d\n",i);
}
