#define //colocar dps

#include "doctest.h"
#include //incluir os .h 

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <cmath>

class Teste_varredura{
    public:
    int i = 0;
    static DIR *dir(const Varredura& c){
        return c.dir;
    }
    static struct dirent *lsdir(const Varredura& c){
        return c.lsdir;
    }
    static vector <string) documentos(const Varredura& c){
        return c.documentos;
    }
};

TEST_SUITE("Varredura"){
    TEST_CASE("void inicializa"){
        CHECK(Teste_varredura::i == 0);
        dir = opendir("D:\\arquivos testes");
        CHECK(Teste_varredura::dir.isopen());
        CHECK(Teste_varredura::i == 3);
        closedir(dir);
    }
}

//*****************************************************************

class Teste_tratamento{
    public:
    static ifstream arquivos(const Tratamento& c){
        return c.arquivos;
    }
    static string palavra(const Tratemento& c){
        return c.palavra;
    }
    static char letra(const Tratamento& c){
        return c.letra;
    }
    static int i(const Tratamento& c){
        return c.i;
    }
};

TEST_SUITE("Tratamento"){
    TEST_CASE("leitura_palavra(vector <string> documentos, ind_inv &colecao)"){
        CHECK(Teste_tratamento.leitura_palavra("OI!") == "oi");
        CHECK(Teste_tratamento.leitura_palavra("Bom dia?") == "bomdia");
    }
}














/****************************************************************************/

class Teste_ind_inv{
public:
    static map <string, set <documento*>> indice_invertido(const ind_inv &c){
        return c.indice_invertido;
    }
    static map <string, double> idf (const ind_inv &c){
        return c.idf;
    }
    static documento* provisorio (const ind_inv &c){
        return c.provisorio;
    }
    static int num_arquivos_ (const ind_inv &c){
        return c.num_arquivos_;
    }
};

TESTE_SUITE("ind_inv"){
    TESTE_CASE("ind_inv()"){
        ind_inv c;
        CHECK(Teste_ind_inv::num_arquivos_ == 0);
    }
    TESTE_CASE("inserir_no_indice(const string palavra)"){
        
    }
}
