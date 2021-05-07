MAIN       := main.bin
CXX        := g++
BLASPATH   := ../opt/OpenBLAS
#BLASPATH   := /home/akhil/compilers/matrix_testing/OpenBLAS/build
CXXFLAGS   := -std=c++11 -g3 -I$(BLASPATH)/include -L$(BLASPATH)/lib
OPENMPFLAG := -fopenmp
LINK       := -lopenblas

.PHONY: all
all: main.o mulmat.o
	$(CXX) $(CXXFLAGS) $(OPENMPFLAG) -o $(MAIN) main.o mulmat.o $(LINK) -static

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(LINK)

mulmat.o: mulmat.cpp
	$(CXX) $(CXXFLAGS) $(OPENMPFLAG) -o $@ -c $< $(LINK)

.PHONY: clean
clean:
	rm -f $(MAIN)
	rm -f *.o
