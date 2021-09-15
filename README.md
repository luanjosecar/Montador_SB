# Montador_SB

## Projeto referênte a Materia de Software Básicos - Universidade de Brasilia

Aluno : Luan José de Almeida Cardoso  
Matrícula : 14/0150161

## Copilador

Todo o sistema foi feito com base na linguagem C++, foi utlizado o Windows como SO.
O código foi feito com o auxilio do MinGW, para auxilio de versão foi executado o código:

```bash
$ g++ --version

g++.exe (MinGW.org GCC-6.3.0-1) 6.3.0
Copyright (C) 2016 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

```

## Executando o código

Para executa-lo seja na plataforma Linux ou Windows, realiza-se os seguintes comandos, dentro do diretório base :

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
  Não há restrições de entrada, porem se aconselha a utlizar os códigos gerados pelo montador.

```bash
# Montador
$ g++ simulador.cpp -o simulador
# Ou caso queira verificar a existência de Warnings
$ g++ --warn-all montador.cpp -o montador
# Executando o arquivo
$ ./simulador file.obj

```
