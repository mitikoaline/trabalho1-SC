#ifndef VIGENERE_HPP_INCLUDED
#define VIGENERE_HPP_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <regex>
#include <cmath>
#include <sstream>

using namespace std;

class Vigenere{
    private:
		string senha;
		string mensagem;
		bool cifrar;
	public:
		string getSenha();
		string Cripto();
		vector<char> GeraAlfabeto();
		int BuscaIndice(char letra, vector<char> alfabeto);
		void setSenha(string);
		void setMensagem(string nome_do_arquivo);
		void setCifrar(bool);
		// metodos para a parte do ataque
		map<int, int> EncontraTamanhosSenha();
		vector<pair<string, vector<int>>> PosicoesTrigramas();
		vector<int> CalculaEspacos(const vector<int>& posicoes);
		vector<int> ObtemFatores(int num);
		// métodos para analisar a frequência das letras
		vector<map<char, float>> ListaDeTabelas(int);
		map<char, float> TabelaDeFrequencia(string);
		void EncontraSenha(int, int);
};

class Menu{
	private:
		bool encerrar = false;
	public:
		void Operacoes(Vigenere);
		int escolhaDeArquivos(int numero_de_arquivos, char* nomes_dos_arquivos[]);
		void setEncerrar(string);
		bool getEncerrar();
};

#endif