
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

#include "tokenreader.h"
#include "symbols.h"
#include "tokenvalidator.h"

class TS
{
public:
    vector<Symbols> symbs;
    //Validation a;
    vector<string> Funcs{"ADD", "SUB", "MULT", "DIV", "JMP", "JMPP", "JMPN", "JMPZ", "COPY", "LOAD", "STORE", "INPUT", "OUTPUT", "STOP", "SPACE", "CONST", "SECTION", "DATA", "TEXT"};

    void AddSymbol(string name, int pos, int line, int value, bool status)
    {

        if (CheckToken(name))
        {

            UpdateSymbol(name, pos, line, value, status);
        }
        else
        {
            Symbols aux;
            aux.SetValues(name, line, pos, value, status);
            symbs.push_back(aux);
        }
    }
    // Update do simbolo
    void UpdateSymbol(string name, int pos, int line, int value, bool status)
    {

        if (!symbs[CheckTokenValue(name)].status)
            symbs[CheckTokenValue(name)].UpdateSymbolValue(line, pos, value, status);
    }
    // Modelo de Adicionar as Labels
    void TokenAdder(string name, int pos, int line, int value, int status)
    {

        if (CheckToken(name))
        {
            UpdateSymbol(name, pos, line, value, status);
        }
        else if (!CheckCaracteristc(name))
        {
            AddSymbol(name, pos, line, value, status);
        }
    }

    // Velidação do Label
    bool CheckCaracteristc(string name)
    {
        return CheckSpecial(name) || ValidFunction(name);
    }

    // Verifica se o token existe na TS
    bool CheckToken(string name)
    {
        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            if (name == symbs[i].name)
                return true;
        }
        return false;
    }

    // Verifica se o token em análise é uma função do sistema
    bool ValidFunction(string name)
    {
        for (int i = 0; i < (signed)Funcs.size(); i++)
        {
            if (name == Funcs[i])
            {
                return true;
            }
        }
        return false;
    }

    // Verifica se é um caracter especial
    bool CheckSpecial(string name)
    {
        return name == ":" || name == ",";
    }

    // Verifica se o SPACE tem algum valor adicional
    int SpaceValue(string name)
    {

        if (name == "SPACE")
            return 0;
        if (name.length() < 6)
            return -1;

        char aux2;
        string temp = "";
        const char *aux = name.c_str();
        if (strncmp(aux, "SPACE+", 10) > 0)
        {
            for (int i = 6; i < (signed)name.length(); i++)
            {
                aux2 = name[i];
                temp.push_back(aux2);
            }
        }
        if (Validation::CheckNumber(temp))
            return atoi(temp.c_str());
        else
            return -1;
    }

    // Verifica se a alocação esta acontecendo durante um SPACE TEXT ou DATA
    void SectionValues(vector<string> tokens)
    {
        if (tokens.size() == 3) // Caso LABEL : SPACE
        {
            if (SpaceValue(tokens[tokens.size() - 1]) != -1)
            {
                Symbols aux;
                aux.secData = true;
                aux.constFunc = false;
                aux.name = tokens[0];
                aux.constValue = to_string(SpaceValue(tokens[tokens.size() - 1]));
                symbs.push_back(aux);
            }
        }
        if (tokens.size() == 4 && tokens[2] == "CONST" && tokens[1] == ":" && Validation::CheckNumber(tokens[3]))
        {
            Symbols aux;
            aux.secData = true;
            aux.constFunc = true;
            aux.name = tokens[0];
            aux.constValue = tokens[3];
            symbs.push_back(aux);
        }
    }

    // Retorna a posição do token na tabela se o mesmo estiver definido
    int CheckTokenValue(string name)
    {
        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            if (name == symbs[i].name)
                return i;
        }

        return -1;
    }

    // Define o valor de uma LABEL
    void LabelSimpleSearch(vector<string> &token, string name, int pos)
    {
        int aux;
        aux = CheckTokenValue(name);
        if (aux >= 0 && pos > 0 && symbs[aux].status)
        {
            token[pos] = symbs[aux].base;
        }
    }

    // Adiciona os valores de PC para a SectionDATA
    void AddTextData(int pos, vector<string> &writer)
    {
        int value = pos + 1;
        string aux;
        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            if (symbs[i].secData)
            {
                // cout << symbs[i].constValue << " " << symbs[i].name << atoi(symbs[i].constValue.c_str()) << symbs[i].constFunc << endl;
                symbs[i].base = to_string(value);
                symbs[i].status = true;
                RoolBack(writer, symbs[i].name);

                if (symbs[i].constFunc)
                {
                    aux = symbs[i].base + " " + symbs[i].constValue;
                    writer.push_back(aux);
                    value++;
                }
                else
                {
                    for (int j = 0; j <= atoi(symbs[i].constValue.c_str()); j++)
                    {
                        aux = to_string(value) + " XX";
                        writer.push_back(aux);
                        value++;
                    }
                }
            }
        }
    }

    // -------------------------------------------------------------------
    void RoolBack(vector<string> &writer, string name)
    {

        TokenReader aux;
        if (CheckToken(name))
        {
            int temp = CheckTokenValue(name);

            for (int i = 0; i < (signed)symbs[temp].positions.size(); i++)
            {

                if (symbs[temp].positions[i] > 0)
                {
                    aux.GenerateTokens(writer[symbs[temp].lines[i]]);
                    // cout << symbs[temp].name << " " << symbs[temp].positions[i] << " " << aux.tokens.size() << endl;
                    for (int j = 0; j < (signed)aux.tokens.size(); j++)
                    {
                        if (aux.tokens[j] == symbs[temp].name)
                            aux.tokens[j] = symbs[temp].base;
                    }
                    //aux.tokens[symbs[temp].positions[i] + 1] = symbs[temp].base;
                    writer[symbs[temp].lines[i]] = aux.LineWrite("");
                    aux.ClearTokens();
                }
            }
        }
    }

    void PrintTable()
    {

        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            cout << symbs[i].name << "------------ " << symbs[i].base << " ---" << symbs[i].status << endl;
            cout << "Lines = ";
            for (int j = 0; j < (signed)symbs[i].lines.size(); j++)
            {
                cout << symbs[i].lines[j] << " ";
            }
            cout << "\n";
            cout << "Position = ";
            for (int j = 0; j < (signed)symbs[i].positions.size(); j++)
            {
                cout << symbs[i].positions[j] << " ";
            }
            cout << "\n";
            cout << "Values = ";
            for (int j = 0; j < (signed)symbs[i].value.size(); j++)
            {
                cout << symbs[i].value[j] << " ";
            }
            cout << "\n";
        }
    }
};