
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

int main(int argc, char *argv[]) {
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
	int vector_x[n], vector_y[n];
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
	
	MPI_Scatter(vector_x, size, MPI_INT, vector_x + sidx, size, MPI_INT, MASTER, world);
	MPI_Scatter(vector_y, size, MPI_INT, vector_y + sidx, size, MPI_INT, MASTER, world);
	
	prod = dot_product(sidx, eidx, vector_x, vector_y);
	etime = MPI_Wtime();
		
	MPI_Gather(&prod, 1, MPI_INT, lst_prod, 1, MPI_INT, MASTER, world);
	
	if (pid == MASTER) {
		for (i = 0; i < nprocs; i++) {
			prod = lst_prod[i] + prod;
		}
	}
	printf("pid=%d: final prod=%d\n", pid, prod);
	printf("pid=%d: elapsed=%f\n", pid, etime-stime);
	MPI_Finalize();
}

int dot_product(int s, int e, int *vector_x, int *vector_y) {
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
