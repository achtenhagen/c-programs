
/*
   Program takes in two command-line parameters: n and error
   command: jacobi 5 0.0001
   command: jacobi 10 0.000001
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define N 100
#define MAX_ITER 10000

int jacobi();
void init();
int convergence();
void srand();
void print_vector();
void print_equation();
void print_matrix();

float A[N][N], D[N][N], DI[N][N], R[N][N], T[N][N];
float x[N], b[N], C[N], buf[N];
int n;
float error;

int main(int argc, char *argv[]) {
    int n_iter;
    n = atoi(argv[1]); // Problem size
    error = atof(argv[2]); // Error value
    init();
    // Ax = b, A = D + R
    // Find D : Replace everything but numbers along diagonal with 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == i) {
                D[i][j] = A[i][j];
            } else {
                D[i][j] = 0;
            }
        }
    }
    // Find R : Replace all numbers along diagonal with 0
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j != i) {
                R[i][j] = A[i][j];
            } else {
                R[i][j] = 0;
            }
        }
    }
    // Find DI : Replace numbers along the diagonal with their reciprocal
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                DI[i][j] = 1 / D[i][j];
            } else {
                DI[i][j] = 0;
            }
        }
    }
    // Find T : Multiply -DI by R
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                T[i][j] += -DI[i][k] * R[k][j];
            }
        }
    }
    // Find C : Multiply DI by b
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i] += DI[i][j] * b[j];
        }
    }
    n_iter = jacobi();
    return 0;
}

// Each iteration multiples Tx+C
// Where x is the previous estimate
int jacobi() {
    int i,j,k;
    float sum;
    k = 1;
    while (!convergence(k) && k <= MAX_ITER) {
        printf("Pass %d:", k);
        for (int i = 0; i < n; i++) {
            buf[i] = 0;
            for (int j = 0; j < n; j++) {
                buf[i] += T[i][j] * x[j];
            }
        }
        for (i = 0; i < n; i++) {
            x[i] = buf[i] + C[i];
        }
        k++;
        printf("\nCurrent solution: ");
        print_vector(x);
        printf("\n");
    }
    printf("Estimated Solution: ");
    print_vector(x);
    return k;
}

// Multiply A by x
// Check if Ax-b is close to 0 or within error
int convergence(int iter) {
    int i,j,k,flag = 1;
    float y[N];
    for (int i = 0; i < N; i++) { y[i] = 0; }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    return ((fabsf(y[0] - b[0]) < error) && (fabsf(y[1] - b[1]) < error));
}

// initalize A, x0 and b
void init() {
    int i,j,k,flag=0;
    float sum;
    int seed = time(0) % 100;
    srand(seed);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            A[i][j] = rand() & 0x7;
            if (rand() & 0x1) {
                A[i][j] = -A[i][j];
            }
        }
        sum = 0;
        for (j = 0; j < n; j++) {
            if (i != j) {
                sum = sum + fabsf(A[i][j]);
            }
        }
        if (A[i][i] < sum) {
            A[i][i] = sum + A[i][i];
        }
    }
    for (i = 0; i < n; i++) {
        x[i] = 1;
    }
    srand(seed);
    for (i = 0; i < n; i++) {
        b[i] = rand() & 0x7;
        if (rand() & 0x1) {
            b[i] = -b[i];
        }
    }
    print_equation();
}

void print_equation() {
    printf("A*x=b\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%2d ", (int)(A[i][j]));
        }
        printf(" * x%d = %d\n", i, (int)(b[i]));
    }
    printf("\n");
}

void print_matrix(float m[N][N]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f  ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_vector(float *l) {
    for (int i = 0; i < n; i++) { printf("%.6f ", l[i]); }
    printf("\n");
}
