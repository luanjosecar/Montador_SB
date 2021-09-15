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
# Ou caso queira verificar a existência de Warnings
$ g++ --warn-all montador.cpp -o montador
# Executando o arquivo
$ ./montador file.asm

```

A saída da execução será um arquivo de mesmo nome porem com a extensão ".obj"

- Simulador :
  Não há restrições de entrada, porém se aconselha a utilizar os códigos gerados pelo montador.

```bash
# Montador
$ g++ simulador.cpp -o simulador
# Ou caso queira verificar a existência de Warnings
$ g++ --warn-all montador.cpp -o montador
# Executando o arquivo
$ ./simulador file.obj

```
