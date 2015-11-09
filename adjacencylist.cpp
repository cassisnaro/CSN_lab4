#include "adjacencylist.h"
#include <iostream>
#include <algorithm>

using namespace std;

AdjacencyList::AdjacencyList()
{
    distance = 0;
}

void AdjacencyList::add(int id1, int id2)
{
    adj_list[id1].push_back(id2);
    adj_list[id2].push_back(id1);
}

bool AdjacencyList::contains(int id1, int id2) const
{
    return find(adj_list[id1].begin(),adj_list[id1].end(),id2) != adj_list[id1].end();
}

void AdjacencyList::remove(int id1, int id2)
{
    adj_list[id1].remove(id2);
    adj_list[id2].remove(id1);
}

void AdjacencyList::resize(int N)
{
        adj_list.resize(N, list<int>());
        if(distance != 0)
            delete [] distance;
        distance = new int [N];
}

void AdjacencyList::printList() const
{
    for(int i = 0; i < adj_list.size(); i++){
        list<int>::const_iterator it = adj_list[i].begin();
        cout << i << ": ";
        while(it != adj_list[i].end()){
            cout << *it << " ";
            it++;
        }
        cout << endl;
    }
}

double AdjacencyList::geodesicDistancesSum(int id)
{
    double sum = 0;
    for(int i = 0; i < adj_list.size(); i++)
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
                sum+= 1.0 / distance[*it];
            }
        }
    }
    return sum;
}

AdjacencyList::~AdjacencyList()
{
    delete [] distance;
}
