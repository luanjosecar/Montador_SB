#include <iostream>
#include <vector>
#include <string>
#include <regex>
#pragma once

using namespace std;

class Validation
{
public:
    // Tipos de entrada
    // Com Label e comment
    // <labl> : <op> <data> ; <comment>
    // <labl> : <op> <data> <data> ; <comment>
    static bool CheckTokens(vector<string> token)
    {
        // Analise sintatica 1
        bool aux = true;
        int i = 0;
        if (token[1] == ":")
        {
            i = 2;
            if (!CheckString(token[0]))
                return false;
        }
        aux = ValidateTokens(i, token);
        return aux;
    }

    static bool ValidateTokens(int pos, vector<string> token)
    {
        bool aux = CheckString(token[pos]);
        int i = pos + 1;
        if (!aux)
            return aux;

        while (i < (signed)token.size())
        {
            aux = CheckNumber(token[i]) || CheckString(token[i]);
            if (!aux)
                return aux;
            i++;
        }

        return aux;
    }

    static bool CheckNumber(string s)
    {
        for (int i = 0; i < (signed)s.length(); i++)
        {
            if (isdigit(s[i]) == 0)
                return false;
        }
        return true;
    }

    static bool CheckString(string s)
    {

        regex regx("[@!#$%^&*()<>?/|}{~]");

        if (isdigit(s[0]) != 0)
            return false;

        if (s[0] == '_')
            return false;

        if (regex_search(s, regx) != 0)
            return false;

        return true;
    }

    static bool AnaliseLexa(vector<string> token)
    {
        for (int i = 0; i < (signed)token.size(); i++)
        {
            if (!(CheckNumber(token[i]) || CheckString(token[i])))
            {
                //cout << "  erro no item " << i << "  ";
                return false;
            }
        }
        return true;
    }

    static bool LabelDefinition(vector<string> token, string name)
    {
        if (token.size() > 1)
        {
            if (token[1] == ":" && name == token[0])
            {
                return true;
            }
        }
        return false;
    }

    static bool SectionAnalises(vector<string> token, bool state)
    {

        if ((signed)token.size() == 2)
        {
            if (token[0] == "SECTION" && token[1] == "TEXT")
                return false;
            if (token[0] == "SECTION" && token[1] == "DATA")
                return true;
        }
        return state;
    }
};
