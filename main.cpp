//
// Created by daniel on 29/10/15.
//
#include <iostream>
#include <vector>

#include "main.h"

using namespace std;

int convert_2d_index(int i, int j);

int main(){
    int N;
    int num_edges;
    int size = (N-1)*N/2;
    vector<bool> matrix;
    matrix.reserve(size);
    cin >> N >> num_edges;
    for (int i=0; i<num_edges; i++){

    }
    return 0;
}

int convert_2d_index(int i, int j, int N){
    if(j > N/2){
        int tmp = i;
        i = j;
        j = tmp;
    }
    int index_complete_matrix_1D = (i*(i-1))/2 + j;
    return index_complete_matrix_1D;
}