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


void iserir_indice_invertido (const string &palavra, map <string, set <documento*>> &indice_invertido, documento* atual);

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
void criar_idf (map <string, set <documento*>> &indice_invertido, map <string, double> &idf, double total_arquivos);

int main()
{
	ifstream arquivo, arquivo1;
    vector<string> palavras, palavras2;
    string recebe;
    map <string,double> doc1,doc2;
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




	arquivo1.open(".\\teste4.txt" );//diretorio do seu pc
    if(arquivo1.fail())
    {
        cout << "falha ao abrir o arquivo11";
        exit(1);
    }
    while(! arquivo1.eof())
    {
        arquivo1 >> recebe;
        formatar (recebe);
        palavras2.push_back(recebe);
    }
    arquivo1.close();
	std::sort(palavras2.begin(), palavras2.end());
	documento* doc_atual2;
	doc_atual2 = new documento ();
	doc2 = criar_map_documento (palavras2, doc_atual2);
	*doc_atual2 = documento ("avulso2",doc1);

    criar_idf(indice_invertido,idf,2);
    cout << idf.size();
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

void criar_idf (map <string, set <documento*>> &indice_invertido, map <string, double> &idf, double total_arquivos)
{
	double aux;
	pair <std::map<string,double>::iterator,bool> verificar;
	for (auto i : indice_invertido){
        aux = total_arquivos/i.second.size();
		aux = log(aux);
        idf.insert(make_pair(i.first, aux));
	}
}

void iserir_indice_invertido (const string &palavra, map <string, set <documento*>> &indice_invertido, documento* atual)
{
    std::map<string, set <documento*>>::iterator i;
    i = indice_invertido.find(palavra);
    if (i == indice_invertido.end())
    {
        set<documento*> aux;
        aux.insert(atual);
        indice_invertido.insert(make_pair(palavra,aux));
    }
    else{
        i -> second.insert(atual);
    }
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
		iserir_indice_invertido (palavras[i],indice_invertido, doc_atual);
	}
	return tf_documento;
}
