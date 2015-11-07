//
// Created by daniel on 7/11/15.
//

#ifndef CSN_LAB4_MATRIXADJACENCY_H
#define CSN_LAB4_MATRIXADJACENCY_H


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <map>
#include <sstream>
#include <unordered_set>

#define ID_TYPE int

class MatrixAdjacency {
public:
    ID_TYPE getN() const {
        return N;
    }

    void setN(ID_TYPE N) {
        MatrixAdjacency::N = N;
    }

    ID_TYPE getNum_edges() const {
        return num_edges;
    }

    void setNum_edges(ID_TYPE num_edges) {
        MatrixAdjacency::num_edges = num_edges;
    }
    MatrixAdjacency(ID_TYPE num_nodes);
    bool getIsEdge(ID_TYPE i, ID_TYPE j);
    void setIsEdge(ID_TYPE i, ID_TYPE j,bool isEdge);

private:
    ID_TYPE N;
    ID_TYPE num_edges;
    unsigned long* dist_matrix = nullptr;

private:
    std::vector<std::unordered_set<ID_TYPE> > matrix;
    std::unordered_set<ID_TYPE>& operator [](const int nIndex);
public:
    void ErdosRenyiAuxFunction(ID_TYPE first_index, ID_TYPE next_first_index, double prob);
    static MatrixAdjacency ErdosRenyi(ID_TYPE num_edges, double p, int num_threads=1);
    MatrixAdjacency randomizeEdges();
    void setExample();
    void writeToCerr();
    void writeDistancesToCerr();
    void computeDistances();
    unsigned long bfs_distance(ID_TYPE start, ID_TYPE goal);
    ~MatrixAdjacency();
};

#endif //CSN_LAB4_MATRIXADJACENCY_H
