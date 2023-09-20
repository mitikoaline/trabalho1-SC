#include "Vigenere.hpp"

#ifdef _WIN32 //macro para limpar o terminal
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif

// retorna a posicao da letra no alfabeto
int Vigenere::BuscaIndice(char letra, vector<char> alfabeto) {
    auto it = find(alfabeto.begin(), alfabeto.end(), letra);

    if (it != alfabeto.end()) {
        return distance(alfabeto.begin(), it);
    } else {
        return -1;
    }

}

vector<char> Vigenere::GeraAlfabeto() {
    vector<char> alfabeto;

    for(char letra = 'a'; letra <= 'z'; letra++) {
        alfabeto.push_back(letra);
    }
    return alfabeto;

}

// Realiza a cifragem ou decifragem da mensagem
string Vigenere::Cripto() {
    string resultado = "";
    vector<char> alfabeto = GeraAlfabeto();
    int j = 0;

    for (char letra : this->mensagem) {
        char char_mensagem = tolower(letra);
        int pos_mensagem = BuscaIndice(char_mensagem, alfabeto); // busca a posicao da letra no alfabeto

        if (pos_mensagem != -1) { // caso em que a letra consta no alfabeto
            char char_senha = this->senha[j % (this->senha).length()]; // realiza a busca da letra da senha que servira para a etapa de cifracao/decifracao
            int pos_senha = BuscaIndice(char_senha, alfabeto);
            // Cifracao:   Ci = Pi + Ki (mod 26)
            // Decifracao: Pi = Ci - Ki + 26 (mod 26)
            int pos_resultado = (this->cifrar) ? ((pos_mensagem + pos_senha) % 26) : ((pos_mensagem - pos_senha + 26) % 26);
            resultado += alfabeto[pos_resultado];
            j++;
        } else { // caso em que a letra nao consta no alfabeto replica o caractere original
            resultado += char_mensagem;
        }
    }

    return resultado;
}

void Vigenere::setCifrar(bool opcao){
    this->cifrar = opcao;
}

void Vigenere::setSenha(string senha){
    this->senha = senha;
}

void Vigenere::setMensagem(string nome_do_arquivo){
    // Abre o arquivo
    ifstream arquivo(nome_do_arquivo+".txt");

    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo." << endl;
        exit(1);
    }

    string mensagem((istreambuf_iterator<char>(arquivo)), (istreambuf_iterator<char>()));
	this->mensagem = mensagem;
    arquivo.close();
}

/*********************************************************************************************************/

//funcoes do menu abaixo

//escolhe qual dos arquivos digitados na linha de comando vai ser utilizado
int Menu::escolhaDeArquivos(int numero_de_arquivos, char* nomes_dos_arquivos[]){

    int escolha;
	int coletor; //variavel para o guardar o retorno de system e parar os warnings
    
	coletor = system(CLEAR);
	if(coletor == -1){
		cout << "Falha na limpeza da tela" <<endl;
	}
	cout << "Escolha um dos " << numero_de_arquivos-1 << "arquivos fornecidos:" << endl;
    for(int i=1; i<numero_de_arquivos; i++){
        cout << i << " - " << nomes_dos_arquivos[i] << endl;
    }
    cout << endl;
    cin >> escolha;
    if(escolha >=1 && escolha <= numero_de_arquivos-1){
        return escolha;
    }
    else
        return -1;
}

//escolhe qual operacao o programa vai fazer com o arquivo: cifrar, decifrar, ou quebrar a cifra descobrindo a senha
void Menu::Operacoes(Vigenere cifragem ){

	char opcao;
    string senha;
	int coletor; //variavel para o guardar o retorno de system e parar os warnings
    int tamanho_senha;

    coletor = system(CLEAR);
	if(coletor == -1){
		cout << "Falha na limpeza da tela" <<endl;
	}
    cout << "Escolha uma das opcoes abaixo"<<endl;
    cout << "1 - cifrar" <<endl;
    cout << "2 - decifrar" <<endl;
    cout << "3 - quebrar arquivo cifrado" <<endl;
	//cout << "0 - encerrar o programa" <<endl;
	cout << "sua escolha: ";
	cin >> opcao;

    switch (opcao)
    {
    case '1':
        coletor = system(CLEAR);
		if(coletor == -1){
			cout << "Falha na limpeza da tela" <<endl;
		}
		cifragem.setCifrar(true);
        cout << "digite a senha: ";
        cin >> senha;
        cifragem.setSenha(senha);
		coletor = system(CLEAR);
		if(coletor == -1){
			cout << "Falha na limpeza da tela" <<endl;
		}
		cout << cifragem.Cripto();//exibe a mensagem cifrada
		cout <<endl;
		cout <<endl;
        cout << "Pressione ENTER para continuar."<<endl;
		getchar();
        getchar();
		coletor = system(CLEAR);
        if(coletor == -1){
			cout << "Falha na limpeza da tela" <<endl;
		}
		break;
    case '2':
		coletor = system(CLEAR);
        if(coletor == -1){
			cout << "Falha na limpeza da tela" <<endl;
		}
		cifragem.setCifrar(false);
        cout << "digite a senha: ";
        cin >> senha;
        cifragem.setSenha(senha);
		coletor = system(CLEAR);
		if(coletor == -1){
			cout << "Falha na limpeza da tela" <<endl;
		}
		cout << cifragem.Cripto();//exibe a mensagem decifrada
		cout <<endl;
		cout <<endl;
        cout << "Pressione ENTER para continuar."<<endl;
        getchar();
		getchar();
		coletor = system(CLEAR);
        if(coletor == -1){
			cout << "Falha na limpeza da tela" <<endl;
		}
		break;
    case '3':
        tamanho_senha = cifragem.EncontraTamanhoSenha();
        cout << "O candidato ao tamanho da senha eh: " << tamanho_senha << endl;
        break;
    default:
        coletor = system(CLEAR);
        cout << "Escolha uma das opcoes POSSIVEL"<<endl;
        cout << "1 - cifrar" <<endl;
        cout << "2 - decifrar" <<endl;
        cout << "3 - quebrar arquivo cifrado" <<endl;
		cout << "sua escolha: ";
        break;
    }
}

//configura o encerramento do menu
void Menu::setEncerrar(string encerrar){
    if(encerrar == "s")
        this->encerrar  = true;
}

//faz o loop do menu parar ou continuar
bool Menu::getEncerrar(){
    return this->encerrar;
}

/*********************************************************************************************************/

// Ataque utilizando metodo kasiski

vector<pair<string, vector<int>>> Vigenere::PosicoesTrigramas() {
    map<string, vector<int>> pos_trigrama;
    vector<string> tri_repetidos;
    vector<pair<string, vector<int>>> pos_tri_repetidos;
    
    regex pattern("[^a-z]");
    string mensagem_filtrada = regex_replace(this->mensagem, pattern, ""); // faz a exclusao de caracteres especiais da mensagem

    // salva os trigramas com suas respectivas posicoes
    for(int i = 0; i < mensagem_filtrada.length(); ++i) {
        string prox_trigrama = mensagem_filtrada.substr(i, 3);
        if (pos_trigrama.find(prox_trigrama) != pos_trigrama.end()) {
            pos_trigrama[prox_trigrama].push_back(i);
        } else {
            pos_trigrama[prox_trigrama] = {i};
        }
    }

    // verifica os trigramas que possuem 2 ou mais ocorrencias
    for(const auto& x : pos_trigrama) {
        if (x.second.size() >= 2) {
            tri_repetidos.push_back(x.first);
        }
    }

    // cria vetor contendo os trigramas com 2 ou mais ocorrencias junto com suas respectivas posicoes
    for(const string& x : tri_repetidos) {
        pos_tri_repetidos.push_back(make_pair(x, pos_trigrama[x]));
    }

    return pos_tri_repetidos;
}

vector<int> Vigenere::CalculaEspacos(const vector<int>& posicoes) {
    vector<int> espacos;

    for(int i = 0; i < posicoes.size() - 1; ++i) {
        espacos.push_back(posicoes[i + 1] - posicoes[i]);
    }

    return espacos;
}

vector<int> Vigenere::ObtemFatores(int num) {
    vector<int> fatores;

    for(int i = 1; i <= sqrt(num); ++i) {
        if (num % i == 0) {
            fatores.push_back(i);
            if (i != num / i) {
                fatores.push_back(num / i);
            }
        }
    }

    sort(fatores.begin(), fatores.end());

    return fatores;

}

int Vigenere::TamanhoSenha(const vector<vector<int>>& fatores) {
    vector<int> tamanhos_senha;
    map<int, int> lista;
    int maior_ocorr = 0;
    int tamanho_candidato;
    
    // armazena todos fatores candidatos para tamanhos da senha
    for(const vector<int>& fat : fatores) {
        for(int f : fat) {
            if(f > 1 && f < 26) {
                tamanhos_senha.push_back(f);
            }

        }
    }

    // armazena os possiveis tamanhos junto com suas ocorrencias
    for(int num : tamanhos_senha) {
        lista[num]++;
    }

    // busca pelo tamanho que possui maior ocorrencia
    for(const auto& x : lista) {
        if (x.second > maior_ocorr) {
            tamanho_candidato = x.first;
            maior_ocorr = x.second;
        }
    }

    return tamanho_candidato;

}


int Vigenere::EncontraTamanhoSenha() {
    // encontra trigramas repetidos com suas respectivas posicoes
    vector<pair<string, vector<int>>> pos_tri_repetidos;
    map<string, vector<int>> espacos_tri;
    vector<vector<int>> fatores;

    pos_tri_repetidos = PosicoesTrigramas();
    // for (const auto& x : pos_tri_repetidos) {
    //     cout << "Trigrama: " << x.first << ", Posicoes: ";
    //     for (int pos : x.second) {
    //         cout << pos << " ";
    //     }
    //     cout << endl;
    // }

    // calcula o espacamento dos trigramas
    for (const auto& x : pos_tri_repetidos) {
        const string& tri = x.first;
        const vector<int>& posicoes = x.second;
        vector<int> espacos = CalculaEspacos(posicoes);
        espacos_tri[tri] = espacos;
    }

    // for (const auto& x : espacos_tri) {
    //     cout << "Trigrama: " << x.first << ", Espacos: ";
    //     for (int esp : x.second) {
    //         cout << esp << " ";
    //     }
    //     cout << endl;
    // }

    // calculo dos fatores dos espacamentos
    for (const auto& x : espacos_tri) {
        const vector<int>& espacos = x.second;

        for (int esp : espacos) {
            fatores.push_back(ObtemFatores(esp));
        }
    }

    // for (const auto& fat : fatores) {
    //     cout << "Fatores: ";
    //     for (int factor : fat) {
    //         cout << factor << " ";
    //     }
    //     cout << endl;
    // }

    return TamanhoSenha(fatores);

}
