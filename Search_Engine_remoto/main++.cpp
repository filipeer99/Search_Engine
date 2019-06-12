#include <dirent.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <utility>
#include <cmath>
#include <cstring>

using namespace std;

struct documento
{
    map <string, double> tf;
    string diretorio;
};

 struct documento_rank
{
    map <string, double> w;
    string diretorio;
};

typedef struct documento documento;
typedef struct documento_rank documento_rank;



class ind_inv{
    public:
    	//Contrutor padrão do objeto ind_inv
        ind_inv();
        /*Declara que um novo documento será inserido no indice invertido e cria um struct
        documento alocado dinamicamente, armazenando até que o documento seja fechado*/
        void novo_documento(string local);
    	//Insere o ponteiro  documento aberto no indice invertido
        /*Pré-requisito : A função novo_documento tem que ser chamada para a construção do struct
        documento, ou seja, algum documento tem que estar aberto*/
        void inserir_no_indice(const string palavra);
        //Icrementa 1 no tf do documento aberto e retorna true se o documento atual já foi inserido no indice invertido no pair da palavra do argumento e false se não foi
        /*Pré-requisito : A função novo_documento tem que ser chamada para a
        construção do struct documento, ou seja, algum documento tem que estar aberto*/
        bool tf_plus(string palavra);
        //fecha o documento que estava sendo inserido, anulando o ponteiro que estava armazenando o documento aberto
        void fechar_documento();
        //Calcula o idf com base no set<documentos*> do indice invertido e do numero total de arquivos
        /*OBS: essa função pode ser chamado em qualquer parte do programa, porem só terá seus valores verdadeiros após a
        leitura de todos os arquivos de uma coleção*/
        void calculo_idf();
        //retorna o idf para ranquear a pesquisa
        map <string, double> get_idf();
        //retorna o conjunto de ponteiros dos documentos (carregados com o tf) correspondentes às palavras pesquisadas
        set<documento*> pesquisa_ponteiro (const vector<string> &pesquisa);
        //retorna um conjunto de documentos com o W de cada palavra carregado
        vector<documento> pesquisa (const vector<string> &pesquisa);
        //Imprime o imdice e o idf
        void imprimir_indice();//nao e muito necessario
        void imprimir_idf();//nao e muito necessario
        //destrutor do objeto da classe
        ~ind_inv();
        //classe amiga para fazer testes
        friend class teste;
    private:
        //armazena o indice invertido
        map <string, set <documento*>> indice_invertido;
        //armazena o idf da coleção
        map <string, double> idf;
        //ponteiro usado para inserir um struct documento, alocado dinamicamente,
        //no indice invertido
        documento* provisorio;
        //guarda o numero de arquivos abertos e armazenados no indice
        int num_arquivos_;
};

class Varredura{
    private:
    int i = 0;
    DIR *dir; // Variavel do tipo diretorio
    struct dirent *lsdir;  // Struct da biblioteca dirent.h
    vector <string> documentos;
    string caminho;

    public:
        void setcaminho(string diretorio);
        string getcaminho();
        void inicializa();
        vector <string> setdocumentos();

};

class Tratamento{
    ifstream arquivos;
    string palavra;
    char letra;
    int i;

    public:
        void leitura_palavra(vector <string> documentos, ind_inv &colecao);

};


int main(void)
{
    string diretorio;
    Varredura inicio; //Cria objeto para varredura dos arquivos no diretorio
    Tratamento palavras; //Cria objeto para tratamento das palavras
    ind_inv colecao; //Cria objeto do indice invertido
    cout << "Digite o diretorio da pasta" << endl;
    getline(cin,diretorio);
    inicio.setcaminho(diretorio);
    inicio.inicializa(); //Inicializa varredura
    palavras.leitura_palavra(inicio.setdocumentos(),colecao); //Envia todos os documentos para tratamento
    colecao.calculo_idf();//Calcula o idf depois de ter lido todos os atquivos
    //duas funcoes para imprimir o indice e o idf
    //talvez nao seja necessario
    colecao.imprimir_idf();
    colecao.imprimir_indice();
    return 0;

}

//-------------------------------------------------------------- Modulo InicializaÃ§Ã£o -----------------------------------------------------------------------------------------------

/* A funÃ§Ã£o inicializar acha todos os arquivos para leitura e chama a leitura_palavra para criar o indice invertido */
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
        documentos.push_back(endereco); //Coloca a localizaÃ§Ã£o desse arquivo no vector
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

//-------------------------------------------------------------- Modulo InicializaÃ§Ã£o - Fim  -----------------------------------------------------------------------------------------------

//-------------------------------------------------------------- Modulo tratamento -----------------------------------------------------------------------------------------------


void Tratamento::leitura_palavra(vector <string> documentos, ind_inv &colecao){
    for(i=0; i < documentos.size(); i++){ //Loop para acessar todos os documentos
        arquivos.open(documentos.at(i)); // Abre o arquivo

        if(!arquivos.is_open()){
            cout << "Nao foi possivel abrir o arquivo" << endl;
            //cout << documentos.at(i) << endl;
        }else{
            //cout << documentos.at(i) << endl;
            colecao.novo_documento(documentos.at(i));
            while(arquivos.get(letra)){ // Loop de formataÃ§Ã£o, pega letra por letra

                if((letra >= 97 && letra <=122) || (letra >= 48 && letra <=57)){ // Pega as letras minusculas e numeros - ASCII
                    palavra = palavra + letra; // Junta as letras na string
                    continue;
                }

                if(letra >= 65 && letra <=90){ //Pega as letras maiusculas e transforma em minusculas - ASCII
                    letra += 32; //Pela tabela ASCII transforma em minusculo
                    palavra = palavra + letra; // Junta as letras na string
                    continue;
                }

                if(letra == 32){ //Olha se tem espaÃ§o " " para finalizar a palavra

                    if(palavra.size() == 0){ //Caso a palavra esteja vazia nÃ£o faÃ§a nada
                        continue;
                    }else{
                        palavra = palavra + '\0'; //Sinaliza final da string palavra
                        colecao.inserir_no_indice(palavra);
                        //cout << palavra << " " ;
                        palavra = "";
                    }
                    continue;
                }

                if(letra == '\n'){ // Olha se acabou a linha
                    //cout << palavra << endl;
                    palavra = palavra + '\0'; //Sinaliza fim da string palavra
                    colecao.inserir_no_indice(palavra);
                    palavra = "";
                }
            }
            if(palavra.size() != 0){ //Caso a palavra esteja vazia nÃ£o faÃ§a nada
                        palavra = palavra + '\0'; //Sinaliza final da string palavra
                        colecao.inserir_no_indice(palavra);
                        //cout << palavra << " " ;
                        palavra = "";
                    }
        }

        colecao.fechar_documento();
        arquivos.close(); // Fecha arquivo antes de abrir outro
    }
    documentos.clear(); // Apaga a memoria dinamica
    cout << "....... Terminado carregamento do Banco de Dados." << endl << endl;
}
//-------------------------------------------------------------- Modulo tratamento - Fim -----------------------------------------------------------------------------------------------


//--------------------------------------------------------------- Modulo Retorna documentos --------------------------------------------------------------------------------------------------

vector <string> Varredura::setdocumentos(){
    return documentos; //Retorna o nome do documento
};

//--------------------------------------------------------------- Fim do Modulo Retorna Documentos ------------------------------------------------------------------------------------------

//-------------------------------------------------------------- Modulo Indice Invertido -----------------------------------------------------------------------------------------------

ind_inv::ind_inv()
{
    num_arquivos_ = 0;
    provisorio = nullptr;
    map <string, set <documento*>> qualquer1;
    map <string, double> qualquer2;
    indice_invertido = qualquer1;
    idf = qualquer2;
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
        std::map<string, set <documento*>>::iterator i;
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
    std::map<string,double>::iterator i;
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
	double aux, numdoc = num_arquivos_;
	if (!(idf.empty()))
        idf.clear();
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
    std::map<string,set<documento*>>::iterator j;
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
    std::map<string,double>::iterator k;
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
    indice_invertido.clear();
}

void ind_inv::imprimir_indice()
{
    for(auto i : indice_invertido){
        cout << i.first << " - {";
        int k=0;
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

//-------------------------------------------------------------- Modulo Indice Invertido - Fim  ----------------------------------------------------------------------------------------------


