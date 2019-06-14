#include "tratamento.h"


void Tratamento::leitura_palavra(vector <string> documentos, ind_inv &colecao){
    for(i=0; i < documentos.size(); i++){ //Loop para acessar todos os documentos
        arquivos.open(documentos.at(i)); // Abre o arquivo
        if(arquivos.fail()){
            cout << "Nao foi possivel abrir o arquivo" << endl;
        }else{

            colecao.novo_documento(documentos.at(i));
            while(arquivos.get(letra)){ // Loop de formatação, pega letra por letra
                if((letra >= 97 && letra <=122) || (letra >= 48 && letra <=57)){ // Pega as letras minusculas e numeros - ASCII
                    palavra = palavra + letra; // Junta as letras na string
                    continue;
                }

                if(letra >= 65 && letra <=90){ //Pega as letras maiusculas e transforma em minusculas - ASCII
                    letra += 32; //Pela tabela ASCII transforma em minusculo
                    palavra = palavra + letra; // Junta as letras na string
                    continue;
                }

                if(letra == 32){ //Olha se tem espaço " " para finalizar a palavra
                    if(palavra.size() == 0){ //Caso a palavra esteja vazia não faça nada
                        continue;
                    }else{
                        palavra = palavra + '\0'; //Sinaliza final da string palavra
                        colecao.inserir_no_indice(palavra);
                        palavra = "";
                    }
                    continue;
                }

                if(letra == '\n'){ // Olha se acabou a linha
                    palavra = palavra + '\0'; //Sinaliza fim da string palavra
                    colecao.inserir_no_indice(palavra);
                    palavra = "";
                }
            }
            if(palavra.size() != 0){ //Caso a palavra esteja vazia não faça nada
                        palavra = palavra + '\0'; //Sinaliza final da string palavra
                        colecao.inserir_no_indice(palavra);
                        palavra = "";
                    }
        }
        colecao.fechar_documento();
        arquivos.close(); // Fecha arquivo antes de abrir outro
    }
    documentos.clear(); // Apaga a memoria dinamica
    cout << "....... Terminado carregamento do Banco de Dados." << endl << endl;
}


vector<string> Tratamento::leitura_palavra(string pesquisa){
    vector<string> saida;
    for(unsigned int j = 0; j < pesquisa.size(); j++){ // Loop de formatação, pega letra por letra
        letra = pesquisa[j];
        if((letra >= 97 && letra <=122) || (letra >= 48 && letra <=57)){ // Pega as letras minusculas e numeros - ASCII
            palavra = palavra + letra; // Junta as letras na string
            continue;
        }

        if(letra >= 65 && letra <=90){ //Pega as letras maiusculas e transforma em minusculas - ASCII
            letra += 32; //Pela tabela ASCII transforma em minusculo
            palavra = palavra + letra; // Junta as letras na string
            continue;
        }

        if(letra == 32){ //Olha se tem espaço " " para finalizar a palavra
            if(palavra.size() == 0){ //Caso a palavra esteja vazia não faça nada
                continue;
            }else{
                palavra = palavra + '\0'; //Sinaliza final da string palavra
                saida.push_back(palavra);
                palavra = "";
            }
            continue;
        }

        if(letra == '\n'){ // Olha se acabou a linha
            palavra = palavra + '\0'; //Sinaliza fim da string palavra
            saida.push_back(palavra);
            palavra = "";
        }
    }
    if(palavra.size() != 0){ //Caso a palavra esteja vazia não faça nada
                palavra = palavra + '\0'; //Sinaliza final da string palavra
                saida.push_back(palavra);
                palavra = "";
            }
    return saida;
}