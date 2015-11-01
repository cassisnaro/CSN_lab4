//
// Created by daniel on 29/10/15.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <locale>
#include <map>
#include <sstream>

using namespace std;

string print_table_1_row(string language, unsigned long N, unsigned long E);
long convert_2d_index(unsigned long i, unsigned long j, unsigned long N);

int main(int argc, char **argv){
    unsigned long N;
    unsigned long num_edges;

    std::locale::global(std::locale(""));
    std::wifstream wf("./data/Arabic_syntactic_dependency_network.txt"); // test.txt contains utf-8 text
    wstring readed_string_1, readed_string_2;

    wf >> N >> num_edges;

    unsigned long size = (N-1)*N/2;
    vector<bool> matrix;
    cerr << "size:"<<size<<endl;
    matrix.resize(size, false);


    unsigned long count=0;
    map<wstring, int> conversion_map;
    for(int i=0; i<num_edges; i++ ){
        wf >> readed_string_1 >> readed_string_2;
        unsigned long id1, id2;
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
            long index_lineal = convert_2d_index(id1, id2, N);
            matrix[index_lineal] = true;
        }
    }
    wcout << readed_string_1 << " " << readed_string_2 << endl;
    wcout << count << endl;

    print_table_1_row("arabic", N, num_edges);

    /*cin >> N >> num_edges;
    for (int i=0; i<num_edges; i++){

    }*/

    return 0;
}

string print_table_1_row(string language, unsigned long N, unsigned long E){
    stringstream returnStringStream;
    returnStringStream << language<< "& "<<N<<"& "<<E<<"& "<<E/(double)N<<"& "<<2*(double)E/(N*(N+1));
    return returnStringStream.str();
}

long convert_2d_index(unsigned long i, unsigned long j, unsigned long N){
    if(i > j){
        unsigned long tmp = i;
        i = j;
        j = tmp;
    }
    long index_complete_matrix_1D = i*N - i*(i+1)/2 + j-(i+1);
    return index_complete_matrix_1D;
}