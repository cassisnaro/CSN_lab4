#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <vector>
#include <list>

using namespace std;

class AdjacencyList
{

private:
    vector<list<int> > adj_list;
    unsigned long N;
    unsigned long num_edges;
    int * distance;

public:
    unsigned long getN() const {
        return N;
    }

    void setN(unsigned long N) {
        this->N = N;
        adj_list.resize(N, list<int>());
        if(distance != 0)
            delete [] distance;
        distance = new int [N];
    }

    unsigned long getNum_edges() const {
        return num_edges;
    }

    void setNum_edges(unsigned long num_edges) {
        this->num_edges = num_edges;
    }
    void add(int id1, int id2);

    AdjacencyList();
    void printList();
    int geodesicDistancesSum(int id);
    ~AdjacencyList();


};

#endif // ADJACENCYLIST_H
