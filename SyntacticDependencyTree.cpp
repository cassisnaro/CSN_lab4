//
// Created by daniel on 1/11/15.
//

#include "SyntacticDependencyTree.h"

SyntacticDependencyTree::SyntacticDependencyTree()
{

}

SyntacticDependencyTree::SyntacticDependencyTree(std::string language, std::string file_path) {
    std::locale::global(std::locale(""));
    std::wifstream wf(file_path); // test.txt contains utf-8 text
    std::wstring readed_string_1, readed_string_2;

    unsigned long N;
    unsigned long num_edges;

    wf >> N >> num_edges;

    adj_list.setN(N);
    adj_list.setNum_edges(num_edges);

    _language = language;

    unsigned long count=0;
    for(int i=0; i<num_edges; i++ ){
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
            adj_list.add(id1,id2);
        }
    }
    print_table_1_row();

}

std::string SyntacticDependencyTree::print_table_1_row(){
    std::stringstream returnStringStream;
    //std::cerr << _language<< "& "<<N<<"& "<<num_edges<<"& "<<num_edges/(double)N<<"& "<<2*(double)num_edges/(N*(N+1));
    returnStringStream << _language<< "& "<<adj_list.getN()<<"& "<<adj_list.getNum_edges()<<"& "<<adj_list.getNum_edges()/(double)adj_list.getN()<<"& "<<2*(double)adj_list.getNum_edges()/(adj_list.getN()*(adj_list.getN()+1))<<std::endl;
    return returnStringStream.str();
}

int ErdosRenyiAuxStarterFunction(Matrix* matrix, unsigned long first_index, unsigned long next_first_index, double prob){
    matrix->ErdosRenyiAuxFunction(first_index,next_first_index,prob);
    return 0;
}
void Matrix::ErdosRenyiAuxFunction(unsigned long first_index, unsigned long next_first_index, double prob){
    for(unsigned long index=first_index; index < next_first_index; index++){
        matrix[index]= drand48()<prob;
    }
    return;
}

SyntacticDependencyTree * SyntacticDependencyTree::ErdosRenyi(unsigned long size, double p, const std::default_random_engine &unifr, int numthreads){
    std::binomial_distribution<int> bindist ((size*(size-1))/2,p);
    unsigned long nEdges = bindist(generator);
    std::uniform_int_distribution<int> unifintdist(0,size-1);
    SyntacticDependencyTree * tree = new SyntacticDependencyTree();
    tree->adj_list.setN(size);
    tree->adj_list.setNum_edges(nEdges);
    set<pair<int,int> > added;
    for(int i = 0; i < nEdges; i++){
        int id1 = unifintdist(generator);
        int id2 = unifintdist(generator);
        if(id1!= id2){
            if(id1 > id2){
                int aux = id1; id1 = id2; id2 = aux;
            }
            pair<int,int> p(id1,id2);
            if(added.find(p)!=added.end()){
                added.insert(p);
                tree->adj_list.add(id1,id2);
            }
        }
    }
    return tree;
}

void MatrixLanguage2::printList()
{
    adj_list.printList();
}

int MatrixLanguage2::getClosenessCentrality()
{
    double C = 0;
    int N = adj_list.getN();

    for(int i = 0; i < adj_list.getN(); i++){
        double Ci = (1 / adj_list.geodesicDistancesSum(i) * (N-1));
        C += Ci;
    }
    return C/N;
}
