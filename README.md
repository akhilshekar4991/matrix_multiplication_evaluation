# Sample code of cblas_sgemm
Written to investigate OpenBLAS's implementation.

# Usage
1. Install OpenBLAS to where you want. This following command is recommended.
```sh
make USE_OPENMP=1 CC=gcc FC=gfortran ONLY_CBLAS=1 DEBUG=1
```
1. Rewrite `Makefile` to link your OpenBLAS correctly. This directory tree is one example.
```
.
├── cblas_gemm
└── opt/OpenBLAS
```
1. `make`

