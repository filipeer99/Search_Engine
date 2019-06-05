#ifndef DOCUMENTO_H
#define DOCUMENTO_H
#include <map>
#include <set>
#include <string>
#include <cmath>

using std::pair;
using std::string;
using std::map;


class documento
{
    public:
        // Constrói um vetor documento nulo
        documento ();
        // Constrói o objeto com um map de tf não normalizado como argumento
        documento(string nome, map <string, double> &tf);
        //Calcula a dimensão em cada eixo e carrega o valor da norma
        void dimensionar(const map <string, double> &idf);
        //retorna o produto escalar de dois documentos
        // pré-condição - o objeto tem que estar com as dimensões carregadas
        double produto_escalar (const std::map<string, double> &p) const;
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
        //retorna o nome do documento
        string nome () const;
        map<string, double> map();
        void operator= (const documento& x);

    private:
		// Armazena o nome do documento
        string nome_;
        /* Armazena as coordenadas do vetor em cada eixo. Para isso, é necessário três etapas:
        1 - Carregar esse map com as palavras e a taxa de frequencia que ela aparece no documento
        2 - Carregar as dimensões multiplicando o tf pelo idf normalizado pela freq_max de cada palavra*/
		std::map<string, double> w_;
        //Verifica se o tf foi normalizado
        bool coordenadas_w_carregada_;
        //Essa variável guarda a norma do vetor documento
        double norma_;
};

#endif // DOCUMENTO_H
