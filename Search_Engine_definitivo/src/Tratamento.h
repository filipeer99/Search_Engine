#ifndef TRATAMENTO_H
#define TRATAMENTO_H

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
#include "ind_inv.h"
#include "Varredura.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::ifstream;

class Tratamento{
    ifstream arquivos;
    string palavra;
    char letra;
    unsigned int i;

    public:
        void leitura_palavra(vector <string> documentos, ind_inv &colecao);
        vector<string> leitura_palavra(string pesquisa);
        friend class Teste_trat;

};

#endif // TRATAMENTO_H
