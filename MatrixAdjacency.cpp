//
// Created by daniel on 7/11/15.
//

#include <thread>
#include "MatrixAdjacency.h"
#include <random>

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

void MatrixAdjacency::setIsEdge(ID_TYPE i, ID_TYPE j,bool isEdge){
    if (isEdge) {
        matrix[i].insert(j);
        matrix[j].insert(i);
    } else{
        matrix[i].erase(j);
        matrix[j].erase(i);
    }
}

void MatrixAdjacency::setExample() {
    std::cerr<<"insert 0 edge\n";
    setIsEdge(0,2,true);
    std::cerr<<"insert 1 edge\n";
    setIsEdge(0,3,true);
    std::cerr<<"insert 1 edge\n";
    setIsEdge(2,4,true);
    std::cerr<<"insert 1 edge\n";
    setIsEdge(3,4,true);
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


int ErdosRenyiAuxStarterFunction(MatrixAdjacency* matrix, unsigned long first_index, unsigned long next_first_index, double prob){
    matrix->ErdosRenyiAuxFunction(first_index,next_first_index,prob);
    return 0;
}
void MatrixAdjacency::ErdosRenyiAuxFunction(ID_TYPE first_index, ID_TYPE next_first_index, double prob){
    for(ID_TYPE i=first_index; i < next_first_index; i++){
        for(ID_TYPE j=i+1; j < N; j++) {
            if (drand48() < prob) setIsEdge(i,j,true);
        }
    }
    return;
}

MatrixAdjacency MatrixAdjacency::ErdosRenyi(ID_TYPE num_vertices, double p, int numthreads){
    std::thread t[numthreads];
    MatrixAdjacency matrix(num_vertices);

    if (numthreads > 16) numthreads=16;
    unsigned long first_index_thread[16];
    for( int i=0; i<numthreads-1; i++){
        first_index_thread[i]=(unsigned long)i*num_vertices/(unsigned long)numthreads;
        std::cerr<<"thread "<<i<<": "<<first_index_thread[i]<<"\n";
    }
    first_index_thread[numthreads-1]=(numthreads-1)*(num_vertices/numthreads);
    for( int i=0; i<numthreads-1; i++){
        t[i]=std::thread(ErdosRenyiAuxStarterFunction,&matrix, first_index_thread[i], first_index_thread[i+1],p);
    }
    t[numthreads-1]=std::thread(ErdosRenyiAuxStarterFunction,&matrix, first_index_thread[numthreads-1], num_vertices,p);
    for( int i=0; i<numthreads; i++){
        t[i].join();
    }
    return matrix;
}

MatrixAdjacency MatrixAdjacency::randomizeEdges() {
    //Needs to be moved
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0,N-1);

    MatrixAdjacency newMatrix = *this;

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
            }
        }
        if (newMatrix.getIsEdge(edge1node1, edge1node2) &&
                newMatrix.getIsEdge(edge2node1, edge2node2)
            && !newMatrix.getIsEdge(edge1node1, edge2node2) &&
            !newMatrix.getIsEdge(edge2node1, edge1node2)) {
            newMatrix.setIsEdge(edge1node1, edge1node2,false);
            newMatrix.setIsEdge(edge2node1, edge2node2,false);
            newMatrix.setIsEdge(edge1node1, edge2node2, true);
            newMatrix.setIsEdge(edge2node1, edge1node2, true);
        }
        std::cerr << std::endl;
        newMatrix.writeToCerr();
    }
    return newMatrix;

}