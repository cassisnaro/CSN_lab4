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

    int seed = 1234;
    std::default_random_engine generator(seed);

    std::vector<string> langs; std::vector<string> paths;
    langs.push_back("Catalan");paths.push_back("./data/Catalan_syntactic_dependency_network.txt");
    langs.push_back("Chinese");paths.push_back("./data/Chinese_syntactic_dependency_network.txt");
    langs.push_back("Czech");paths.push_back("./data/Czech_syntactic_dependency_network.txt");
    langs.push_back("English");paths.push_back("./data/English_syntactic_dependency_network.txt");
    langs.push_back("Hungarian");paths.push_back("./data/Hungarian_syntactic_dependency_network.txt");

    std::vector<double> Cs;
    Cs.push_back(0.341010236465873);
    Cs.push_back(0.326123380880794);
    Cs.push_back(0.305948201747303);
    Cs.push_back(0.343509448238309);
    Cs.push_back(0.288346438018935);

    cerr.precision(15);
    int T = 20;
    for(int i = 0; i < 5; i++){
        cerr << "===========" << langs[i] << "============" << endl;
        cerr << "C=" << Cs[i] << endl;
        SyntacticDependencyTree * tree = new SyntacticDependencyTree(langs[i],paths[i]);
        cerr << "original generated" << endl;
        double Cnh;

        int countER = 0;
        for(int j = 0; j < T; j++){
            SyntacticDependencyTree * ER = SyntacticDependencyTree::ErdosRenyi(tree->getNNodes(),tree->getNEdges(),generator);
            cerr << "---ER[" << j << "] generated---" << endl;
            Cnh = ER->getClosenessApproximate(generator);
            cerr << "Cer=" << Cnh << endl;
            if(Cnh >= Cs[i]) countER++;
            delete ER;
            cerr << "---ER[" << j << "] deleted---" << endl;
        }

        int countSM = 0;
        for(int j = 0; j < T; j++){
            SyntacticDependencyTree *SM = SyntacticDependencyTree::SwitchingModel(*tree, log(tree->getNEdges()),
                                                                                  generator);
            cerr << "---SM[" << j << "]  generated---" << endl;
            Cnh = SM->getClosenessApproximate(generator);
            cerr << "Csm=" << Cnh << endl;
            if(Cnh >= Cs[i]) countSM++;
            delete SM;
            cerr << "---SM[" << j << "]  deleted---" << endl;
        }
        cerr << "----SUMMARY----" << endl;
        cerr << "T="<<T;
        cerr << "ER: count="<< countER << "  ;  p-value=" << countER/(double)T << endl;
        cerr << "SM: count="<< countSM << "  ;  p-value=" << countSM/(double)T << endl;
        cerr << "---------------" << endl;

        delete tree;
        cerr << "original deleted" << endl;
        cerr << "================================" << endl << endl;
    }

    return 0;
}



