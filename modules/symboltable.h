
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
        else if (!CheckCaracteristc(name) && !Validation::CheckNumber(name))
        {
            AddSymbol(name, pos, line, value, status);
        }
    }

    void CheckTokenCS(vector<string> tokens)
    {
        if (tokens.size() == 2 && tokens[1] == ":")
            return;
        if (tokens[2] == "CONST")
        {
            symbs[CheckTokenValue(tokens[0])].constFunc = true;
            symbs[CheckTokenValue(tokens[0])].constValue = tokens[3];
        }
        else if (SpaceValue(tokens[2]) != -1)
        {
            symbs[CheckTokenValue(tokens[0])].constFunc = false;
            symbs[CheckTokenValue(tokens[0])].constValue = to_string(SpaceValue(tokens[2]));
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
        string base;
        aux = CheckTokenValue(name);

        if (aux >= 0 && pos > 0 && symbs[aux].status)
        {
            if (Validation::CheckLastString(token[pos]))
            {
                base = to_string(atoi(symbs[aux].base.c_str()) + atoi(Validation::CheckPlusLabelInt(token[pos]).c_str()));
            }
            else
            {
                base = symbs[aux].base;
            }
            token[pos] = base;
        }
    }

    // Adiciona os valores de PC para a SectionDATA
    void AddTextData(int pos, vector<string> &writer)
    {

        string aux;
        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            if (symbs[i].secData)
            {

                symbs[i].base = to_string(pos);
                symbs[i].status = true;
                RoolBack(writer, symbs[i].name, pos);

                if (symbs[i].constFunc)
                {
                    aux = symbs[i].base + " " + symbs[i].constValue;
                    writer.push_back(aux);
                    pos++;
                }
                else
                {
                    for (int j = 0; j <= atoi(symbs[i].constValue.c_str()); j++)
                    {
                        aux = to_string(pos) + " 00";
                        writer.push_back(aux);
                        pos++;
                    }
                }
            }
        }
    }

    void ConstSpaceFunc(vector<string> &tokens, int &pc, vector<string> &writer, int &aux1)
    {
        string aux;
        if (tokens[0] == "CONST")
        {
            tokens.erase(tokens.begin());
            pc++;
        }
        if (tokens[0] == "SPACE")
        {
            tokens.erase(tokens.begin());
            tokens.push_back("X");
            pc++;
        }

        if (Validation::CheckLastString(tokens[0]))
        {

            for (int i = 0; i < atoi(Validation::CheckPlusLabelInt(tokens[0]).c_str()) - 1; i++)
            {
                aux = to_string(aux1) + " 00";
                writer.push_back(aux);
                aux1++;
                pc++;
            }
            tokens[0] = "00";
            pc++;
        }
    }

    void RoolLabel(vector<string> &tokens, string label, int &pc, vector<string> &writer)
    {

        string aux;
        if (label == "")
            return;
        if (tokens[0] == "CONST")
        {
            // Erro neste instante de tamanho
            if (tokens.size() < 2)
                return;
            symbs[CheckTokenValue(label)].constFunc = true;
            symbs[CheckTokenValue(label)].constValue = tokens[1];
            writer.push_back(to_string(pc) + " " + tokens[1]);
            pc++;
            return;
        }
        if (tokens[0] == "SPACE")
        {
            tokens.erase(tokens.begin());
            symbs[CheckTokenValue(label)].constFunc = false;
            writer.push_back(to_string(pc) + " 00");
            pc++;
            return;
        }
        if (Validation::CheckLastString(tokens[0]))
        {
            symbs[CheckTokenValue(label)].constFunc = false;
            symbs[CheckTokenValue(label)].constValue = Validation::CheckPlusLabelInt(tokens[0]);
            for (int i = 0; i < atoi(Validation::CheckPlusLabelInt(tokens[0]).c_str()); i++)
            {
                aux = to_string(pc) + " 00";
                writer.push_back(aux);
                pc++;
            }
            return;
            // Falta adicionar o número de loops do sistema
        }
    }

    // -------------------------------------------------------------------
    void RoolBack(vector<string> &writer, string name, int pos = 0)
    {

        TokenReader aux;
        string base = "";
        string numb = "";
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
                        if (Validation::CheckLastString(aux.tokens[j]))
                        {
                            if (pos != 0)
                                numb = to_string(pos + atoi(Validation::CheckPlusLabelInt(aux.tokens[j]).c_str()));
                            else
                                numb = to_string(atoi(symbs[temp].base.c_str()) + atoi(Validation::CheckPlusLabelInt(aux.tokens[j]).c_str()));
                            base = Validation::CheckPlusLabelToken(aux.tokens[j]);
                        }
                        else
                        {
                            if (pos != 0)
                                numb = to_string(pos);
                            else
                                numb = symbs[temp].base;
                            base = aux.tokens[j];
                        }
                        if (base == symbs[temp].name)
                        {
                            aux.tokens[j] = numb;
                        }
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
            cout << symbs[i].name << "------------ " << symbs[i].base << " --- " << symbs[i].constValue << endl;
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

    void NonDef(vector<string> &message)
    {
        string aux;
        for (int i = 0; i < (signed)symbs.size(); i++)
        {
            if (symbs[i].status == false)
            {
                aux = "Erro Semântico - Declaração de rótulos ausentes : " + symbs[i].name;
                message.push_back(aux);
            }
        }
    }
};