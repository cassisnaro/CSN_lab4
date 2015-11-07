//
// Created by daniel on 1/11/15.
//

#include "MatrixLanguage.h"

MatrixLanguage::MatrixLanguage(std::string language, std::string file_path){
    std::locale::global(std::locale(""));
    std::wifstream wf(file_path); // test.txt contains utf-8 text
    std::wstring readed_string_1, readed_string_2;

    unsigned long N;
    unsigned long num_edges;
    unsigned long size;

    wf >> N >> num_edges;

    matrix = new MatrixAdjacency(N);
    matrix->setNum_edges(num_edges);

    size = (N-1)*N/2;
    std::cerr << language << " size set "<<size<<std::endl;



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
            matrix->setIsEdge(id1, id2, true);
        }
    }
    std::cerr << "just here before table \n";

    print_table_1_row();

    std::cerr << "just here after table \n";

    /*cin >> N >> num_edges;
    for (int i=0; i<num_edges; i++){

    }*/
}

std::string MatrixLanguage::print_table_1_row(){
    std::stringstream returnStringStream;
    //std::cerr << _language<< "& "<<N<<"& "<<num_edges<<"& "<<num_edges/(double)N<<"& "<<2*(double)num_edges/(N*(N+1));
    returnStringStream << _language<< "& "<<matrix->getN()<<"& "<<matrix->getNum_edges()<<"& "<<matrix->getNum_edges()/(double)matrix->getN()<<"& "<<2*(double)matrix->getNum_edges()/(matrix->getN()*(matrix->getN()+1))<<std::endl;
    return returnStringStream.str();
}