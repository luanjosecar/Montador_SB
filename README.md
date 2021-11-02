# Montador_SB

- Projeto referente a Materia de Software Básicos - Universidade de Brasilia

Aluno : Luan José de Almeida Cardoso  
Matrícula : 14/0150161

git : https://github.com/luanjosecar/Montador_SB

## Copilador

Todo o sistema foi feito com base na linguagem C++, foi utilizado o Windows como SO.
O código foi feito com o auxílio do MinGW, para auxílio de versão foi executado o código:

```bash
$ g++ --version

g++.exe (MinGW.org GCC-6.3.0-1) 6.3.0
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

```

## Executando o código

Para clonar o repositório podemos executar os seguinte comando antes da compilação:

```bash
# CLonar Repositório
$ git clone https://github.com/luanjosecar/Montador_SB
# Mover para a pasta do diretório
$ cd Montador_SB
```

Para executa-lo seja na plataforma Linux ou Windows, realiza-se os seguintes comandos, dentro do diretório principal :

- Montador :
  A entrada do montador é explicitamente de arquivos de extensão ".asm"

```bash
# Montador
$ g++ montador.cpp -o montador
# Executando o arquivo - Montador simples
$ ./montador file.asm
# Execução do código para a saida do Mapa de registradores do sistema
$ ./montador -r 0 file.asm
# Execução do código para a saida BitMap do sistema
$ ./montador -r 1 file.asm

```

A saída da execução será um arquivo de mesmo nome porem com a extensão ".obj"

Paca cada uma das execuções teremos um código no formato

```
H : "Nome do Arquivo"
H : "Tamanho do código em memória"
H : "Mapa de bits ou Mapa de Registradores"
T : "Código Objeto"
```

Para a atribuição do argumento "-r" no código não existirá verificação de erros, para que seja possível identificar erros no código deve-se utilizar a tag "e". A saída associada ao mapa de bit ou de registradores continua a mesma.

```bash
# Execução do código com análise de erros
$ ./montador -e 0 file.asm

```

- Simulador :
  Não há restrições de entrada, porém se aconselha a utilizar os códigos gerados pelo montador.

```bash
#Simulador
$ g++ simulador.cpp -o simulador
# Ou caso queira verificar a existência de Warnings
$ g++ --warn-all montador.cpp -o montador
# Executando o arquivo
$ ./simulador file.obj

```

- Carregador :

O carregador pode ser executado da forma:

```bash
# Carregador
$ g++ carregador.cpp -o carregador
# Exemplo de execução
$ ./simulador files.obj 3 10 30 58 10 250 560
```

Tendo sua estrutura de argumentos na forma

```
"files" Number_of_chunks  Chunk_Space Chunk_Place
```

O valor de Number_of_chunks define o número de entradas após a execução, sendo necessário n itens definidos, para cada chunk de memória se é necessário especificar um valor do espaço de memória total do mesmo, e seu ponto de inicio, nesta ordem.

O código aponta apenas dois casos de erros, de argumentos passados, ou caso exista algum chunk que poderá ser sobrescrito pelos valores especificados.

O resultado final da execução são n-arquivos de extensão ".saida" com o nome do arquivo, alocando os espaços associados a cada um dos códigos nos chunks de memórias associados.
Para este sistema não foi possibilitado a utilização de um mesmo chunk de memória para múltiplos códigos, assim cada chunk terá apenas um código associado, porém cada código poderá estar associado a múltiplos chunks. Esta associação ocorre de forma linear, então o primeiro código definido nos argumentos será aquele que será alocado primeiro no sistema.
