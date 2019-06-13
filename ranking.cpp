#include "ranking.h"
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <cmath>
//adicionar na main
using std::map;
using std::vector;
using std::priority_queue;
using std::cin;
using std::cout;
using std::endl;

ranking::ranking(){

}

ranking::ranking(ind_inv indice, const vector<string> &p){
    //Obtem todos os documentos que contém pelo menos uma palavra da pesquisa
    docs_ = indice.pesquisa(p);
    //Obtem um map com o idf para cada palavra do documento
    idf_ = indice.get_idf();    
    pesquisa_.diretorio = "pesquisa";
    //Cálculo dos valores de tf da pesquisa
    map<string, double> tf_p;
    map<string, double>::iterator it_tf;
    double aux;
    for(map<string, double>::const_iterator i = p.begin(); i < p.end(); i++)
    {
        it_tf = tf_p.find(i);
        if(it_tf != tf_p.end())
        {
            tf_p.at(i) = tf_p.second + 1;
        }
        else
        {
            tf_p.insert(make_pair(i, 1));
        }
    }
    //Obtenção dos valores de W, multiplicando os tf por seus respectivos idf
    map<string, double>::iterator it_idf;
    for(map<string, double>::iterator j = tf_p.begin(); j < tf_p.end(); j++)
    {
        it_idf = idf_.find(j->first);
        //Verifica se existe idf para a palavra no indice invertido
        if(it_idf != idf_.end())
        {
            j->second = j->second * it_idf;
        }
        else
        {
            j->second = 0;
        }
    }
    //Armazena os valores de W na variavel tf da pesquisa
    pesquisa_.tf = tf_p;
    //Cálculo da norma da pesquisa
    double norma_quadrado = 0;
    for(map<string, double>::iterator i = pesquisa_.tf.begin(); i < pesquisa.tf.end(); i++)
    {
        norma_quadrado += pow(i.second, 2); 
    }
    norma_p_ = sqrt(norma_quadrado);
}

double ranking::produto_escalar(map<string, double> d_W){
    double prod_esc = 0;
    map<string, double>::iterator existe;
    //Multiplica o W da pesquisa com o respectivo W do documento para cada palavra
    for(map<string, double>::iterator i = pesquisa_.tf.begin(); i < pesquisa.tf.end(); i++)
    {
        existe = d_W.find(i.first);
        if(existe != d_W.end())
        {
            prod_esc += d_W.at(i.first) * i.second;
        }
    }
}

double ranking::calculo_norma(map<string, double> d_W){
    double norma_quadrado = 0;
    for(map<string, double>::iterator i = d_W.begin(); i < d_W.end(); i++)
    {
        norma_quadrado += pow(i.second, 2); 
    }
    return sqrt(norma_quadrado);
}

double ranking::similaridade(documento d){
    double numerador = produto_escalar(d.tf);
    norma_d = calculo_norma(d.tf);
    if(norma_d != 0)
    {
        return numerador/(norma_d * norma_p_);
    }
    else
    {
        return 0;
    }
}
    
void ranking::gera_ranking(){
    //Gera ranking caso o vetor documentos possua documentos
    if(docs_.size() != 0)
    {
        for(vector<documento>::iterator it_doc = docs_.begin(); it_doc < docs_.end(); it_doc++)
        {
            double cos = similaridade(it_doc);
            ranking_.push(make_pair(cos, it_doc));
        }
    }
    //Retorna ranking vazio
    else
    {
        priority_queue<pair<double, documento>> nulo;
        ranking_.swap(nulo);
    }
}

void ranking::imprime_ranking(int k){
    //Imprime ranking caso este possua documentos 
    if(ranking_.size() != 0){
        if(k < ranking_.size()){
            for(priority_queue<pair<double, documento>>iterator it_rank = ranking_.begin();
            it_rank <= k; it_rank++)
        {   
            cout << "imprimindo " << k << " documentos em ordem descrescente de similaridade... : ";
            cout << "--------------------------------------------------"; 
            cout << endl << "->";
            cout << ranking_.top().second << endl;
            ranking_.pop();
        }
            cout << "--------------------------------------------------"; 
            }
        else{
            while(! ranking_.empty())
        {
            cout << "imprimindo todos docs...";
            cout << "--------------------------------------------------"; 
            cout << endl << "->";
            cout << ranking_.top().second << endl;
            ranking_.pop();
        }
            cout << "--------------------------------------------------"; 
        }
    }
    //Imprime mensagem de erro caso o ranking esteja vazio
    else
    {
        cout << "pesquisa não retornou resultados" << endl;
    }
}