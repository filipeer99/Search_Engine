#ifndef IND_INV_H
#define IND_INV_H


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <cmath>

using std::map;
using std::set;
using std::vector;
using std::cout;
using std::endl;
using std::string;


struct documento
{
    map <string, double> tf;
    string diretorio;
};

typedef struct documento documento;

class ind_inv{
    public:
    	//Contrutor padrao do objeto ind_inv
        ind_inv();
        /*Declara que um novo documento sera inserido no indice invertido e cria um struct
        documento alocado dinamicamente, armazenando ate que o documento seja fechado*/
        void novo_documento(string local);
    	//Insere o ponteiro  documento aberto no indice invertido
        /*Pré-requisito : A funcao novo_documento tem que ser chamada para a construcao do struct
        documento, ou seja, algum documento tem que estar aberto*/
        void inserir_no_indice(const string palavra);

        //fecha o documento que estava sendo inserido, anulando o ponteiro que estava armazenando o documento aberto
        void fechar_documento();
        //Calcula o idf com base no set<documentos*> do indice invertido e do numero total de arquivos
        /*OBS: essa funcao pode ser chamado em qualquer parte do programa, porem so tera seus valores verdadeiros apos a
        leitura de todos os arquivos de uma colecao*/
        void calculo_idf();
        //retorna o idf para ranquear a pesquisa
        map <string, double> get_idf();
        //retorna o conjunto de ponteiros dos documentos (carregados com o tf) correspondentes as palavras pesquisadas
        set<documento*> pesquisa_ponteiro (const vector<string> &pesquisa);
        //retorna um conjunto de documentos com o W de cada palavra carregado
        vector<documento> pesquisa (const vector<string> &pesquisa);
        //Imprime o imdice e o idf
        void imprimir_indice();//nao e muito necessario
        void imprimir_idf();//nao e muito necessario
        //destrutor do objeto da classe
        ~ind_inv();
        //classe amiga para fazer testes
        friend class Teste_ind;
    private:
        //Icrementa 1 no tf do documento aberto e retorna true se o documento atual ja foi inserido no indice invertido no pair da palavra do argumento e false se n�o foi
        bool tf_plus(string palavra);
        //armazena o indice invertido
        map <string, set <documento*>> indice_invertido;
        //armazena o idf da colecao
        map <string, double> idf;
        //ponteiro usado para inserir um struct documento, alocado dinamicamente,
        //no indice invertido
        documento* provisorio;
        //guarda o numero de arquivos abertos e armazenados no indice
        int num_arquivos_;


};


#endif // IND_INV_H
