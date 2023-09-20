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

using namespace std;

class Vigenere{
    private:
		string senha;
		string mensagem;
		bool cifrar;
	public:
		string Cripto();
		vector<char> GeraAlfabeto();
		int BuscaIndice(char letra, vector<char> alfabeto);
		void setSenha(string);
		void setMensagem(string nome_do_arquivo);
		void setCifrar(bool);
		// metodos para a parte do ataque
		int EncontraTamanhoSenha();
		vector<pair<string, vector<int>>> PosicoesTrigramas();
		vector<int> CalculaEspacos(const vector<int>& posicoes);
		vector<int> ObtemFatores(int num);
		int TamanhoSenha(const vector<vector<int>>& fatores);
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