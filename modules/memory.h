
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include "tokenreader.h"
using namespace std;

class Memory
{
public:
    int space;
    vector<string> code;
    vector<string> codebase;
    string codename;
    vector<int> chunksnumber;

    void AddSpaces(vector<int> chuncks, vector<int> chunckSpace)
    {
    }

    void DefineVariables(string s)
    {
        codename = s;
        fstream newfile;
        TokenReader reader;
        newfile.open(s, ios::in);
        int line = 0;
        if (newfile.is_open())
        {
            string tp;
            while (getline(newfile, tp))
            {
                std::istringstream ss(tp);
                reader.GenerateTokens(tp);
                if (reader.tokens[0] == "" || reader.tokens.size() == 0)
                {
                    reader.ClearTokens();
                    continue;
                }
                reader.RemoveFront(2);
                if (line == 1)
                {
                    space = stoi(reader.tokens[0]);
                }
                if (line == 2)
                {
                    codebase = reader.tokens;
                }
                if (line == 3)
                {
                    code = reader.tokens;
                }
                line++;
                reader.ClearTokens();
            }
        }
    }

    void PrintMemory()
    {
        cout << codename << "---------------------" << endl
             << "SIZE : " << space << endl
             << "CODE : ";
        for (int i = 0; i < (signed)code.size(); i++)
        {
            cout << code[i] << " ";
        }
        cout << endl
             << "BASE : ";

        for (int i = 0; i < (signed)codebase.size(); i++)
        {
            cout << codebase[i] << " ";
        }
    }

    void WriteFile();
};