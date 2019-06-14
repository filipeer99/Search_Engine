#include "ind_inv.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <cmath>
#include <cstring>


ind_inv::ind_inv()
{
    num_arquivos_ = 0;
    provisorio = nullptr;
}

void ind_inv::novo_documento(string local)
{
    if(provisorio == nullptr){
        provisorio = new documento;
        num_arquivos_ ++;
    }
    else if(provisorio != nullptr && (local != provisorio -> diretorio)){
        fechar_documento();
        provisorio = new documento;
        num_arquivos_ ++;
    }

    provisorio -> diretorio = local;
}

void ind_inv::inserir_no_indice(const string palavra)
{
    bool incluso;
    incluso = tf_plus(palavra);
    if(!(incluso)){
        map<string, set <documento*>>::iterator i;
        i = indice_invertido.find(palavra);
        if (i == indice_invertido.end())
        {
            set<documento*> aux;
            aux.insert(provisorio);
            indice_invertido.insert(make_pair(palavra,aux));
        }
        else{
            i -> second.insert(provisorio);
        }
    }
}

bool ind_inv::tf_plus(string palavra)
{
    map<string,double>::iterator i;
    i = provisorio -> tf.find(palavra);
    if (i == provisorio -> tf.end())
    {
        provisorio -> tf.insert(make_pair(palavra,1));
        return false;
    }
    else
    {
        i -> second += 1;
        return true;
    }
}

void ind_inv::fechar_documento()
{
    provisorio = nullptr;
}

void ind_inv::calculo_idf()
{
    if (!(idf.empty()))
        idf.clear();
	double aux, numdoc = num_arquivos_;
	for (auto i : indice_invertido){
		aux = log(numdoc/i.second.size());
		idf.insert(make_pair(i.first, aux));
	}
}

map <string, double> ind_inv::get_idf()
{
    return idf;
}

set <documento*> ind_inv::pesquisa_ponteiro(const vector <string> &pesquisa)
{
    set<documento*> resultado_pesquisa;
    map<string,set<documento*>>::iterator j;
    for (auto i: pesquisa){
    	j = indice_invertido.find(i);
    	if(j != indice_invertido.end()){
	        for (auto k : j -> second)
	            resultado_pesquisa.insert(k);
		}
    }
    return resultado_pesquisa;
}

vector<documento> ind_inv::pesquisa(const vector <string> &pesquisa)
{
    set<documento*> resultado_pesquisa = pesquisa_ponteiro(pesquisa);
    vector <documento> resultado_retorno;
    documento aux;
    map<string,double>::iterator k;
    calculo_idf();
    for (auto i : resultado_pesquisa){
    	aux = *i;
    	for(auto j : aux.tf){
            k = idf.find(j.first);
            j.second *= k -> second;
    	}
        resultado_retorno.push_back(aux);
	}
    return resultado_retorno;
}

ind_inv::~ind_inv()
{
    set <documento*> colecao;
    for (auto i : indice_invertido){
        for (auto j : i.second)
        	colecao.insert(j);
    }
	for (auto i : colecao)
		delete i;
}

void ind_inv::imprimir_indice()
{
    for(auto i : indice_invertido){
        cout << i.first << " - {";
        unsigned int k=0;
        for(auto j : i.second){
            std::size_t nome = j -> diretorio.find_last_of("\\");
            string temporaria = j -> diretorio.substr(nome+1);
            cout << temporaria;
            k++;
            if(k < i.second.size())
                cout << ", ";
        }
        cout << "}" << endl;
    }
}

void ind_inv::imprimir_idf()
{
    for (auto i : idf)
        cout << i.first << " - " << i.second << endl;
    cout << endl;
}
