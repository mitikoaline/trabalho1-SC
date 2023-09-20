# trabalho1-SC

## Alunos:
Matheus Guaraci - 180046951

Aline Mitiko - 170004601

## Comando para compilar:
g++ -std=c++20 -g -Wall -O2 main.cpp Vigenere.cpp -o main

## Comando para verificação de erros e vazamento de memória
valgrind --leak-check=full ./main <nome_do_arquivo>

## Como utilizar o programa:
ao executar o programa, escreva o(s) nome(s) do(s) arquivo(s) de teste sem a extensão:

### ./main <nome_do_arquivo1> <nome_do_arquivo2> ... <nome_do_arquivoN>

em seguida, escolha uma das 3 opções disponíveis.


a opção 1 faz a cifragem utilizando uma chave fornecida pelo usuário.


a opção 2 decifra utilizando uma chave fornecida pelo usuário.


a opção 3 utiliza o arquivo para recuperar a chave e então decifra a mensagem.
