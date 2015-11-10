//
// Created by daniel on 1/11/15.
//

#ifndef CSN_LAB4_MATRIXLANGUAGE_H
#define CSN_LAB4_MATRIXLANGUAGE_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <map>
#include <sstream>
#include "Matrix.h"
#include "MatrixAdjacency.h"

class MatrixLanguage {
    private:
        std::string _language;
        MatrixAdjacency* matrix;
        std::map<std::wstring, unsigned long > conversion_map;
        long convert_2d_index(unsigned long i, unsigned long j);

    public:
        MatrixLanguage(std::string language, std::string file_path);
        std::string print_table_1_row();
        double closeness();
        void computeDistances();
        int getN(){
            matrix->getN();
        }
        int getNumEdges(){
            matrix->getNum_edges();
        }
};


#endif //CSN_LAB4_MATRIXLANGUAGE_H
