
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

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
        bool temp = false;
        for (int i = 0; i < (signed)symbs.size(); i++)
        {

            if (name == symbs[i].name)
            {
                symbs[i].UpdateSymbolValue(line, pos, value, status);
                temp = true;
                break;
            }
        }
        if (!temp)
        {
            Symbols aux;
            aux.SetValues(name, line, pos, value, status);
            this->symbs.push_back(aux);
        }
    }

    void UpdateSymbol(string name, int pos, int line, int value, bool status)
    {
        for (int i = 0; i < (signed)symbs.size(); i++)
        {

            if (name == symbs[i].name)
            {
                symbs[i].UpdateSymbolValue(line, pos, value, status);
                break;
            }
        }
    }

    bool CheckSymbol(string name)
    {
        for (int i; i < (signed)symbs.size(); i++)
        {
            if (name == symbs[i].name)
                return true;
        }
        return false;
    }

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

    bool CheckSpecial(string name)
    {
        // True se for um simbolo sozinho valido

        return name == ":" || name == ",";
    }

    void ValidateSymbol(string name, int pos, int line, int value, bool status)
    {
        // Adiciona uma nova label
        if (status && !ValidFunction(name) && !(Validation::CheckNumber(name)) && !CheckSpecial(name))
        {
            AddSymbol(name, pos, line, value, status);
            // cout << "Label " << name << " Adcionada Com valor " << value << endl;
        }
        else if (CheckUsedToken(name) == -2 && !ValidFunction(name) && !(Validation::CheckNumber(name)) && !CheckSpecial(name))
        {
            // cout << "Label " << name << " Adcionada Com valor " << value << endl;
            AddSymbol(name, pos, line, value, false);
        }
        else if (!ValidFunction(name) && !(Validation::CheckNumber(name)) && !CheckSpecial(name))
        {
            // cout << "Label " << name << " Update in value " << value << endl;
            UpdateSymbol(name, pos, line, value + 1, status);
        }
        // Update da Label
    }

    void LabelConstCheck(vector<string> tokens)
    {
        if (tokens[2] == "CONST" && tokens[1] == ":")
        {
            if (Validation::CheckNumber(tokens[3]))
            {
                Symbols aux;
                aux.SetValues(tokens[0], 0, 0, 0, true);
                aux.SetSection(tokens[3], true);
                symbs.push_back(aux);
            }
        }
    }

    void LabelSpaceCheck(vector<string> tokens)
    {
        if (tokens[2] == "SPACE" && tokens[1] == ":")
        {
            Symbols aux;
            aux.SetValues(tokens[0], 0, 0, 0, true);
            aux.SetSection("", false);
            symbs.push_back(aux);
        }
    }

    void CheckLabelValue(vector<string> tokens)
    {
        if (tokens.size() == 4)
            LabelConstCheck(tokens);
        if (tokens.size() == 3)
            LabelSpaceCheck(tokens);
    }

    void PrintTable()
    {

        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            cout << symbs[i].name << "------------ " << symbs[i].base << endl;
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

    int CheckUsedToken(string name)
    {
        bool aux = true;
        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            // cout << name << " - - " << symbs[i].name << " " << symbs[i].status << " " << symbs[i].secData << " " << symbs[i].base << endl;
            if (name == symbs[i].name && symbs[i].status && !symbs[i].secData)
                return i;
        }
        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            // cout << name << " - - " << symbs[i].name << " " << symbs[i].status << " " << symbs[i].secData << " " << symbs[i].base << endl;
            if (name == symbs[i].name && !symbs[i].secData)
                aux = false;
        }
        if (aux)
            return -2;
        return -1;
    }

    void LabelSimpleSearch(vector<string> &token, string name, int pos)
    {

        int aux;
        aux = CheckUsedToken(name);
        if (aux >= 0)
        {
            token[pos] = symbs[aux].base;
        }
    }

    void AddTextData(int pos)
    {
        int value = pos + 1;
        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            if (symbs[i].secData)
            {
                symbs[i].base = to_string(value);
                value++;
            }
        }
    }
};