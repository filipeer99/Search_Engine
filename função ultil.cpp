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
#include <algorithm>
#include "documento.h"

using namespace std;

void formatar (string &palavra)
{
	for (int i = 0; i<palavra.size(); i++){
		if((palavra[i] >= 'a' && palavra[i] <= 'z') || (palavra[i] >='A' && palavra[i] <= 'Z') || (palavra[i] >='0' && palavra[i] <= '9')){
			if(palavra[i] >= 'A' && palavra[i] <= 'Z' )
				palavra[i] += 0x20;
		}
		else{
			palavra.erase(i,1);
			i--;
		}
	}
}


int verificar_repetida (vector <string> &palavras, int& i)
{
	int rep = 1;
	while(palavras[i+rep] == palavras[i] && i + rep < palavras.size())
		rep++;
	i += rep-1;
	return rep ;
}

map <string,double> criar_map_documento (vector <string> &palavras)
{
	int tf_palavra;
	map <string,double> tf_documento;
	for (int i = 0; i < palavras.size(); i++){
		tf_palavra = verificar_repetida (palavras, i);
		tf_documento.insert(make_pair(palavras[i],tf_palavra));
	}
	return tf_documento;
}

int main()
{
	ifstream arquivo;
    vector<string> palavras;
    string recebe;
    map <string,double> doc1;
    arquivo.open(".\\teste3.txt" );//diretorio do seu pc
    if(arquivo.fail())
    {
        cout << "falha ao abrir o arquivo";
        exit(1);
    }
    while(! arquivo.eof())
    {
        arquivo >> recebe;
        formatar (recebe);
        palavras.push_back(recebe);
    }
    arquivo.close();
	std::sort(palavras.begin(), palavras.end());
	doc1 = criar_map_documento (palavras);
    for(auto i : doc1)
    {
        cout << i.first << " - " << i.second << "\n";
    }
    system("pause");

    return 0;
}
