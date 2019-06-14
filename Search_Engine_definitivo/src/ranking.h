#ifndef RANKING_H
#define RANKING_H


#include <iostream>
#include <queue>
#include <string.h>
#include <map>
#include <set>
#include <cmath>
#include "ind_inv.h"

using std::map;
using std::vector;
using std::priority_queue;
using std::pair;
using std::string;


class ranking
{
    private:
        //Armazena o ranking de documentos, que sao ordenados a partir das similaridades
        priority_queue<pair<double, string>> ranking_;
        //Armazena os documentos para o calculo das similaridades
        vector<documento> docs_;
        //Struct documento que armazena o W da pesquisa
        documento pesquisa_;
        //Armazena a norma da pesquisa
        double norma_p_;
        //Armazena os valores idf para cada palavra
        map<string, double> idf_;
        //Indica se a pesquisa corresponde igualmente a todos os documentos da pasta
        //Obs.: So acontece quando nenhuma das palavras da pesquisa tem idf > 0
        bool correspondencia_total_;
        //Calcula o produto escalar entre o W do documento e o W da pesquisa
        double produto_escalar(map<string, double> d_W);
        //Calcula a norma do vetor W do documento
        double calculo_norma(map<string, double> d_W);
        //Calcula a similaridade de um documento com a pesquisa
        //PRE-CONDICAO: documento nao pode estar vazio
        double similaridade(documento d);

    public:
        //Construtor-Padrao
        ranking();
        //Constroi um objeto ranking e carrega as variaveis a partir do indice invertido
        //PRE-CONDICAO: A pesquisa nao pode estar vazia
        ranking(ind_inv indice, const vector<string> &p);
        //Calcula as similaridades de cada documento e os armazena em uma fila de prioridade
        void gera_ranking();
        /*imprime k documentos em ordem decrescente de similaridade
        com o vetor pesquisa */
        void imprime_ranking(unsigned int k);
};

#endif // RANKING_H
