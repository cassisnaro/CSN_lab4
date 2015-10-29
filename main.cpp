//
// Created by daniel on 29/10/15.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <map>

#include "main.h"

using namespace std;

int convert_2d_index(int i, int j, int N);

int main(int argc, char **argv){
    long N;
    long num_edges;

    std::locale::global(std::locale(""));
    std::wifstream wf("./data/Arabic_syntactic_dependency_network.txt"); // test.txt contains utf-8 text
    wstring readed_string_1, readed_string_2;

    wf >> N >> num_edges;

    long size = (N-1)*N/2;
    vector<bool> matrix;
    cerr << "size:"<<size<<endl;
    matrix.resize(size, false);


    int count=0;
    map<wstring, int> conversion_map;
    for(int i=0; i<num_edges; i++ ){
        wf >> readed_string_1 >> readed_string_2;
        int id1, id2;
        auto conversion_map_it_1 = conversion_map.find(readed_string_1);
        if (conversion_map_it_1==conversion_map.end()){
            conversion_map.insert(std::pair<wstring,int>(readed_string_1, count));
            id1 = count;
            count++;
        } else {
            id1 = conversion_map_it_1->second;
        }

        auto conversion_map_it_2 = conversion_map.find(readed_string_2);
        if (conversion_map_it_2==conversion_map.end()){
            conversion_map.insert(std::pair<wstring,int>(readed_string_2, count));
            id2 = count;
            count++;
        } else {
            id2 = conversion_map_it_2->second;
        }
        if (id1 != id2){
            int index_lineal = convert_2d_index(id1, id2, N);
            matrix[index_lineal] = true;
        }
    }
    wcout << readed_string_1 << " " << readed_string_2 << endl;
    cout << count << endl;

    /*cin >> N >> num_edges;
    for (int i=0; i<num_edges; i++){

    }*/

    return 0;
}

int convert_2d_index(int i, int j, int N){
    if(i > j){
        int tmp = i;
        i = j;
        j = tmp;
    }
    int index_complete_matrix_1D = i*N - i*(i+1)/2 + j-(i+1);
    return index_complete_matrix_1D;
}