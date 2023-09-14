#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// retorna a posicao da letra no alfabeto
int BuscaIndice(char letra, vector<char> alfabeto) {

    auto it = find(alfabeto.begin(), alfabeto.end(), letra);

    if (it != alfabeto.end()) {
        return distance(alfabeto.begin(), it);
    } else {
        return -1;
    }

}

string Cifra(string senha, string mensagem) {
    string mensagem_cifrada = "";
    int pos_mensagem, pos_senha, pos_cifra;
    char char_mensagem, char_senha;
    vector<char> alfabeto;

    // cria vetor do alfabeto
    for(char letra = 'a'; letra <= 'z'; letra++) {
        alfabeto.push_back(letra);
    }

    int j = 0;
    for(char letra : mensagem) {
        char_mensagem = tolower(letra);

        pos_mensagem = BuscaIndice(char_mensagem, alfabeto); // busca a posicao no alfabeto da letra da mensagem a ser cifrada

        if (pos_mensagem != -1) { // caso em que a letra consta no alfabeto

            char_senha = senha[j % senha.length()]; // realiza a busca da letra da senha que servira para a etapa de cifracao
            pos_senha = BuscaIndice(char_senha, alfabeto); // busca a posicao da letra da senha no alfabeto

            pos_cifra = ((pos_mensagem + pos_senha) % 26); // Ci = Pi + Ki (mod 26)
            mensagem_cifrada += alfabeto[pos_cifra];
            
            j++;

        } else { // caso em que a letra nao consta no alfabeto replica o caractere original na mensagem cifrada
            mensagem_cifrada += char_mensagem;
        }
    }

    return mensagem_cifrada;
}

string Decifra(string senha, string mensagem) {
    string mensagem_decifrada = "";
    int pos_mensagem, pos_senha;
    char char_mensagem, char_senha;
    vector<char> alfabeto;

    // cria vetor do alfabeto
    for(char letra = 'a'; letra <= 'z'; letra++) {
        alfabeto.push_back(letra);
    }

    int j = 0;
    for(char letra : mensagem) {
        char_mensagem = tolower(letra);

        pos_mensagem = BuscaIndice(char_mensagem, alfabeto); // busca a posicao da letra da mensagem a ser decifrada no alfabeto

        if (pos_mensagem != -1) { // caso em que a letra consta no alfabeto

            char_senha = senha[j % senha.length()]; // realiza a busca da letra da senha que servira para a etapa de decifracao
            pos_senha = BuscaIndice(char_senha, alfabeto); // busca a posicao da letra da senha no alfabeto

            char char_decifrado = ((pos_mensagem - pos_senha + 26) % 26); // Pi = Ci - Ki + 26 (mod 26)
            mensagem_decifrada += alfabeto[char_decifrado];
            
            j++;

        } else { // caso em que a letra nao consta no alfabeto replica o caractere original na mensagem decifrada
            mensagem_decifrada += char_mensagem;
        }
    }

    return mensagem_decifrada;
}

int main() {
    // Abra o arquivo
    std::ifstream arquivo("desafio1.txt");
    
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return 0;
    }

    // Crie uma string para armazenar o conteúdo do arquivo
    string mensagem((istreambuf_iterator<char>(arquivo)), (istreambuf_iterator<char>()));

    string senha = "arara";

    cout << Decifra(senha, mensagem) << endl;

    arquivo.close();
    return 0;
}