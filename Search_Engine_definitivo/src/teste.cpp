#include "doctest.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <cmath>
#include "ind_inv.h"
#include "Tratamento.h"
#include "Varredura.h"
#include "ranking.h"
//*****************************************************************
//teste do tratemento e indice invertido
class Teste_trat{
    public:
    static string palavra(const Tratamento& c){
        return c.palavra;
    }
    static char letra(const Tratamento& c){
        return c.letra;
    }
    static int i(const Tratamento& c){
        return c.i;
    }
};

 class Teste_ind{
    static map <string, set <documento*>> indice_invertido(const ind_inv& c){
        return c.indice_invertido;
    }
    static map <string, double> idf (const ind_inv& c){
        return c.idf;
    }
    static documento provisorio (const ind_inv& c){
        return c.provisorio;
    }
    static int num_arquivos_ (const ind_inv& c){
        return c.num_arquivos_;
    }
}; 


TEST_SUITE("ind_inv"){
    TEST_CASE("ind_inv() && novo_documento(string local) && fechar_documento()"){
        ind_inv colecao;
        REQUIRE(Teste_ind::num_arquivos_(colecao) == 0);
        REQUIRE(Teste_ind::provisorio(colecao) == nullptr);
        colecao.novo_documento("dinossauro");
        REQUIRE((Teste_ind::provisorio(colecao) != nullptr));
        REQUIRE(Teste_ind::provisorio(colecao)->diretorio == "dinossauro");
        REQUIRE(Teste_ind::provisorio(colecao) != nullptr);
        CHECK(Teste_ind::num_arquivos_(colecao) == 1);
        colecao.fechar_documento();
        CHECK(Teste_trat_ind::num_arquivos_(colecao) == 1);
        CHECK( Teste_trat_ind::provisorio(colecao) == nullptr);
    }
    TEST_CASE("inserir_no_indice(const string palavra"){
        ind_inv colecao;
        colecao.novo_documento("dinossauro");
        colecao.inserir_no_indice("morreram");
        std::map <string, double>::iterator i = Teste_trat_ind::provisorio->tf.find("morreram");
        CHECK((i != Teste_ind::provisorio(colecao)->tf.end()));
        CHECK(i.second == 1);
        colecao.inserir_no_indice("morreram");
        CHECK(i.second == 2);
        colecao.inserir_no_indice("meteoro");
        i = Teste_ind::provisorio->tf.find("meteoros");
        CHECK(i == Teste_ind::provisorio(colecao)->tf.end());
        i = Teste_ind::provisorio(colecao)->tf.find("meteoro");
        CHECK(i != Teste_ind::provisorio(colecao)->tf.end());
    }
    TEST_CASE("pesquisa_ponteiro(const vector<string> &pesquisa"){
        ind_inv colecao;
        colecao.novo_documento("dinossauro");
        colecao.inserir_no_indice("morreram");
        colecao.inserir_no_indice("meteoro");
        colecao.fechar_documento();
        colecao.novo_documento("mamiferos");
        colecao.inserir_no_indice("morreram");
        colecao.inserir_no_indice("leite");
        colecao.fechar_documento();
        vector<string> palavras = {"meteoro", "morreram", "leite"};
        set <documentos*> doc = palavras.pesquisa_ponteiro();
        CHECK(doc.size() == 2);
        palavras.pop_back();
        doc = palavras.pesquisa_ponteiro();
        CHECK(doc.size() == 2);
        palavras.pop_back();
        doc = palavras.pesquisa_ponteiro();
        CHECK(doc.size() == 1);
    }
}

TEST_SUITE("Tratamento"){
    TEST_CASE("leitura_palavra(vector <string> documentos, ind_inv &colecao)"){
        std::string p1 = "abelha";
        std::string p2 = "barata";
        std::string p3 = "caramujo";
        ind_inv colecao;
        Tratamento trat;
        string pesq = "Abelha Abelha. aBELHA ABELHA AB+ELHA .abelha ?abelha";
        vector<string> tratada;
        tratada = trat.leitura_palavra(pesq);
        for(auto i : tratada){
            REQUIRE(i == pesq);
        }
        REQUIRE(Teste_trat_ind::num_arquivos_ == 4);
        for(auto i: Teste_trat_ind::indice_invertido(colecao)){
            CHECK(i.first == p1 || i.first == p2 || i.first == p3);
        }
        interator map<string, set<documento *>> i;
        i = Teste_trat_ind::indice_invertido(colecao).find(p1);
        CHECK(i->second.size() == 3);
        i = Teste_trat_ind::indice_invertido(colecao).find(p2);
        CHECK(i->second.size() == 2);
        i = Teste_trat_ind::indice_invertido(colecao).find(p3);
        CHECK(i->second.size() == 1);*/
    }
}