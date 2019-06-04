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
#include <cmath>
#include "documento.h"

using namespace std;

map <string, set <documento*>> indice_invertido;
map <string, double> idf;

//map usado para normalizar os tfs de cada palavra em cada documento
map <string, double> tf_max;

void iserir_indice_invertido (const string &palavra, map <string, set <documento*>> &indice_invertido, documento* &atual);

void freq_max(map <string, double> &tf_max, const pair <string, double> &tf_doc);

// Formata uma string tirando as pontuacoes e colocando todas letras em minusculo
void formatar (string &palavra);

// Verifica a reperição de uma palavra em um documento a partir de um vector de strings
//Pré-condição : o vector tem que estar ordenado
int verificar_repetida (vector <string> &palavras, int& i);

// Cria um map tendo a taxa de repetição de cada palavra em um documento
/* Altera o indice invertido, colocando um ponteiro do documento no set de cada palavra
que ele aparece através da função freq_max (frequencia maxima (item por item)*/
// Altera o map tf_max atraves da funcao freq_max (item por item)
map <string,double> criar_map_documento (vector <string> &palavras, documento* &doc_atual);

//Altera o map tf_max se:
// 1 - Se o tf da palavra correspondente do map tf_max for menor que o do pair tax_freq_doc
// 2 - Se não existir um pair com a chave correspondente, adicionando o pair tax_freq_doc
void freq_max (pair <string, int> tax_freq_doc);

//Cria o map idf a partir do índice invertido
void criar_idf (map <const string, set <documento*>> indice_invertido, map <string, double> idf, int total_arquivos);

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
	documento* doc_atual;
	doc_atual = new documento ();
	doc1 = criar_map_documento (palavras, doc_atual);
	*doc_atual = documento ("avulso",doc1);
    for(auto i : doc1)
    {
        cout << i.first << " - " << i.second << "\n";
    }
    system("pause");

    return 0;
}

void formatar (string &palavra)
{
	for (int i = 0; i<palavra.size(); i++){
		if((palavra[i] >= 'a' && palavra[i] <= 'z') || (palavra[i] >='A' && palavra[i] <= 'Z') || 
			(palavra[i] >='0' && palavra[i] <= '9')){
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

void freq_max(map <string, double> &tf_max, const pair <string, double> &tf_doc)
{
    std::map <string, double>::iterator i;
    i = tf_max.find(tf_doc.first);
    if(i == tf_max.end())
        tf_max.insert(tf_doc);
    else if (i-> second < tf_doc.second)
        i-> second = tf_doc.second;
}

void criar_idf (map <string, set <documento*>> indice_invertido, map <string, double> idf, 
				map <string, double> tf_max, double total_arquivos)
{
	std::map<string,double>::iterator j;
	double aux;
	for (auto i : indice_invertido){
		j = tf_max.find(i.first);
		aux = log(total_arquivos/i.second.size());
		aux /= j -> second;
		idf.insert(make_pair(i.first, aux));
	}
}

void iserir_indice_invertido (const string &palavra, map <string, set <documento*>> &indice_invertido, documento* &atual)
{
    std::map<string, set <documento*>>::iterator i;
    i = indice_invertido.find(palavra);
    i-> second.insert(atual);
}

map <string,double> criar_map_documento (vector <string> &palavras, documento* &doc_atual)
{
	int tf_palavra;
	pair <string, double> tf;
	map <string,double> tf_documento;
	for (int i = 0; i < palavras.size(); i++){
		tf_palavra = verificar_repetida (palavras, i);
		tf = make_pair(palavras[i],tf_palavra);
		tf_documento.insert(tf);
		freq_max(tf_max, tf);
		iserir_indice_invertido (palavras[i],indice_invertido, doc_atual);
	}
	return tf_documento;
}
