#include "ranking.h"

ranking::ranking(){

}

ranking::ranking(ind_inv indice, const vector<string> &p){
    //Obtem todos os documentos que contem pelo menos uma palavra da pesquisa
    docs_ = indice.pesquisa(p);
    //Obtem um map com o idf para cada palavra do documento
    idf_ = indice.get_idf();
    pesquisa_.diretorio = "pesquisa";
    //Calculo dos valores de tf da pesquisa
    map<string, double> tf_p;
    map<string, double>::iterator it_tf;
    //double aux;
    for(vector<string>::const_iterator i = p.begin(); i < p.end(); i++)
    {
        it_tf = tf_p.find(*i);
        if(it_tf != tf_p.end())
        {
            it_tf->second = it_tf->second + 1;
        }
        else
        {
            tf_p.insert(make_pair(*i, 1));
        }
    }
    //Obtencao dos valores de W, multiplicando os tf por seus respectivos idf
    map<string, double>::iterator it_idf;
    for(map<string, double>::iterator j = tf_p.begin(); j != tf_p.end(); j++)
    {
        it_idf = idf_.find(j->first);
        //Verifica se existe idf para a palavra no indice invertido
        if(it_idf != idf_.end())
        {
            j->second *= it_idf -> second;
        }
        else
        {
            j->second = 0;
        }
    }
    //Armazena os valores de W na variavel tf da pesquisa
    pesquisa_.tf = tf_p;
    //Calculo da norma da pesquisa
    double norma_quadrado = 0;
    for(map<string, double>::iterator i = pesquisa_.tf.begin(); i != pesquisa_.tf.end(); i++)
    {
        norma_quadrado += pow(i->second, 2);
    }
    norma_p_ = sqrt(norma_quadrado);
}

double ranking::produto_escalar(map<string, double> d_W){
    double prod_esc = 0;
    map<string, double>::iterator existe;
    //Multiplica o W da pesquisa com o respectivo W do documento para cada palavra
    for(map<string, double>::iterator i = pesquisa_.tf.begin(); i != pesquisa_.tf.end(); i++)
    {
        existe = d_W.find(i->first);
        if(existe != d_W.end())
        {
            prod_esc += d_W.at(i->first) * i->second;
        }
    }
    return prod_esc;
}

double ranking::calculo_norma(map<string, double> d_W){
    double norma_quadrado = 0;
    for(map<string, double>::iterator i = d_W.begin(); i != d_W.end(); i++)
    {
        norma_quadrado += pow(i->second, 2);
    }
    return sqrt(norma_quadrado);
}

double ranking::similaridade(documento d){
    double numerador = produto_escalar(d.tf);
    double norma_d = calculo_norma(d.tf);
    if(norma_d != 0)
    {
        return numerador/(norma_d * norma_p_);
    }
    else
    {
        return 0;
    }
}

void ranking::gera_ranking(){
    //Gera ranking caso o vetor documentos possua documentos
    if(docs_.size() != 0)
    {
        if(norma_p_ == 0)
        {
            correspondencia_total_ = true;
        }
        else
        {
            for(vector<documento>::iterator it_doc = docs_.begin(); it_doc != docs_.end(); it_doc++)
            {
                double cos = similaridade(*it_doc);
                ranking_.push(make_pair(cos, it_doc -> diretorio));
            }
            correspondencia_total_ = false;
        }
    }
    //Retorna ranking vazio
    else
    {
        priority_queue<pair<double, string>> nulo;
        ranking_.swap(nulo);
        correspondencia_total_ = false;
    }
}

void ranking::imprime_ranking(unsigned int k){
    //Imprime ranking caso este possua documentos
    string temporaria;
    if(correspondencia_total_ == false)
    {
        if(ranking_.size() != 0){
            if(k < ranking_.size()){
                cout << "imprimindo " << k << " documentos em ordem descrescente de similaridade... : ";
                cout << endl << "--------------------";
                for(unsigned int j = k; j!=0; j--)
                {

                    cout << endl << "->";
                    std::size_t nome = ranking_.top().second.find_last_of("\\");
                    string temporaria = ranking_.top().second.substr(nome+1);
                    cout << temporaria << endl;
                    ranking_.pop();
                }
            }
            else{
                cout << "Imprimindo documentos em ordem decrescente de similaridade";
                while(! ranking_.empty())
                {
                    cout << endl << "->";
                    std::size_t nome = ranking_.top().second.find_last_of("\\");
                    string temporaria = ranking_.top().second.substr(nome+1);
                    cout << temporaria << endl;
                    ranking_.pop();
                }
                
            }
            cout  << "--------------------" << endl;
        }
        //Imprime mensagem de erro caso o ranking esteja vazio
        else
        {
            cout << "Pesquisa nao retornou resultados." << endl;
        }
    }
    else
    {
        cout << "A pesquisa digitada nao possui nenhuma palavra que caracteriza algum documento. (Pequisa n�o espec�fica)" << endl;
    }
}
