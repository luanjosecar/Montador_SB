
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include "tokenvalidator.h"
using namespace std;

class Chunks
{
public:
    int chuncksNumber;
    vector<int> chunckSpace;
    vector<int> chunckPlace;
    vector<int> usedChunks;

    void ReadArgs(char const *arg[], int index)
    {
        chuncksNumber = stoi(arg[index]);
        for (int i = 1; i <= chuncksNumber; i++)
        {
            chunckSpace.push_back(stoi(arg[index + i]));
            chunckPlace.push_back(stoi(arg[index + i + chuncksNumber]));
        }
    }

    void PrintChunks()
    {
        for (int i = 0; i < (signed)chunckPlace.size(); i++)
        {
            cout << " CHUNK " << i << "--------------" << endl
                 << "SPACE : " << chunckSpace[i] << endl
                 << "PLACE : " << chunckPlace[i] << endl;
        }
    }

    bool CheckObjectFile(string s)
    {
        string temp = "";
        string aux1 = "";
        bool aux2 = false;
        for (int i = 0; i < (signed)s.length(); ++i)
        {
            char up = s[i];
            if (up == '.')
            {
                aux2 = true;
                continue;
            }
            if (aux2)
                aux1.push_back(up);
            else
                temp.push_back(up);
        }
        if (!temp.empty() && aux1 == "obj")
        {
            return true;
        }
        return false;
    }

    bool SuficientChunckSpace();
};