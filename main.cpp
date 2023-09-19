#include "Vigenere.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    
	if(argc - 1 == 0){
		cout << "Nao ha arquivos para trabalhar" <<endl;
		exit(0);
	}
	else{
		
		Menu menu;
		Vigenere cifragem;
		int escolha;
		string encerrar;

		cout << "Deseja encerrar o programa? Em caso afirmativo, digite 's', senao, apenas aperte qualquer letra e dê ENTER: ";
		cin >> encerrar;
		menu.setEncerrar(encerrar);
		
		while(!menu.getEncerrar()){

			cout<<endl;

			escolha = menu.escolhaDeArquivos(argc, argv);
			if (escolha == -1){
				cout << "Escolha invalida!" << endl;
				exit(escolha);
			}
			else{
				cifragem.setMensagem(argv[escolha]);//abre o arquivo e faz a leitura
				menu.Operacoes(cifragem);//escolhe a operacao
			}

			cout << "Deseja encerrar o programa? Em caso afirmativo, digite 's': ";
			cin >> encerrar;
			menu.setEncerrar(encerrar);
		}

    	/*senha do desafio1 = arara

    	string mensagemCifrada = cifragem.Cripto("teste", "Gondim Gondim", true);
    	string mensagemDecifrada = cifragem.Cripto(senha, mensagem, false);

    	cout << "Mensagem Cifrada:" << endl;
    	cout << mensagemCifrada << endl;
    	cout << "---------------------------------------------" << endl;
    	cout << "Mensagem Decifrada:" << endl;
    	cout << mensagemDecifrada << endl;*/
	}

    return 0;
}
