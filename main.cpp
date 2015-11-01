//
// Created by daniel on 29/10/15.
//
#include <iostream>
#include <vector>
#include "MatrixLanguage.h"


using namespace std;

int main(int argc, char **argv){

    std::vector<MatrixLanguage> matrices;
    MatrixLanguage arabicMatrix("Arabic","./data/Arabic_syntactic_dependency_network.txt");
    matrices.push_back(arabicMatrix);
    MatrixLanguage basqueMatrix("Basque","./data/Basque_syntactic_dependency_network.txt");
    matrices.push_back(basqueMatrix);
    MatrixLanguage catalanMatrix("Catalan","./data/Catalan_syntactic_dependency_network.txt");
    matrices.push_back(catalanMatrix);
    MatrixLanguage chineseMatrix("Chinese","./data/Chinese_syntactic_dependency_network.txt");
    matrices.push_back(chineseMatrix);
    MatrixLanguage czechMatrix("Czech","./data/Czech_syntactic_dependency_network.txt");
    matrices.push_back(czechMatrix);
    MatrixLanguage englishMatrix("English","./data/English_syntactic_dependency_network.txt");
    matrices.push_back(englishMatrix);
    MatrixLanguage greekMatrix("Greek","./data/Greek_syntactic_dependency_network.txt");
    matrices.push_back(greekMatrix);
    MatrixLanguage hungarianMatrix("Hungarian","./data/Hungarian_syntactic_dependency_network.txt");
    matrices.push_back(hungarianMatrix);
    MatrixLanguage italianMatrix("Italian","./data/Italian_syntactic_dependency_network.txt");
    matrices.push_back(italianMatrix);
    MatrixLanguage turkishMatrix("Turkish","./data/Turkish_syntactic_dependency_network.txt");
    matrices.push_back(turkishMatrix);


    //Printing table 1
    for(auto it=matrices.begin(); it!=matrices.end(); it++){
        cerr << it->print_table_1_row();
    }




    return 0;
}



