//
// Created by daniel on 2/11/15.
//

#include <thread>
#include <random>
#include "Matrix.h"

#define MIN(a,b) ((a)<(b)?(a):(b))

long Matrix::convert_2d_index(unsigned long i, unsigned long j){
    if(i > j){
        unsigned long tmp = i;
        i = j;
        j = tmp;
    }
    long index_complete_matrix_1D = i*N - i*(i+1)/2 + j-(i+1);
    return index_complete_matrix_1D;
}

void Matrix::resize(unsigned long size, bool value){
    matrix.resize(size, value);
}

std::_Bit_reference Matrix::operator [](const int nIndex){
    return matrix[nIndex];
}

int ErdosRenyiAuxStarterFunction(Matrix* matrix, unsigned long first_index, unsigned long next_first_index, double prob){
    matrix->ErdosRenyiAuxFunction(first_index,next_first_index,prob);
    return 0;
}
void Matrix::ErdosRenyiAuxFunction(unsigned long first_index, unsigned long next_first_index, double prob){
    for(unsigned long index=first_index; index < next_first_index; index++){
        matrix[index]= drand48()<prob;
    }
    return;
}

Matrix Matrix::ErdosRenyi(unsigned long size, double p, int numthreads){
    std::thread t[numthreads];
    Matrix matrix;
    matrix.matrix.resize(size);

    if (numthreads > 16) numthreads=16;
    unsigned long first_index_thread[16];
    for( int i=0; i<numthreads-1; i++){
        first_index_thread[i]=(unsigned long)i*size/(unsigned long)numthreads;
    }
    first_index_thread[numthreads-1]=(numthreads-1)*(size/numthreads);
    for( int i=0; i<numthreads-1; i++){
        t[i]=std::thread(ErdosRenyiAuxStarterFunction,&matrix, first_index_thread[i], first_index_thread[i+1],p);
    }
    t[numthreads-1]=std::thread(ErdosRenyiAuxStarterFunction,&matrix, first_index_thread[numthreads-1], size,p);
    for( int i=0; i<numthreads; i++){
        t[i].join();
    }
    return matrix;
}

Matrix Matrix::randomizeEdges() {
    //Needs to be moved
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0,N-1);

    Matrix newMatrix = *this;

    int steps=20;
    for(int i=0; i<steps; i++){
        int edge1node1 = uni(rng);
        int edge1node2 = uni(rng);
        int edge2node1 = uni(rng);
        int edge2node2 = uni(rng);

        std::cerr <<edge1node1<<"-"<<edge1node2<<";"<<edge2node1<<"-"<<edge2node2<<std::endl;

        //We do not want to have selected randomly selected loop edges
        if ((edge1node1!=edge1node2) && (edge2node1!=edge2node2)) {
            //Checking for cases leading to loops
            if ((edge1node1 == edge2node2) || (edge1node2 == edge2node1)) {

            } else {
                //Checking that both edges exist indeed
                if (newMatrix[convert_2d_index(edge1node1, edge1node2)] &&
                    newMatrix[convert_2d_index(edge2node1, edge2node2)]
                    && !newMatrix[convert_2d_index(edge1node1, edge2node2)] &&
                    !newMatrix[convert_2d_index(edge2node1, edge1node2)]) {
                    newMatrix[convert_2d_index(edge1node1, edge1node2)] = false;
                    newMatrix[convert_2d_index(edge2node1, edge2node2)] = false;
                    newMatrix[convert_2d_index(edge1node1, edge2node2)] = true;
                    newMatrix[convert_2d_index(edge2node1, edge1node2)] = true;
                }
            }
        }
        std::cerr << std::endl;
        newMatrix.writeToCerr();
    }
    return newMatrix;

}

void Matrix::setExample() {
    matrix.resize(10,false);
    N=5;
    matrix[convert_2d_index(0,2)]=true;
    matrix[convert_2d_index(0,3)]=true;
    matrix[convert_2d_index(2,4)]=true;
    matrix[convert_2d_index(3,4)]=true;
}

void Matrix::writeToCerr() {
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            if (i==j) std::cerr << false << " ";
            else std::cerr << matrix[convert_2d_index(i,j)] << " ";
        }
        std::cerr << std::endl;
    }
}

void Matrix::writeDistancesToCerr() {
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
           std::cerr << dist_matrix[i*N+j] << " ";
        }
        std::cerr << std::endl;
    }
}

void Matrix::computeDistances() {
    dist_matrix = (unsigned long *) calloc(sizeof(unsigned long), N*N);
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            if (i==j) {
                dist_matrix[i*N+j] = 0;
            }else {
                if(matrix[convert_2d_index(i,j)]){
                    dist_matrix[i*N+j] = 1;
                }else{
                    dist_matrix[i*N+j] = INTMAX_MAX;
                }
            }
        }
    }
    writeDistancesToCerr();
    std::cerr << std::endl;

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist_matrix[i*N+j] = MIN(dist_matrix[i*N+j], dist_matrix[i*N+k] + dist_matrix[k*N+j]);
            }
        }
    }
}


Matrix::~Matrix(){
    free(dist_matrix);
}