//
// Created by daniel on 7/11/15.
//

#include "MatrixAdjacency.h"

#define MIN(a,b) ((a)<(b)?(a):(b))

MatrixAdjacency::MatrixAdjacency(ID_TYPE num_nodes) {
    N = num_nodes;
    matrix.resize(N);
    /*matrix = (std::unordered_set<ID_TYPE>*) malloc(num_edges*sizeof(std::unordered_set<ID_TYPE>));
    for(int i=0;i<N; i++){
        matrix[i]=std::unordered_set<ID_TYPE>();
    }*/
}

MatrixAdjacency::~MatrixAdjacency() {
    //free(matrix);
}

std::unordered_set<ID_TYPE>& MatrixAdjacency::operator [](const int nIndex){
    return matrix[nIndex];
}

bool MatrixAdjacency::getIsEdge(ID_TYPE i, ID_TYPE j){
    return (matrix[i].find(j)!=matrix[i].end() ||
            matrix[j].find(i)!=matrix[j].end());
}

void MatrixAdjacency::setIsEdge(ID_TYPE i, ID_TYPE j){
    std::cerr << matrix[i].size();
    std::cerr << (matrix[i].find(j)!=matrix[i].end());
    matrix[i].insert(j);
    matrix[j].insert(i);
}

void MatrixAdjacency::setExample() {
    std::cerr<<"insert 0 edge\n";
    setIsEdge(0,2);
    std::cerr<<"insert 1 edge\n";
    setIsEdge(0,3);
    std::cerr<<"insert 1 edge\n";
    setIsEdge(2,4);
    std::cerr<<"insert 1 edge\n";
    setIsEdge(3,4);
    std::cerr<<"insert 1 edge\n";
}

void MatrixAdjacency::writeToCerr() {
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            if (i==j) std::cerr << false << " ";
            else std::cerr << getIsEdge(i,j) << " ";
        }
        std::cerr << std::endl;
    }
}

void MatrixAdjacency::writeDistancesToCerr() {
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            std::cerr << dist_matrix[i*N+j] << " ";
        }
        std::cerr << std::endl;
    }
}

void MatrixAdjacency::computeDistances() {
    dist_matrix = (unsigned long*) calloc(sizeof(unsigned long), N*N);
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            if (i==j) {
                dist_matrix[i*N+j] = 0;
            }else {
                if(getIsEdge(i,j)){
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