//
// Created by daniel on 1/11/15.
//

#include "MatrixLanguage.h"

MatrixLanguage::MatrixLanguage(std::string language, std::string file_path) {
    std::locale::global(std::locale(""));
    std::wifstream wf(file_path); // test.txt contains utf-8 text
    std::wstring readed_string_1, readed_string_2;

    wf >> N >> num_edges;

    size = (N-1)*N/2;
    matrix.resize(size, false);

    _language = language;

    unsigned long count=0;
    for(int i=0; i<num_edges; i++ ){
        wf >> readed_string_1 >> readed_string_2;
        unsigned long id1, id2;
        auto conversion_map_it_1 = conversion_map.find(readed_string_1);
        if (conversion_map_it_1==conversion_map.end()){
            conversion_map.insert(std::pair<std::wstring,int>(readed_string_1, count));
            id1 = count;
            count++;
        } else {
            id1 = conversion_map_it_1->second;
        }

        auto conversion_map_it_2 = conversion_map.find(readed_string_2);
        if (conversion_map_it_2==conversion_map.end()){
            conversion_map.insert(std::pair<std::wstring,int>(readed_string_2, count));
            id2 = count;
            count++;
        } else {
            id2 = conversion_map_it_2->second;
        }
        if (id1 != id2){
            long index_lineal = convert_2d_index(id1, id2);
            matrix[index_lineal] = true;
        }
    }

    print_table_1_row();

    /*cin >> N >> num_edges;
    for (int i=0; i<num_edges; i++){

    }*/
}

std::string MatrixLanguage::print_table_1_row(){
    std::stringstream returnStringStream;
    //std::cerr << _language<< "& "<<N<<"& "<<num_edges<<"& "<<num_edges/(double)N<<"& "<<2*(double)num_edges/(N*(N+1));
    returnStringStream << _language<< "& "<<N<<"& "<<num_edges<<"& "<<num_edges/(double)N<<"& "<<2*(double)num_edges/(N*(N+1))<<std::endl;
    return returnStringStream.str();
}


long MatrixLanguage::convert_2d_index(unsigned long i, unsigned long j){
    if(i > j){
        unsigned long tmp = i;
        i = j;
        j = tmp;
    }
    long index_complete_matrix_1D = i*N - i*(i+1)/2 + j-(i+1);
    return index_complete_matrix_1D;
}