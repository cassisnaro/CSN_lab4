//
// Created by daniel on 29/10/15.
//
#include <iostream>
#include "MatrixLanguage.h"


using namespace std;

int main(int argc, char **argv){

    srand(1234);
    /*std::vector<MatrixLanguage> matrices;
    MatrixLanguage arabicMatrix("Arabic","./data/Arabic_syntactic_dependency_network.txt");
    matrices.push_back(arabicMatrix);
    MatrixLanguage basqueMatrix("Basque","./data/Basque_syntactic_dependency_network.txt");
    matrices.push_back(basqueMatrix);
    MatrixLanguage catalanMatrix("Catalan","./data/Catalan_syntactic_dependency_network.txt");
    matrices.push_back(catalanMatrix);
    MatrixLanguage chineseMatrix("Chinese","./data/Chinese_syntactic_dependency_network.txt");
    matrices.push_back(chineseMatrix);
    try {
        MatrixLanguage czechMatrix("Czech", "./data/Czech_syntactic_dependency_network.txt");
        matrices.push_back(czechMatrix);
    } catch (const std::length_error& le) {
        std::cerr << "Length error: " << le.what() << '\n';
    }
    MatrixLanguage englishMatrix("English","./data/English_syntactic_dependency_network.txt");
    matrices.push_back(englishMatrix);
    MatrixLanguage greekMatrix("Greek","./data/Greek_syntactic_dependency_network.txt");
    matrices.push_back(greekMatrix);
    MatrixLanguage hungarianMatrix("Hungarian","./data/Hungarian_syntactic_dependency_network.txt");
    matrices.push_back(hungarianMatrix);
    MatrixLanguage italianMatrix("Italian","./data/Italian_syntactic_dependency_network.txt");
    matrices.push_back(italianMatrix);
    MatrixLanguage turkishMatrix("Turkish","./data/Turkish_syntactic_dependency_network.txt");
    matrices.push_back(turkishMatrix);*/


     MatrixLanguage basqueMatrix("Basque","./data/Basque_syntactic_dependency_network.txt");
    cerr<<"loaded\n";
    cerr<<basqueMatrix.closeness()<<endl;




    return 0;
}



