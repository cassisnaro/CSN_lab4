//
// Created by daniel on 1/11/15.
//

#ifndef CSN_LAB4_SYNTACTICDEPTREE_H
#define CSN_LAB4_SYNTACTICDEPTREE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <map>
#include <sstream>
#include <random>
#include "adjacencylist.h"

class SyntacticDependencyTree {
    private:
        std::string _language;
        AdjacencyList adj_list;
        int N;
        int E;
        vector<pair<int,int> >edges;
        std::map<std::wstring, unsigned long > conversion_map;

        SyntacticDependencyTree();
        SyntacticDependencyTree(const SyntacticDependencyTree& tree);


    public:
        SyntacticDependencyTree(std::string language, std::string file_path);
        static SyntacticDependencyTree * ErdosRenyi(int N, int E, std::default_random_engine &unifr);
        static SyntacticDependencyTree * SwitchingModel(const SyntacticDependencyTree &original, int Q,
                                                                          std::default_random_engine &unifr);
        std::string print_table_1_row() const;
        void printList() const;
        int getClosenessCentrality();
        int getNNodes() const;
        int getNEdges() const;
        ~SyntacticDependencyTree();

};


#endif //CSN_LAB4_SYNTACTICDEPTREE_H
