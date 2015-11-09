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

void AdjacencyList::sortIncreasing(int N)
{
    int maxDegree = 0;
    //Get maximum degree
    for(int i = 0; i < N; i++){
        int degree = getDegree(i);
        if(degree > maxDegree){
            maxDegree = degree;
        }
    }
    list<int> * nodes = new list<int>[maxDegree+1];
    int * idChange = new int [N];
    //Group nodes by degree
    for(int i = 0; i < N; i++)
        nodes[getDegree(i)].push_back(i);
    int id = 0;
    //Sort by degree
    vector<list<int> > aux;
    for(int i = 0; i <= maxDegree; i++){
        for(list<int>::iterator it = nodes[i].begin(); it != nodes[i].end(); it++){
            aux.push_back(adj_list[*it]);
            idChange[*it] = id;
            id++;
        }
    }
    //Update ids
    for(int i = 0; i < N; i++){
        for(list<int>::iterator it = aux[i].begin(); it != aux[i].end(); it++){
            *it = idChange[*it];
        }
    }
    adj_list = aux;

    delete [] idChange;
    delete [] nodes;
}

void AdjacencyList::sortDecreasing(int N)
{
    int maxDegree = 0;
    //Get maximum degree
    for(int i = 0; i < N; i++){
        int degree = getDegree(i);
        if(degree > maxDegree){
            maxDegree = degree;
        }
    }
    list<int> * nodes = new list<int>[maxDegree+1];
    int * idChange = new int [N];
    //Group nodes by degree
    for(int i = 0; i < N; i++)
        nodes[getDegree(i)].push_back(i);
    int id = 0;
    //Sort by degree
    vector<list<int> > aux;
    for(int i = maxDegree; i >= 0; i--){
        for(list<int>::iterator it = nodes[i].begin(); it != nodes[i].end(); it++){
            aux.push_back(adj_list[*it]);
            idChange[*it] = id;
            id++;
        }
    }
    //Update ids
    for(int i = 0; i < N; i++){
        for(list<int>::iterator it = aux[i].begin(); it != aux[i].end(); it++){
            *it = idChange[*it];
        }
    }
    adj_list = aux;

    delete [] idChange;
    delete [] nodes;
}

int AdjacencyList::getDegree(int id)
{
    return adj_list[id].size();
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
                sum+= 1.0 / (double)distance[*it];
            }
        }
    }
    return sum;
}

AdjacencyList::~AdjacencyList()
{
    delete [] distance;
}
