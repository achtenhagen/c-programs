
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define N 1048576
#define NELM 10
#define BIN 256
#define MAXBIT 32
#define LST 1
#define BUF 0

int n,group,bin;
int flag;
int lst[N],buf[N];
int count[BIN],map[BIN],tmap[BIN];

void initialize();
void radix_sort();
void print_lst();
void self_check();

int main(int argc, char *argv[]) {
	int i;
	flag = LST;
	group = 8;
	n = NELM;
	initialize();
	for (i = 0; i < MAXBIT; i += group) {
		radix_sort(i);
	}
	print_lst(lst, n);
	self_check(lst, n);
	return 0;
}

void initialize() {
	srand(1234);
	for (int i = 0; i < n; i++) {
		lst[i] = rand();
	}
}

// fix the bucket size to 256. run 4 passes where each pass processes 8 bits
// use lst and buf only. do not use any more memory of size n.
void radix_sort(int idx) {
	int i,j,k,mask;
	int *src_p, *dst_p;
	mask = BIN - 1;
	if (flag == LST) {
		src_p = lst;
		dst_p = buf;
	} else {
		src_p = buf;
		dst_p = lst;
	}
	
	/* count */
	
	for (i = 0; i < BIN; i++) {
		count[(src_p[i] >> (idx*8))&mask]++;
	}
	
	/* map */
	
	map[0] = 0;
	for (j = 1; j < BIN; j++) {
		map[j] = map[j-1] + count[j-1];
	}
	
	/* move */
	
	for (k = 0; k < N; k++) {
		dst_p[map[(src_p[k] >> (idx*8))&mask]++] = src_p[k];
	}
}

void print_lst(int *l, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ",l[i]);
	}
	printf("\n");
}

void self_check(int *list, int n) {
	int i,j,flag=OK,*listp;
	listp = list;
	for (i = 0; i < n - 1; i++) {
		if (listp[i] > listp[i+1]) {
			flag = NOK; break;
		}
	}
	if (flag == OK) printf("sorted\n");
	else printf("NOT sorted at %d\n",i);
}
