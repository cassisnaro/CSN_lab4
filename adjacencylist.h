#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <vector>
#include <list>

using namespace std;

class AdjacencyList
{

private:
    vector<list<int> > adj_list;


public:

    AdjacencyList();
    AdjacencyList(const AdjacencyList&);
    void resize(int N);
    void printList() const;
    double geodesicDistancesSum(int id, int * distance);
    void add(int id1, int id2);
    bool contains(int id1, int id2) const;
    void remove(int id1, int id2);
    void sortIncreasing(int N);
    void sortDecreasing(int N);
    int getDegree(int id);
    ~AdjacencyList();


};

#endif // ADJACENCYLIST_H
