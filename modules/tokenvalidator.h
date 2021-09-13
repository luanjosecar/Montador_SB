#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <regex>
#pragma once

using namespace std;

class Validation
{
public:
    // Analise inicial dos Tokens
    static bool CkeckTokens(vector<string> tokens)
    {
        int pos = 0;
        if (tokens.size() > 7)
            return false;
        if (LabelFunction(tokens))
            pos = 2;
        return ValidateTokens(pos, tokens);
    }

    // Verifica se é a definição de uma variável
    static bool LabelFunction(vector<string> tokens)
    {
        if (tokens.size() == 1)
        {
            return false;
        }
        if (tokens[1] == ":" && CheckString(tokens[0]))
            return true;
        return false;
    }

    // Verificação dos tokens validos
    static bool ValidateTokens(int pos, vector<string> tokens)
    {
        int i = 0;
        do
        {
            if (!(CheckNumber(tokens[i]) || CheckString(tokens[i])))
            {
                cout << tokens[i] << endl;
                break;
            }
            i++;
        } while (i < (signed)tokens.size());

        if (i == ((signed)tokens.size()))
            return true;
        return CheckLastString(tokens[tokens.size() - 1]);
    }

    // Verificação da ultima string
    static bool CheckLastString(string label)
    {
        // Falso Para o caso do LABEL < 7 CHARS
        if (label.size() < 6)
            return false;

        char aux2;
        string temp = "";
        const char *aux = label.c_str();
        if (strncmp(aux, "SPACE+", 10) > 0)
        {
            for (int i = 6; i < (signed)label.length(); i++)
            {
                aux2 = label[i];
                temp.push_back(aux2);
            }
        }
        //cout << temp << " " << aux << " " << strncmp(aux, "SPACE+", 10) << " " << label.length() << endl;
        return CheckNumber(temp);
    }

    // Busca por Números
    static bool CheckNumber(string s)
    {
        if (s == "")
            return false;

        for (int i = 0; i < (signed)s.length(); i++)
        {
            if (isdigit(s[i]) == 0)
                return false;
        }
        return true;
    }

    // Busca de Strings Validas sem caracteres especiais
    static bool CheckString(string s)
    {

        regex regx("[@!#$%^&*()<>+?/|}{~]");

        if (isdigit(s[0]) != 0)
            return false;

        if (s[0] == '_')
            return false;

        if (regex_search(s, regx) != 0)
            return false;

        return true;
    }

    // Verifica se Label duplas no sistema
    static bool CheckDuplicates(vector<string> tokens)
    {
        if (tokens.size() == 1)
            return false;
        for (int i = 0; i < (signed)tokens.size(); i++)
        {
            for (int j = 0; j < (signed)tokens.size(); j++)
            {
                if (tokens[i] == tokens[j] && i != j)
                    return true;
            }
        }
        return false;
    }

    static int SectionCheck(vector<string> token)
    {

        if ((signed)token.size() == 2)
        {
            if (token[0] == "SECTION" && token[1] == "TEXT")
                return 1;
            if (token[0] == "SECTION" && token[1] == "DATA")
                return 2;
        }
        return 0;
    }
};
