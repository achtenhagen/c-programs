
#include <stdio.h>
#include <mpi.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NELMS 1000000
#define MASTER 0
#define MAXPROCS 16

int dot_product();
void init_lst();
void print_lst();

int vector_x[NELMS], vector_y[NELMS];

int main(int argc, char **argv) {
	int i, n;
	int prod, tmp_prod, sidx, eidx, size;
	int pid, nprocs;
	double stime, etime;
	MPI_Status status;
	MPI_Comm world;

	n = atoi(argv[1]);
	if (n > NELMS) {
		printf("n=%d > N=%d\n", n, NELMS);
		exit(1);
	}
	init_lst(vector_x, n);
	init_lst(vector_y, n);

	MPI_Init(&argc, &argv);
	world = MPI_COMM_WORLD;
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	
	int lst_prod[nprocs];
	for (int i = 0; i < nprocs; i++) { lst_prod[i] = 0; }
	size = n / nprocs;
	stime = MPI_Wtime();
	sidx = pid * size;
	eidx = sidx + size - 1;
	
	// printf("sidx: %d\neidx: %d\n", sidx, eidx);
	// print_lst(sidx, eidx, vector_x);
	// print_lst(sidx, eidx, vector_y);
	
	prod = dot_product(sidx, eidx);
	etime = MPI_Wtime();
	// Program will hang if Master tries to receive from itself
	// If Master = 0, start with i = 1
	if (pid == MASTER) {
		for (i = 1; i < nprocs; i++) {
			MPI_Recv(&tmp_prod, 1, MPI_INT, i, 123, world, &status);
			lst_prod[i] = tmp_prod;
		}
	} else {
		MPI_Send(&prod, 1, MPI_INT, MASTER, 123, world);
	}
	if (pid == MASTER) {
		for (i = 0; i < nprocs; i++) {
			prod = lst_prod[i] + prod;
		}		
	}
	printf("pid=%d: final prod=%d\n", pid, prod);
	printf("pid=%d: elapsed=%f\n", pid, etime-stime);
	MPI_Finalize();
}

int dot_product(int s, int e) {
	int i, prod = 0;
	for (i = s; i < e; i++) {
		prod += vector_x[i] * vector_y[i];
	}
	return prod;
}

void init_lst(int *l, int n) {
	int i;
	for (i = 0; i < n; i++) { l[i] = i; }
}

void print_lst(int s, int e, int *l) {
	int i;
	for (i = s; i < e; i++) { printf("%i ", l[i]); }
	printf("\n");
}
