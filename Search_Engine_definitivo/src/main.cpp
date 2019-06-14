#include <iostream>
#include <dirent.h>
#include <iostream>
//#include <cstdlib>//se for windows deixe a bilioteca do system("pause")
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <cmath>
#include <cstring>
#include "ind_inv.h"
#include "Tratamento.h"
#include "Varredura.h"
#include "ranking.h"


using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;


int main()
{
    string diretorio, pesquisa;
    Varredura inicio; //Cria objeto para varredura dos arquivos no diretorio
    Tratamento palavras,palavras1; //Cria objeto para tratamento das palavras
    ind_inv colecao; //Cria objeto do indice invertido
    vector<string> pesquisa_ranking;
    cout << "Digite o diretorio da pasta" << endl;
    getline(cin,diretorio);
    inicio.setcaminho(diretorio);
    inicio.inicializa(); //Inicializa varredura
    palavras.leitura_palavra(inicio.setdocumentos(),colecao); //Envia todos os documentos para tratamento
    colecao.calculo_idf();//Calcula o idf depois de ter lido todos os atquivos
    cout << "Digite a pesquisa" << endl;
    getline(cin,pesquisa);
    pesquisa_ranking = palavras1.leitura_palavra(pesquisa);
    ranking resultado(colecao,pesquisa_ranking);
    resultado.gera_ranking();
    resultado.imprime_ranking(100);
    //system ("pause");
    return 0;

}



