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
		int pos_mensagem = BuscaIndice(letra, alfabeto); // busca a posicao da letra no alfabeto

		if (pos_mensagem != -1) { // caso em que a letra consta no alfabeto
			char char_senha = this->senha[j % (this->senha).length()]; // realiza a busca da letra da senha que servira para a etapa de cifracao/decifracao
			int pos_senha = BuscaIndice(char_senha, alfabeto);
			// Cifracao:   Ci = Pi + Ki (mod 26)
			// Decifracao: Pi = Ci - Ki + 26 (mod 26)
			int pos_resultado = (this->cifrar) ? ((pos_mensagem + pos_senha) % 26) : ((pos_mensagem - pos_senha + 26) % 26);
			resultado += alfabeto[pos_resultado];
			j++;
		} else { // caso em que a letra nao consta no alfabeto replica o caractere original
			resultado += letra;
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

    for (char &car : mensagem) {
        car = tolower(car);
    }

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
	cout << "Digite um número para escolher um dos " << numero_de_arquivos-1 << " arquivos fornecidos:" << endl;
	for(int i=1; i<numero_de_arquivos; i++){
		cout << "[" << i << "] - " << nomes_dos_arquivos[i] << endl;
	}
	cout << endl;
	cin >> escolha;
	if(escolha >=1 && escolha <= numero_de_arquivos-1){
		return escolha;
	}
	else
		return -1;
}

string Vigenere::getSenha(){
	return senha;
}

//escolhe qual operacao o programa vai fazer com o arquivo: cifrar, decifrar, ou quebrar a cifra descobrindo a senha
void Menu::Operacoes(Vigenere cifragem ){

	char opcao;
	string senha;
	int coletor; //variavel para o guardar o retorno de system e parar os warnings
	int tamanho_senha;
	int idioma;

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
    {
        coletor = system(CLEAR);
		if(coletor == -1){
			cout << "Falha na limpeza da tela" <<endl;
		}

        map<int, int> lista_candidatos = cifragem.EncontraTamanhosSenha();
		cout << "Digite [1] se o plaintext for em inglês, e [2] se ele for em português: ";
        cin >> idioma;
        while(true) {
            int maior_ocorr = 0;
            // busca pelo tamanho que possui maior ocorrencia
            for(const auto& x : lista_candidatos) {
                if (x.second > maior_ocorr) {
                    tamanho_senha = x.first;
                    maior_ocorr = x.second;
                }
            }
            cout << "O candidato ao tamanho da senha eh: " << tamanho_senha << endl;
            cifragem.EncontraSenha(idioma, tamanho_senha);
            cout << "Senha: " << cifragem.getSenha() << endl;
            cout << "Plaintext: " << endl;
            cifragem.setCifrar(false);
            cout << cifragem.Cripto() <<endl;
            string ataque_concluido;
            cout << "A senha quebrou a cifra? [s/n]: ";
            cin >> ataque_concluido;
			cout << endl;

            if (ataque_concluido != "s") {
                auto it = lista_candidatos.find(tamanho_senha);
				if (it != lista_candidatos.end()) {
        			lista_candidatos.erase(it); // remove a senha que nao conseguiu realizar o ataque
				}
            } else {
				break;
			}
            
        }

		break;
    }
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
	for(int i = 0; i < (int) mensagem_filtrada.length(); ++i) { //corrigido o warning de falta de casting
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

	for(int i = 0; i < (int) posicoes.size() - 1; ++i) { //corrigido o warning de falta de casting
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

map<int, int> Vigenere::EncontraTamanhosSenha() {
	vector<pair<string, vector<int>>> pos_tri_repetidos; // encontra trigramas repetidos com suas respectivas posicoes
	map<string, vector<int>> espacos_tri;
	vector<vector<int>> fatores;
    vector<int> tamanhos_senha;
    map<int, int> lista_candidatos;

	pos_tri_repetidos = PosicoesTrigramas();

	// calcula o espacamento dos trigramas
	for (const auto& x : pos_tri_repetidos) {
		const string& tri = x.first;
		const vector<int>& posicoes = x.second;
		vector<int> espacos = CalculaEspacos(posicoes);
		espacos_tri[tri] = espacos;
	}

	// calculo dos fatores dos espacamentos
	for (const auto& x : espacos_tri) {
		const vector<int>& espacos = x.second;

		for (int esp : espacos) {
			fatores.push_back(ObtemFatores(esp));
		}
	}

    // armazena todos fatores candidatos para tamanhos da senha
	for(const vector<int>& fat : fatores) {
		for(int f : fat) {
			if(f > 1 && f < 20) {
				tamanhos_senha.push_back(f);
			}
		}
	}

    // armazena os possiveis tamanhos junto com suas ocorrencias
	for(int x : tamanhos_senha) {
		lista_candidatos[x]++;
	}

    return lista_candidatos;

}

/*********************************************************************************************************/

// Análise de frequência

/*
dado uma chave de tamanho t, faz uma quantidade de tabelas t.
cada tabela conta a frequência de letras a cada t períodos.
*/
vector<map<char, float>> Vigenere::ListaDeTabelas(int tamanho_senha){
	vector<map<char, float>> lista_de_tabelas;
	map<char, int> contagem_de_letras;
	map<char, float> tabela_de_frequencia; //das letras do ciphertext referente a posição da chave (cada letra da chave gera uma tabela)
	map<char, int>::iterator it;
	float frequencia;
	vector<char> alfabeto = GeraAlfabeto();

	regex pattern("[^a-z]");
	string mensagem_filtrada = regex_replace(this->mensagem, pattern, "");//retira todos os caracteres de fora do alfabeto a-z minusculo

	//int total_de_letras = (int)mensagem_filtrada.length(); //tamanho total da mensagem
	int total;//suponha que a senha seja bad, o total seria o quantas vezes o 'b', o 'a', ou 'd' se repetem

	for(int i = 0; i<tamanho_senha; i++){
		total = 0;
		for(int j = i; j < (int) mensagem_filtrada.length(); j+= tamanho_senha)
			total++;
		for(int j = 0; j < 26; j++){
				contagem_de_letras.insert(make_pair(alfabeto[j], 0)); //inicializa com 0 todas as letras para em seguida efetuar a contagem
		}
		for(int j = i; j < (int) mensagem_filtrada.length(); j+= tamanho_senha){
			it = contagem_de_letras.find(mensagem_filtrada[j]);
			if(it != contagem_de_letras.end())
				contagem_de_letras.find(mensagem_filtrada[j])->second +=1; //se a letra já estava sendo contada, aumenta 1
		}
		for(it = contagem_de_letras.begin(); it != contagem_de_letras.end(); it++){
			//frequencia = (( (float) it->second)/( (float) total_de_letras) ); //calcula a frequencia e faz o casting
			//cout <<"freq " <<frequencia<<endl;
			frequencia = (( (float) it->second)/( (float) total) ); //calcula a frequencia e faz o casting
			tabela_de_frequencia.insert(make_pair(it->first, frequencia));
		}
		lista_de_tabelas.push_back(tabela_de_frequencia); // salva a tabela na lista
		contagem_de_letras.clear();
		tabela_de_frequencia.clear(); // limpa a tabela e a contagem para fazer a proxima rodada
	}

	/*for(int i = 0; i <tamanho; i++){
		cout <<"tabela "<< i <<endl;
		for(map<char,float>::iterator it = lista_de_tabelas[i].begin(); it != lista_de_tabelas[i].end(); it++){
			cout << it->first <<" "<< it->second<<endl;
		}
		cout <<endl;
	}*/

	return lista_de_tabelas;
}

//tabela de frequência das letras do idioma
//o método faz a leitura de um arquivo que contém a frequência de letras de um idioma
map<char, float> Vigenere::TabelaDeFrequencia(string nome_do_arquivo){

	map<char, float> tabela_de_frequencia;
	string linha;
	string frequencia;
	float frequencia2; //ambas as frequencias são o mesmo número, utilizadas para conversão de string para float
	//stringstream buffer; //variável para converter a string do arquivo em número ponto flutuante

	ifstream arquivo(nome_do_arquivo+".txt");

	if (!arquivo.is_open()) {
		cout << "Erro ao abrir o arquivo." << endl;
		exit(1);
	}

	//buffer.str(""); //limpa o buffer
	while(getline(arquivo, linha)){
		frequencia = linha.substr(3); //pega a substring com a frequencia em porcentagem
		frequencia2 = stof(frequencia);//converte a string para float
		frequencia2 = frequencia2/100; //retira do formato de porcentagem
		tabela_de_frequencia.insert(make_pair(linha[0], frequencia2)); //monta a tabela com os valores
	}

	arquivo.close();

	return tabela_de_frequencia;
}

//método que encontra a senha
void Vigenere::EncontraSenha(int idioma, int tamanho_senha){
	
	string nome_do_arquivo = "";
	map<char, float> tabela_de_frequencia_do_idioma;
	vector<map<char, float>> lista_de_tabelas = ListaDeTabelas(tamanho_senha);
	vector<float> lista1, lista2, lista3, lista4;
	map<char, float>::iterator it;
	float auxiliar, auxiliar2;
	vector<float>::iterator itr;
	int indice_de_k;
	string senha;
	vector<char> alfabeto = GeraAlfabeto();
	
	if(idioma == 1)
		nome_do_arquivo = "FrequenciaIngles";
	else if(idioma == 2)
		nome_do_arquivo = "FrequenciaPortugues";
	else{
		cout << "Opção de idioma inválida!" <<endl;
		exit(1);
	}

	tabela_de_frequencia_do_idioma = TabelaDeFrequencia(nome_do_arquivo);
	for(it = tabela_de_frequencia_do_idioma.begin(); it != tabela_de_frequencia_do_idioma.end(); it++){
		auxiliar = it->second;
		lista2.push_back(auxiliar);//lista 2 guarda todas as frequências das letras do idioma escolhido
	}

	for(int i=0; i < (int) lista_de_tabelas.size(); i++){
		auxiliar2 = 0;
		for(it = lista_de_tabelas[i].begin(); it != lista_de_tabelas[i].end(); it++){
			auxiliar = it->second;
			//cout << "for1 aux: " << auxiliar<<endl;
			lista1.push_back(auxiliar);//lista1 guarda todas as frequências da i-ésima tabela da lista de tabelas
		}
		for(int j = 0; j < (int) lista2.size(); j++){
			for(int k = 0; k < (int) lista1.size(); k++){
				auxiliar = lista1[k] * lista2[k];
				//cout << "for3 aux: " << auxiliar<<endl;
				lista3.push_back(auxiliar); //faz a listagem do produto de frequências da língua com os caracteres da i-ésima tabela
			}
			auxiliar = 0;
			for(int k = 0; k < (int) lista3.size(); k++){
				auxiliar = auxiliar + lista3[k];// realiza o somatório dos produtos de frequência
				//cout << "for4 aux: " << auxiliar<<endl;
			}
			//cout << "for2 aux: " << auxiliar<<endl;
			//cout << "for2 aux2: " << auxiliar2<<endl;
			if(auxiliar > auxiliar2)
				auxiliar2 = auxiliar; //salva o maior somatório
			lista4.push_back(auxiliar);
			auxiliar = lista1[0];
			lista1.erase(lista1.begin());
			lista1.push_back(auxiliar);// faz rotacionar a lista1 para que um dos somatórios da lista4 dê  aproximadamente 0.065 (maior valor)
			lista3.clear();
		}
		//cout << "aux2: "<< auxiliar2<<endl;
		itr = find(lista4.begin(), lista4.end(), auxiliar2);
		indice_de_k = distance(lista4.begin(), itr); //encontra o indice de uma letra da chave no alfabeto
		//cout << "k"<< i << ": " << indice_de_k <<endl;
		auxiliar = 0;
		//cout << lista1.size() <<endl;
		//cout << lista4.size() <<endl;
		//cout << lista3.size() <<endl;
		lista1.clear();
		lista4.clear();//limpa tudo para reutilizar na próxima iteração
		senha.push_back(alfabeto[indice_de_k]);
	}
	//cout << lista2.size() <<endl;
	setSenha(senha);
}