//
// Created by daniel on 2/11/15.
//

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