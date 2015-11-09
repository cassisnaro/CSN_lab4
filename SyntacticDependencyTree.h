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
#include "adjacencylist.h"

class SyntacticDependencyTree {
    private:
        std::string _language;
        AdjacencyList adj_list;
        std::map<std::wstring, unsigned long > conversion_map;
        SyntacticDependencyTree();

    public:
        SyntacticDependencyTree(std::string language, std::string file_path);
        void ErdosRenyiAuxFunction(unsigned long first_index, unsigned long next_first_index, double prob);
        static SyntacticDependencyTree ErdosRenyi(unsigned long size, double p, const std::default_random_engine& unifr, int num_threads=1);
        std::string print_table_1_row();
        void printList();
        int getClosenessCentrality();

};


#endif //CSN_LAB4_SYNTACTICDEPTREE_H
