#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <dirent.h>
#include <fstream>

using namespace std;

int main(){
    ifstream arquivo;
    vector<string> palavras;
    string recebe;

    arquivo.open("C:\\Users\\filip\\UFMG\\PDS2\\TP\\doc1.txt" );//diretorio do seu pc
    if(arquivo.fail())
    {
        cout << "falha ao abrir o arquivo";
        exit(1);
    }
    while(! arquivo.eof())
    {    
        arquivo >> recebe;
        palavras.push_back(recebe);  
    }
    arquivo.close();

    for(auto i : palavras)
    {
        cout << i << "," << endl;
    }

    system("pause");

    return 0;
}