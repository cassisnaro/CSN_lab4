//
// Created by daniel on 29/10/15.
//
#include <iostream>
#include <random>
#include "SyntacticDependencyTree.h"


using namespace std;

int main(int argc, char **argv){

    //srand(1234);
    int seed = 1234;
    std::default_random_engine generator(seed);

    /*
    std::vector<SyntacticDependencyTree*> trees;
    trees.push_back(new SyntacticDependencyTree("Arabic","./data/Arabic_syntactic_dependency_network.txt"));
    trees.push_back(new SyntacticDependencyTree("Basque","./data/Basque_syntactic_dependency_network.txt"));
    trees.push_back(new SyntacticDependencyTree("Catalan","./data/Catalan_syntactic_dependency_network.txt"));
    trees.push_back(new SyntacticDependencyTree("Chinese","./data/Chinese_syntactic_dependency_network.txt"));
    trees.push_back(new SyntacticDependencyTree("Czech", "./data/Czech_syntactic_dependency_network.txt"));
    trees.push_back(new SyntacticDependencyTree("English","./data/English_syntactic_dependency_network.txt"));
    trees.push_back(new SyntacticDependencyTree("Greek","./data/Greek_syntactic_dependency_network.txt"));
    trees.push_back(new SyntacticDependencyTree("Hungarian","./data/Hungarian_syntactic_dependency_network.txt"));
    trees.push_back(new SyntacticDependencyTree("Italian","./data/Italian_syntactic_dependency_network.txt"));
    trees.push_back(new SyntacticDependencyTree("Turkish","./data/Turkish_syntactic_dependency_network.txt"));
    */

    double c;
    SyntacticDependencyTree basque("Basque","./data/Basque_syntactic_dependency_network.txt");
    //cout << "Basque closeness centrality: " << basque.getClosenessCentrality() << endl;
    //SyntacticDependencyTree * ER = SyntacticDependencyTree::ErdosRenyi(basque.getNNodes(),basque.getNEdges(),generator);
    //c = ER->getClosenessCentrality();
    cerr << "ER closeness centrality: " << c << endl;
    SyntacticDependencyTree * SM = SyntacticDependencyTree::SwitchingModel(basque,1,generator);
    c = SM->getClosenessCentrality();
    cerr << "SM closeness centrality: " << c << endl;

    //MatrixLanguage basqueMatrix("Basque","./data/Basque_syntactic_dependency_network.txt");
    //cerr<<"loaded\n";
    //cerr<<basqueMatrix.closeness()<<endl;


    //srand(1234);
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


    /*MatrixLanguage matrixLanguage("Hungarian","./data/Hungarian_syntactic_dependency_network.txt");
    cerr<<"loaded\n";
    cerr.precision(15);
    cerr<< fixed << matrixLanguage.closeness()<<endl;*/


    return 0;
}



