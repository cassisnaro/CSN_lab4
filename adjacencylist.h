#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H

#include <vector>
#include <list>

using namespace std;

class AdjacencyList
{

private:
    vector<list<int> > adj_list;
    int * distance;

public:

    AdjacencyList();
    void resize(int N);
    void printList() const;
    double geodesicDistancesSum(int id);
    void add(int id1, int id2);
    bool contains(int id1, int id2) const;
    void remove(int id1, int id2);
    ~AdjacencyList();


};

#endif // ADJACENCYLIST_H
