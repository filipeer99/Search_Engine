#ifndef DOCUMENTO_H
#define DOCUMENTO_H
#include <map>
#include <set>
#include <string>
#include <cmath>

using std::pair;
using std::string;
using std::map;

//Usado para calcular a norma de um vetor a partir de suas dimensões
double Calcula_Norma (map <string, double> W){
	double norma_elevado_2 = 0;
	for (auto i : W){
		norma_elevado_2 += pow(i.second,2);
	}
	return sqrt(norma_elevado_2);
}



class documento
{
    public:
        // Construtói um vetor documento nulo
        documento ();
        documento(string nome);
        // Construtói o objeto com um map de tf não normalizado como argumento
        documento(string nome, map <string, double> &tf);
        documento(map <string, double> &tf);
        //Com o tf normalizado, calcula a dimensão em cada eixo e carrega o valor da norma
        //Pré-condição: O argumento tem que ser o map idf da coleção de documentos e o tf tem que estar normalizado
        void dimensionar(const map <string, double> &idf);
        //retorna o produto escalar de dois documentos
        // pré-condição - o objeto tem que estar com as dimensões carregadas
        double produto_escalar (const documento& x) const;
        // Retorna a similaridade entre dois vetores documentos
        // pré-condição - o objeto tem que estar com as dimensões carregadas 
        double cosseno (const documento& x) const;
        // Retorna a norma do documento
        // pré-condição - o objeto tem que estar com as dimensões carregadas 
        double norma () const;
        //Verifica se alguma palavra  de um conjunto de palavras pertence ao documento
        bool pertence (const string pesquisa) const;
        //Verifica se as dimensões estão carregadas
        bool coordenadas_w_carregada () const;
        //retorn o nome do documento
        string nome () const;
        void operator= (const documento& x);
        
    private:
		// Armazena o nome do documento
        string nome_;
        /* Armazena as coordenadas do vetor em cada eixo. Para isso, é necessário três etapas:
        1 - Carregar esse map com as palavras e a taxa de frequencia que ela aparece no documento
        2 - Carregar as dimensões multiplicando o tf pelo idf normalizado pela freq_max de cada palavra*/
		map<string, double> w_;
        //Verifica se o tf foi normalizado
        bool coordenadas_w_carregada_;
        //Essa variável guarda a norma do vetor documento
        double norma_;
};

#endif // DOCUMENTO_H
