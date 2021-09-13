#include <iostream>
#include <vector>
#include <string>
#include <regex>
#pragma once
#include "symboltable.h"
using namespace std;

class TokenReader
{
public:
    vector<string> tokens;

    void GenerateTokens(string s)
    {
        if (s == "")
        {
            tokens.push_back("");
            return;
        }
        string temp = "";
        for (int i = 0; i < (signed)s.length(); ++i)
        {
            char up = toupper(s[i]);
            switch (up)
            {
            case ' ':
                AddToken(temp);
                temp = "";
                break;
            case ';':
                AddToken(temp, ";");
                temp = "";
                break;
            case ':':
                AddToken(temp, ":");
                temp = "";
                break;
            case ',':
                AddToken(temp, ",");
                temp = "";
                break;
            default:
                temp.push_back(up);
                break;
            }
        }
        AddToken(temp);
        RemoveComments();
    }

    void PrintTokens()
    {
        for (int i = 0; i < (signed)tokens.size(); ++i)
            cout << tokens[i] << " ";
        cout << endl;
    }

    void AddToken(string s, string separetor = "")
    {
        if (s != "")
        {
            tokens.push_back(s);
        }
        if (separetor != "")
        {
            tokens.push_back(separetor);
        }
    }

    void RemoveComments()
    {

        for (int i = 0; i < (signed)tokens.size(); ++i)
        {
            if (tokens[i] == ";")
            {
                Remover(tokens.size() - i);
            }
        }
    }

    void Remover(int i)
    {
        if (i > 0)
        {
            tokens.pop_back();
            Remover(--i);
        }
    }

    void ClearTokens()
    {
        tokens.clear();
    }

    // Função para remover principalmente as labels
    void RemoveFront(int n)
    {
        for (int i = 0; i < n; i++)
            tokens.erase(tokens.begin());
    }

    string LineWrite(string pc)
    {
        string aux = pc + " ";
        if (aux == " ")
            aux = "";
        for (int i = 0; i < (signed)tokens.size(); i++)
        {
            aux = aux + tokens[i] + " ";
        }
        return aux;
    }

    void PrintWriter(vector<string> writer)
    {
        for (int i = 0; i < (signed)writer.size(); i++)
            cout << writer[i] << endl;
    }
};
