#ifndef VARREDURA_H
#define VARREDURA_H

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

using std::cout;
using std::endl;
using std::vector;
using std::string;

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

#endif // VARREDURA_H
