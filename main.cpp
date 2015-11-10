//
// Created by daniel on 29/10/15.
//
#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include "SyntacticDependencyTree.h"


using namespace std;

int main(int argc, char *argv[]){

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

    string str_language = argv[1];
    cout << str_language << endl;
    string str_path = argv[2];
    cout << str_path << endl;
    string C_str = argv[3];
    std::string::size_type sz;


    bool b;
    cout.precision(15);
    SyntacticDependencyTree language(str_language,str_path);
    cout << str_language<< " generated" << endl;
    double C=stod(C_str);

    SyntacticDependencyTree * ER = SyntacticDependencyTree::ErdosRenyi(language.getNNodes(),language.getNEdges(),generator);
    clock_t begin_time = clock();
    /*for(int i=0; i<4; i++){
        ER->closenessCentralityGEQ(C);
    }
    cout << float(clock()-begin_time)/ CLOCKS_PER_SEC;
    ER->sortDecreasing();
    begin_time = clock();
    for(int i=0; i<4; i++){
        ER->closenessCentralityGEQ(C);
    }
    cout << float(clock()-begin_time)/ CLOCKS_PER_SEC;*/
    ER->sortIncreasing();
    begin_time = clock();
    //for(int i=0; i<4; i++){
        ER->closenessCentralityGEQ(C);
    //}
    cout << float(clock()-begin_time)/ CLOCKS_PER_SEC;
    /*for(int i=0; i<20; i++){
        SyntacticDependencyTree * ER = SyntacticDependencyTree::ErdosRenyi(language.getNNodes(),language.getNEdges(),generator);
        ER->sortDecreasing();
        b = ER->closenessCentralityGEQ(C);
        cout << "Cer " << (b ? ">=" : "<") << " C" << endl;
        delete ER;
    }


    for(int i=0; i<20; i++) {
        SyntacticDependencyTree *SM = SyntacticDependencyTree::SwitchingModel(language, log(language.getNEdges()),
                                                                              generator);
        SM->sortDecreasing();
        //b = SM->closenessCentralityGEQ(C);
        //cout << "Csm " << (b ? ">=" : "<") << " C" << endl;
        delete SM;
    }*/

    return 0;
}



