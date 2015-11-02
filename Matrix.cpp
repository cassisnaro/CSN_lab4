//
// Created by daniel on 2/11/15.
//

#include <thread>
#include "Matrix.h"

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