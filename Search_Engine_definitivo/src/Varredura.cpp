#include "Varredura.h"


/* A função inicializar acha todos os arquivos para leitura e chama a leitura_palavra para criar o indice invertido */
void Varredura::inicializa(){

    cout << "Iniciando carregamento do Banco de Dados......" << endl << endl; //MOstrar inicio da varredura
    string endereco;
    char * caminho_c = new char [caminho.length()+1];
    std::strcpy (caminho_c, caminho.c_str());
    dir = opendir(caminho_c); //Abre a pasta - colocar variavel
    /* Loop para identificar e armazenar temporariamente os arquivos da pasta*/
    while ((lsdir = readdir(dir)) != NULL ){
        endereco = caminho + "\\";
        endereco = endereco + lsdir->d_name; //Junta o nome do arquivo com o diretorio especificado
        if((endereco != caminho + "\\.") && (endereco != caminho + "\\.."))
            documentos.push_back(endereco); //Coloca a localização desse arquivo no vector
        i++;
    }
    closedir(dir); // Fecha diretorio
}

void Varredura::setcaminho(string diretorio)
{
    caminho = diretorio;
}

string Varredura::getcaminho()
{
    return caminho;
}

vector <string> Varredura::setdocumentos(){
    return documentos; //Retorna o nome do documento
};
