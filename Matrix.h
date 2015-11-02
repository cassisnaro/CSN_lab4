//
// Created by daniel on 2/11/15.
//

#ifndef CSN_LAB4_MATRIX_H
#define CSN_LAB4_MATRIX_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <map>
#include <sstream>

class Matrix {
public:
    unsigned long getN() const {
        return N;
    }

    void setN(unsigned long N) {
        Matrix::N = N;
    }

    unsigned long getNum_edges() const {
        return num_edges;
    }

    void setNum_edges(unsigned long num_edges) {
        Matrix::num_edges = num_edges;
    }

private:
    unsigned long N;
    unsigned long num_edges;
    std::vector<bool> matrix;
public:
    long convert_2d_index(unsigned long i, unsigned long j);
    void resize(unsigned long size, bool value);
    std::_Bit_reference operator [](const int nIndex);
};


#endif //CSN_LAB4_MATRIX_H
