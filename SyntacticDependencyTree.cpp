//
// Created by daniel on 1/11/15.
//

#include <set>
#include <unordered_set>
#include "SyntacticDependencyTree.h"

SyntacticDependencyTree::SyntacticDependencyTree()
{

}

SyntacticDependencyTree::SyntacticDependencyTree(const SyntacticDependencyTree& tree)
{
    N = tree.N;
    E = tree.E;
    adj_list = tree.adj_list;
}

SyntacticDependencyTree::SyntacticDependencyTree(std::string language, std::string file_path) {
    std::locale::global(std::locale(""));
    std::wifstream wf(file_path); // test.txt contains utf-8 text
    std::wstring readed_string_1, readed_string_2;
    int EwithLoops;
    wf >> N >> EwithLoops;

    adj_list.resize(N);
    E = 0;
    _language = language;
    unsigned long count=0;
    for(int i=0; i<EwithLoops; i++ ){
        wf >> readed_string_1 >> readed_string_2;
        unsigned long id1, id2;
        auto conversion_map_it_1 = conversion_map.find(readed_string_1);
        if (conversion_map_it_1==conversion_map.end()){
            conversion_map.insert(std::pair<std::wstring,unsigned long >(readed_string_1, count));
            id1 = count;
            count++;
        } else {
            id1 = conversion_map_it_1->second;
        }

        auto conversion_map_it_2 = conversion_map.find(readed_string_2);
        if (conversion_map_it_2==conversion_map.end()){
            conversion_map.insert(std::pair<std::wstring,unsigned long >(readed_string_2, count));
            id2 = count;
            count++;
        } else {
            id2 = conversion_map_it_2->second;
        }
        if (id1 != id2){
            E++;
            edges.push_back(pair<int,int>(id1,id2));
            adj_list.add(id1,id2);
        }
    }
    print_table_1_row();
}

std::string SyntacticDependencyTree::print_table_1_row() const
{
    std::stringstream returnStringStream;
    //std::cerr << _language<< "& "<<N<<"& "<<E<<"& "<<num_edges/(double)N<<"& "<<2*(double)num_edges/(N*(N+1));
    returnStringStream << _language<< "& "<<N<<"& "<<E<<"& "<<E/(double)N<<"& "<<2*(double)E/(N*(N+1))<<std::endl;
    return returnStringStream.str();
}

int SyntacticDependencyTree::getNNodes() const
{
    return N;
}

int SyntacticDependencyTree::getNEdges() const
{
    return E;
}

void SyntacticDependencyTree::sortIncreasing()
{
    adj_list.sortIncreasing(N);
}

void SyntacticDependencyTree::sortDecreasing()
{
    adj_list.sortDecreasing(N);
}

SyntacticDependencyTree * SyntacticDependencyTree::ErdosRenyi(int N, int E, std::default_random_engine &unifr){
    std::uniform_int_distribution<int> unifintdist(0,N-1);
    SyntacticDependencyTree * tree = new SyntacticDependencyTree();
    tree->N = N;
    tree->E = E;
    tree->adj_list.resize(N);
    set<pair<int,int> > added;
    int i = 0;
    while(i < E){
        int id1 = unifintdist(unifr);
        int id2 = unifintdist(unifr);
        if(id1 != id2){
            if(id1 > id2){
                int aux = id1; id1 = id2; id2 = aux;
            }
            pair<int,int> p(id1,id2);
            if(added.find(p)==added.end()){
                added.insert(p);
                tree->adj_list.add(id1,id2);
                i++;
            }
        }
    }
    return tree;
}

SyntacticDependencyTree * SyntacticDependencyTree::SwitchingModel(const SyntacticDependencyTree &original,
            int Q, std::default_random_engine &unifr){

    std::uniform_int_distribution<int> unifintdist(0,original.getNEdges()-1);
    std::uniform_int_distribution<int> booldist(0,1);
    SyntacticDependencyTree * tree = new SyntacticDependencyTree(original);
    tree->edges = original.edges;
    for(int i = 0; i < Q*tree->getNEdges(); i++){
        int e1idx = unifintdist(unifr);
        int e2idx = unifintdist(unifr);
        if(e1idx != e2idx){
            pair<int,int> e1 = tree->edges[e1idx];
            pair<int,int> e2 = tree->edges[e2idx];
            int u,v,s,t;
            if(booldist(unifr)==1){
                u = e1.first;
                v = e1.second;
            } else{
                u = e1.second;
                v = e1.first;
            }
            if(booldist(unifr)==1){
                s = e2.first;
                t = e2.second;
            } else{
                s = e2.second;
                t = e2.first;
            }

            if(u!= t && s != v){ //Invalid case, form a loop
                if(u != s && v != t){ //Valid, but don't alter the resulting graph
                    if(!tree->adj_list.contains(u,t)
                        && !tree->adj_list.contains(s,v)){ //Invalid, already existing edge
                        tree->adj_list.remove(u,v);
                        tree->adj_list.remove(s,t);

                        pair<int,int> e1new(u,t);
                        pair<int,int> e2new(s,v);
                        tree->adj_list.add(u,t);
                        tree->adj_list.add(s,v);
                        tree->edges[e1idx] = e1new;
                        tree->edges[e2idx] = e2new;
                    }
                }
            }

        }
    }
    return tree;
}

void SyntacticDependencyTree::printList() const
{
    adj_list.printList();
}

double SyntacticDependencyTree::getClosenessCentrality()
{
    double C = 0;
    int distance[N];
    for(int i = 0; i < N; i++){
        double Ci = adj_list.geodesicDistancesSum(i,distance) / (N-1);
        C += Ci;
    }
    return C/N;
}

double SyntacticDependencyTree::getClosenessApproximate(std::default_random_engine &unifr)
{
    double C = 0;
    int count=0;
    int distance[N];
    std::uniform_int_distribution<int> unifintdist(0,N-1);
    std::unordered_set<int> visited_nodes;
    while(count < N/10){
        int node = unifintdist(unifr);
        if (visited_nodes.find(node)==visited_nodes.end()){
            visited_nodes.insert(node);
            double Ci = adj_list.geodesicDistancesSum(node,distance) / (N-1);
            C += Ci;
            count++;
            //if(count%100==0) cerr << count << "/" << N/10 << endl;
        }

    }
    return C/count;
}

bool SyntacticDependencyTree::closenessCentralityGEQ(double C)
{
    double Cnh = 0;
    int distance[N];
    for(int i = 0; i < N; i++){
        double Ci = adj_list.geodesicDistancesSum(i,distance) / (N-1);
        Cnh += Ci;
        if(Cnh/N >= C) return true;
        if(Cnh/N + 1 - (i+1)/N < C) return false;
    }
    return Cnh/N >= C;
}

SyntacticDependencyTree::~SyntacticDependencyTree()
{

}
