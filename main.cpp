#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/time.h>
#include <sys/types.h>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <ctime>

#include "mulmat.hpp"

uint64_t getus() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1E6 + tv.tv_usec;
}

uint64_t temp_t;
void printTime(void) {
    uint64_t end_t = getus();
    //std::cout << std::setw(8) << (temp_t - end_t) << " [us]" << std::endl;
    std::cout << "Duration of this operation is "<< (end_t - temp_t) << " [us]" << std::endl;
    temp_t = end_t;
}

int main(int argc, char* argv[]) {
    if(argc != 2 && argc != 4) {
        std::cout << "usage: ./a.out N or ./a.out M N K" << std::endl;
        return 1;
    }

    std::string::size_type sz = 0;
    std::string str;
    long M, N, K;
    if (argc == 2) {
        str = std::string(argv[1]);
        N = std::stol(str, &sz, 0);
        M = K = N;
    } else if (argc == 4){
        str = std::string(argv[1]);
        M = std::stol(str, &sz, 0);
        str = std::string(argv[2]);
        N = std::stol(str, &sz, 0);
        str = std::string(argv[3]);
        K = std::stol(str, &sz, 0);
    }

    std::cout << "(M,N,K)=(" << M << "," << N << "," << K << ")" << std::endl;

    temp_t = getus();

    float alpha=1.0, beta=0;
    //alpha = beta = 2.0;

    std::cout << std::endl; 

    std::cout << "constructor : ";
    MulMat mm(M, N, K, alpha, beta);
    printTime();
    std::cout << std::endl; 

    std::cout << "initialize  : ";
    mm.initialize();
    printTime();
    std::cout << std::endl; 

    /*
    std::cout << "Printing Results : ";
    mm.printResults();
    std::cout << "Duration of printing operation : ";
    printTime();
    std::cout << std::endl; 
    */

    std::cout << "cblas_sgemm : ";
    mm.multiply();
    printTime();
    std::cout << std::endl; 

    /*
    std::cout << "Printing Results : ";
    mm.printResults();
    std::cout << "Duration of printing operation : ";
    printTime();
    std::cout << std::endl; 

    std::cout << "initialize  : ";
    mm.initialize();
    printTime();
    std::cout << std::endl; 
	*/

    std::cout << "Vanilla Matrix Multiplication : ";
    mm.vanillaMultiply();
    printTime();
    std::cout << std::endl; 

    /*
    std::cout << "Printing Results : ";
    mm.printResults();
    std::cout << "Duration of printing operation : ";
    printTime();
    std::cout << std::endl; 
    */

    std::cout << "memoryFree  : ";
    mm.memoryFree();
    printTime();
    std::cout << std::endl; 

    return 0;
}
