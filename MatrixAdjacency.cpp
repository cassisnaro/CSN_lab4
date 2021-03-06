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
        num_edges++;
    } else{
        matrix[i].erase(j);
        matrix[j].erase(i);
        num_edges--;
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
    std::cerr<<"[";
    for(int i=0;i<N;i++){
        std::cerr<<"[";
        for(int j=0; j<N; j++){
            std::cerr <<getIsEdge(i,j);
            if(j!=N-1) std::cerr << ", ";
        }
        std::cerr << "]";
        if(i!=N-1) std::cerr << ";";
    }
    std::cerr<"]";
}

void MatrixAdjacency::writeDistancesToCerr() {
    std::cerr<<"[";
    for(int i=0;i<N;i++){
        std::cerr<<"[";
        for(int j=0; j<N; j++){
            std::cerr << dist_matrix[i*N+j] << ", ";
        }
        std::cerr << "]";
        if(i!=N-1) std::cerr << ";";
    }
}

void MatrixAdjacency::computeDistances() {
    dist_matrix = (int*) calloc(sizeof(int), N*N);
    if (dist_matrix== nullptr) std::cerr<<"shit\n";
    for(int i=0;i<N;i++){
        for(int j=0; j<N; j++){
            if (i==j) {
                dist_matrix[i*N+j] = 0;
            }else {
                if(getIsEdge(i,j)){
                    dist_matrix[i*N+j] = 1;
                }else{
                    dist_matrix[i*N+j] = N*N*N;
                }
            }
        }
    }
    //writeDistancesToCerr();
    std::cerr << "initizialized"<<std::endl;

    for (int k = 0; k < N; k++) {
        if(k%100==0) std::cerr<<k<<std::endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist_matrix[i*N+j] = MIN(dist_matrix[i*N+j], dist_matrix[i*N+k] + dist_matrix[k*N+j]);
            }
        }
    }
}

ID_TYPE MatrixAdjacency::getNum_edges() const {
    return num_edges;
}

void MatrixAdjacency::setNum_edges(ID_TYPE val) {
    num_edges = val;
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

    std::cerr << "erdos renyi with num_vertices"<<num_vertices<<" p="<<p<<std::endl;

    /*if (numthreads > 16) numthreads=16;
    unsigned long first_index_thread[16];
    for( int i=0; i<numthreads-1; i++){
        first_index_thread[i]=(unsigned long)i*num_vertices/(unsigned long)numthreads;
    }
    first_index_thread[numthreads-1]=(numthreads-1)*(num_vertices/numthreads);
    for( int i=0; i<numthreads-1; i++){
        t[i]=std::thread(ErdosRenyiAuxStarterFunction,&matrix, first_index_thread[i], first_index_thread[i+1],p);
    }
    t[numthreads-1]=std::thread(ErdosRenyiAuxStarterFunction,&matrix, first_index_thread[numthreads-1], num_vertices,p);
    for( int i=0; i<numthreads; i++){
        t[i].join();
    }*/
    ErdosRenyiAuxStarterFunction(&matrix, 0, num_vertices,p);
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

        //std::cerr <<edge1node1<<"-"<<edge1node2<<";"<<edge2node1<<"-"<<edge2node2<<std::endl;

        //We do not want to have selected randomly selected loop edges
        if ((edge1node1!=edge1node2) && (edge2node1!=edge2node2)) {
            //Checking for cases leading to loops
            if ((edge1node1 == edge2node2) || (edge1node2 == edge2node1)) {

            } else {
                //Checking that both edges exist indeed
                if (newMatrix.getIsEdge(edge1node1, edge1node2) &&
                    newMatrix.getIsEdge(edge2node1, edge2node2)
                    && !newMatrix.getIsEdge(edge1node1, edge2node2) &&
                    !newMatrix.getIsEdge(edge2node1, edge1node2)) {
                    newMatrix.setIsEdge(edge1node1, edge1node2, false);
                    newMatrix.setIsEdge(edge2node1, edge2node2, false);
                    newMatrix.setIsEdge(edge1node1, edge2node2, true);
                    newMatrix.setIsEdge(edge2node1, edge1node2, true);
                }
            }
        }
        std::cerr << std::endl;
    }
    return newMatrix;

}

unsigned long MatrixAdjacency::bfs_distance(ID_TYPE start, ID_TYPE goal){
    std::unordered_set<ID_TYPE> openSet, closedSet;
    openSet.insert(start);
    unsigned long distance = 0;
    bool found=false;
    while(!openSet.empty() && !found){
        std::unordered_set<ID_TYPE> nodes_to_open;
        for(const ID_TYPE &id:openSet){
            if (id==goal){
                found=true;
                break;
            }else{
                if(closedSet.find(id)==closedSet.end()){
                    nodes_to_open.insert(matrix[id].begin(), matrix[id].end());
                }
                closedSet.insert(id);
            }
        }
        openSet.clear();
        openSet.insert(nodes_to_open.begin(),nodes_to_open.end());
        distance++;
    }
    return found ? distance-1 : INTMAX_MAX;
}

double MatrixAdjacency::closeness_vertex(ID_TYPE measure_node){
    double result=0;
    for(ID_TYPE id_node=0; id_node<N; id_node++){
        if(id_node!=measure_node) {
            result += 1 / (double)bfs_distance(measure_node, id_node);
        }
    }
    return 1/(double)(N-1)*result;
}

double MatrixAdjacency::closeness(){
    double result;
    for(ID_TYPE id_node=0; id_node<N; id_node++){
        result += closeness_vertex_optimization(id_node,12000);
        if(id_node%100 ==0) std::cerr << id_node<<std::endl;
    }
    return 1/(double)(N)*result;
}

bool MatrixAdjacency::closeness_greater_then(double baseline){
    double result;
    for(ID_TYPE id_node=0; id_node<N; id_node++){
        result += closeness_vertex_optimization(id_node,12000);
        if(id_node%100 ==0) std::cerr << id_node<<std::endl;
        double min_result = 1/(double)N*result;
        double max_result = 1/(double)N*result + 1 - id_node/N;
        std::cerr << "min: "<<min_result<<" max: "<<max_result<<std::endl;
        if( min_result > baseline) return true;
        if( max_result < baseline) return true;

    }
    return (1/(double)(N)*result)>baseline;
}

double MatrixAdjacency::closeness_vertex_optimization(ID_TYPE measure_node, int max_depth){
    std::unordered_set<ID_TYPE> closed_nodes;
    std::unordered_set<ID_TYPE> nodes_at_previous_distance;
    nodes_at_previous_distance.insert(measure_node);
    double result=0;
    for(int i=0; !nodes_at_previous_distance.empty();i++){
        std::unordered_set<ID_TYPE> nodes_at_next_distance;
        for(ID_TYPE node: nodes_at_previous_distance){
            if ( closed_nodes.find(node) == closed_nodes.end()){
                nodes_at_next_distance.insert(matrix[node].begin(),matrix[node].end());
                if(i!=0) result+=1/(double)i;
            }
        }
        closed_nodes.insert(nodes_at_previous_distance.begin(),nodes_at_previous_distance.end());
        nodes_at_previous_distance.clear();
        nodes_at_previous_distance.insert(nodes_at_next_distance.begin(), nodes_at_next_distance.end());
    }
    return 1/(double)(N-1)*result;
}