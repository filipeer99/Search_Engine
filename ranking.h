#ifndef RANKING_H
#define RANKING_H

#include <iostream>
#include <queue>
#include <string.h>
#include <map>
#include <set>
#include <cmath>

using std::map;
using std::vector;
using std::priority_queue;
using std::pair;

class ranking
{
    private:
        //Armazena o ranking de documentos, que são ordenados a partir das similaridades
        priority_queue<pair<double, documento>> ranking_;
        //Armazena os documentos para o cálculo das similaridades
        vector<documento> docs_;
        //Struct documento que armazena o W da pesquisa
        documento pesquisa_;
        //Armazena a norma da pesquisa
        double norma_p_;
        //Armazena os valores idf para cada palavra
        map<string, double> idf_;
    
    public:
        //Construtor-Padrão
        ranking();
        //Constrói um objeto ranking e carrega as variáveis a partir do indice invertido
        //PRÉ-CONDIÇÃO: A pesquisa não pode estar vazia
        ranking(ind_inv indice, const vector<string> &p);
        //Calcula o produto escalar entre o W do documento e o W da pesquisa
        double produto_escalar(map<string, double> d_W);
        //Calcula a norma do vetor W do documento
        double calculo_norma(map<string, double> d_W);
        //Calcula a similaridade de um documento com a pesquisa
        //PRÉ-CONDIÇÃO: documento não pode estar vazio
        double similaridade(documento d);
        //Calcula as similaridades de cada documento e os armazena em uma fila de prioridade
        void gera_ranking();
        /*imprime k documentos em ordem decrescente de similaridade
        com o vetor pesquisa */
        void imprime_ranking(int k);
}

#endif //RANKING_H
