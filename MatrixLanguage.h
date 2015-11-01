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

class MatrixLanguage {
    private:
        std::string _language;
        unsigned long N;
        unsigned long num_edges;
        unsigned long size;
        std::vector<bool> matrix;
        std::map<std::wstring, int> conversion_map;
        long convert_2d_index(unsigned long i, unsigned long j);

    public:
        MatrixLanguage(std::string language, std::string file_path);
        std::string print_table_1_row();
};


#endif //CSN_LAB4_MATRIXLANGUAGE_H
