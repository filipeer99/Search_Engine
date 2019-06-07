<<<<<<< HEAD
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
=======
#include "documento.h"
#include <map>
#include <set>
#include <string>
#include <cmath>

using std::pair;
using std::string;

documento::documento(){
    nome_ = "";
    norma_ = 0;
    coordenadas_w_carregada_ = false;
    std::map<string, double> d;
    w_ = d;
}

documento::documento(string nome, std::map <string, double> &tf){
    nome_ = nome;
    norma_ = 0;
    coordenadas_w_carregada_ = false;
    w_ = tf;
}

void documento::dimensionar(const std::map <string, double> &idf){
    std::map<string, double>::iterator w_it;
    for (std::map<string, double>::const_iterator k = idf.begin(); k!= idf.end(); k++){
        if(pertence (k->first))
        {
            w_it = w_.find(k->first);
            w_it->second = w_it->second * k->second;
        }
    }
    double norma_elevado_2 = 0;
	for (std::map<string, double>::iterator i = w_.begin(); i != w_.end(); i++){
		norma_elevado_2 += pow(i->second,2);
	}
	norma_ = sqrt(norma_elevado_2);
    coordenadas_w_carregada_ = true;
}

double documento::produto_escalar (const std::map<string, double> &p) const{
    double prod_esc = 0;
    for(std::map<string, double>::const_iterator p_it = p.begin(); p_it != p.end(); p_it++){
        if(pertence (p_it->first))
        {
            prod_esc += ((w_.at(p_it->first))*(p_it->second));
        }
    }
    return prod_esc;
}

double documento::cosseno (const documento& q) const{
    double som_wdq = q.produto_escalar(this->w_);
    double som_wdd = norma_;
    double som_wqq = q.norma();
    double cos = som_wdq / (som_wdd*som_wqq);
    return cos;
}

double documento::norma() const{
    return norma_;
}

bool documento::pertence (const string pesquisa) const{
    std::map<string,double>::const_iterator i;
    i = w_.find(pesquisa);
    if(i != w_.end())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

bool documento::coordenadas_w_carregada() const{
    return coordenadas_w_carregada_;
}

string documento::nome() const{
    return nome_;
}

void documento::operator=(const documento& x){
    this->nome_ = x.nome_;
    this->norma_ = x.norma_;
    this->coordenadas_w_carregada_ = x.coordenadas_w_carregada_;
    this->w_ = x.w_;
}
>>>>>>> c070ca96151df9928b4c12662087e58e7ccb69ef
