#include "documento.h"
#include <map>
#include <set>
#include <string>
#include <cmath>

using namespace std;

documento::documento(){
    nome_ = "";
    norma_ = 0;
    coordenadas_w_carregada_ = false;
    map <string,double> novo;
    w_ = novo;
}

documento::documento(string nome, map <string, double> &tf){
    nome_ = nome;
    norma_ = 0;
    coordenadas_w_carregada_ = false;
    w_ = tf;
}

void documento::operator=(documento &x){
	this->nome_ = x.nome_;
    this->norma_ = x.norma_;
    this->coordenadas_w_carregada_ = x.coordenadas_w_carregada_;
    this->w_ = x.w_;
}
