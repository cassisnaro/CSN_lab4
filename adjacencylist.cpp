#include "adjacencylist.h"
#include <iostream>

using namespace std;

void AdjacencyList::add(int id1, int id2)
{
    adj_list[id1].push_back(id2);
    adj_list[id2].push_back(id1);
}

AdjacencyList::AdjacencyList()
{
    distance = 0;
}

void AdjacencyList::printList()
{
    for(int i = 0; i < N; i++){
        list<int>::iterator it = adj_list[i].begin();
        cout << i << ": ";
        while(it != adj_list[i].end()){
            cout << *it << " ";
            it++;
        }
        cout << endl;
    }
}

int AdjacencyList::geodesicDistancesSum(int id)
{
    int nVisited = 1; //id1 is visited (the node itself)
    int sum = 0;
    for(int i = 0; i < N; i++)
        distance[i] = -1;
    distance[id] = 0;
    list<int> q;
    q.push_back(id);
    while(q.begin() != q.end()){
        int dest = q.front();
        q.pop_front();
        for(list<int>::iterator it = adj_list[dest].begin(); it != adj_list[dest].end(); it++){
            if(distance[*it]==-1){
                q.push_back(*it);
                distance[*it]=distance[dest]+1;
                sum+=distance[*it];
            }
        }
    }
    return sum;
}

AdjacencyList::~AdjacencyList()
{
    delete [] distance;
}
