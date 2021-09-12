#include <iostream>
#include <vector>
#include <string>
#pragma once
using namespace std;

class Symbols
{
public:
    string name;
    vector<int> lines;     // Linha a ser substituido
    vector<int> positions; // Posição do vetor de substituição
    vector<int> value;     // Valor dentro da tabela de symbolos
    string base;           // Valor a ser substituido
    string constValue;     // Valor da Constante a ser construida
    bool constFunc;        // Verifica se é uma constante
    bool secData = false;  // Verifica se for adicionado da parte de Section
    bool status = false;   // Simbolo definido

    void UpdateSymbolValue(int line, int pos, int value, bool status)
    {
        this->lines.push_back(line);
        this->positions.push_back(pos);
        this->value.push_back(value);

        this->status = status || (this->status);
        if ((this->status) && this->secData)
        {
            this->base = to_string(value);
        }
    }

    void SetValues(string name, int line, int pos, int value, bool status)
    {
        this->name = name;
        this->value.push_back(value);
        this->lines.push_back(line);
        this->positions.push_back(pos);
        this->status = status;
        if (status)
        {
            this->base = to_string(value);
        }
    }

    void SetSection(string consValue, bool constState)
    {
        this->constFunc = constState;
        if (constState)
        {
            this->constValue = consValue;
        }
        this->secData = true;
    }
};
