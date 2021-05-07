#include "mulmat.hpp"
#include <cstdlib>
#include <iostream>
//#include <omp.h>

MulMat::MulMat(long m, long n, long k, float a, float b) {
    M = m; N = n; K = k;
    LDA = K; LDB = N; LDC = N;
    alpha = a; beta = b;
}

MulMat::~MulMat() {
}

bool MulMat::initialize() {
    A = (float*)malloc(sizeof(float) * M*K);
    B = (float*)malloc(sizeof(float) * K*N);
    C = (float*)malloc(sizeof(float) * M*N);
   
	//A = new float(N);
	//B = new float(N);
 	//C = new float(N);

    srand(time(0));
    if (A == NULL || B == NULL || C == NULL) {
        return false;
    }

    //#pragma omp parallel for simd
    for (long i = 0; i < M; i++) {
        for (long j = 0; j < LDA; j++) {
            A[i*LDA + j] = rand() % 10;
        }
    }

    //#pragma omp parallel for simd
    for (long i = 0; i < K; i++) {
        for (long j = 0; j < LDB; j++) {
            B[i*LDB + j] = rand() % 10;
        }
    }

    //#pragma omp parallel for simd
    for (long i = 0; i < M; i++) {
        for (long j = 0; j < LDC; j++) {
            C[i*LDC + j] = rand() % 10;
        }
    }
    /*
    for(int i=0; i < N*N; i++) {
	    A[i] = rand() % 10;
	    B[i] = rand() % 10;
	    C[i] = 0;
	    printf("A[%d] = %.1f B[%d]=%.1f \n", i, A[i], i, B[i]);
    }*/
    return true;
}

void MulMat::multiply() {
    cblas_sgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,M,N,K,alpha,A,LDA,B,LDB,beta,C,LDC);
}

void MulMat::vanillaMultiply() {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			C[j + (i * N)] = 0;
			for (int k=0; k<N; k++) {
				C[j + (i * N)] += A[k + (i * N)] * B[j + (k * N)];
			}
		}
	}
}


void MulMat::printResults() {
	printf ("\n");
	printf("Array A : \n");
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%.1f\t", A[j+(i*N)]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Array B : \n");
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%.1f\t", B[j+(i*N)]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Product of A and B i.e C=A*B: \n");
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			printf("%.1f\t", C[j+(i*N)]);
		}
		printf("\n");
	}
}

void MulMat::memoryFree() {
    //free(A);
    //free(B);
    //free(C);
    delete[] A;
    delete[] B;
    delete[] C;
}
