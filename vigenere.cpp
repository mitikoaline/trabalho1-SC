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

vector<char> GeraAlfabeto() {
    vector<char> alfabeto;

    for(char letra = 'a'; letra <= 'z'; letra++) {
        alfabeto.push_back(letra);
    }
    return alfabeto;

}

// Realiza a cifragem ou decifragem da mensagem
string Cripto(string senha, string mensagem, bool cifrar) {
    string resultado = "";
    vector<char> alfabeto = GeraAlfabeto();
    int j = 0;

    for (char letra : mensagem) {
        char char_mensagem = tolower(letra);
        int pos_mensagem = BuscaIndice(char_mensagem, alfabeto); // busca a posicao da letra no alfabeto

        if (pos_mensagem != -1) { // caso em que a letra consta no alfabeto
            char char_senha = senha[j % senha.length()]; // realiza a busca da letra da senha que servira para a etapa de cifracao/decifracao
            int pos_senha = BuscaIndice(char_senha, alfabeto);
            // Cifracao:   Ci = Pi + Ki (mod 26)
            // Decifracao: Pi = Ci - Ki + 26 (mod 26)
            int pos_resultado = (cifrar) ? ((pos_mensagem + pos_senha) % 26) : ((pos_mensagem - pos_senha + 26) % 26);
            resultado += alfabeto[pos_resultado];
            j++;
        } else { // caso em que a letra nao consta no alfabeto replica o caractere original
            resultado += char_mensagem;
        }
    }

    return resultado;
}

int main() {
    // Abre o arquivo
    ifstream arquivo("desafio1.txt");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    string mensagem((istreambuf_iterator<char>(arquivo)), (istreambuf_iterator<char>()));
    arquivo.close();

    string senha = "arara";

    string mensagemCifrada = Cripto("teste", "Gondim Gondim", true);
    string mensagemDecifrada = Cripto(senha, mensagem, false);

    cout << "Mensagem Cifrada:" << endl;
    cout << mensagemCifrada << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Mensagem Decifrada:" << endl;
    cout << mensagemDecifrada << endl;

    return 0;
}