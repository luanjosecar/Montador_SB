
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include "tokenreader.h"
#include "functioncheck.h"
using namespace std;

class Memory
{
public:
    int space;
    vector<string> code;
    vector<string> codebase;
    string codename;

    int chunksused;

    void DefineVariables(string s)
    {
        codename = s;
        codename.resize(codename.size() - 4);
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

    bool CheckFunctionBitwise(int index)
    {
        string decode = codebase[0];

        if (index == (signed)(decode.length() - 1))
            return false;
        if (decode[index + 1] == '0')
            return false;

        return true;
    }

    void BitwisePrint(Chunks space, int used = 0)
    {
        int op = space.chunckPlace[used];
        int usedspace = used;
        int totalSpace = space.chunckSpace[used];
        string decoder = codebase[0];
        for (int i = 0; i < (signed)decoder.length(); i++)
        {
            if (totalSpace <= i)
            {
                //used++;
                usedspace++;
                op = space.chunckPlace[usedspace];

                totalSpace += space.chunckSpace[usedspace];
            }

            if (decoder[i] == '0')
            {
                if (i != 0)
                    cout << endl;
                cout << op << " " << code[i] << " ";
                if (CheckFunctionBitwise(i))
                    op += FunctionCheck::FunctionOP(stoi(code[i]));
                else
                    op += 1;
            }

            if (decoder[i] == '1')
            {
                // Falta ajustar para multiplos chunks sendo usados
                int auxspace = 0;
                int alocatedspace = 0;
                for (int j = used; j < (signed)space.chunckSpace.size(); j++)
                {
                    auxspace += space.chunckSpace[j];
                    if (stoi(code[i]) < auxspace)
                    {
                        cout << stoi(code[i]) + space.chunckPlace[j] - alocatedspace << " ";
                        break;
                    }
                    alocatedspace += space.chunckSpace[j];
                }
            }
        }
    }

    void BitwiseWrite(Chunks space, int used = 0)
    {

        fstream newfile;
        TokenReader a;
        string filename = codename + ".saida";

        newfile.open(filename, ios::out);

        int op = space.chunckPlace[used];
        int usedspace = used;
        int totalSpace = space.chunckSpace[used];
        string decoder = codebase[0];

        if (newfile.is_open())
        {
            for (int i = 0; i < (signed)decoder.length(); i++)
            {
                if (totalSpace <= i)
                {
                    //used++;
                    usedspace++;
                    op = space.chunckPlace[usedspace];

                    totalSpace += space.chunckSpace[usedspace];
                }

                if (decoder[i] == '0')
                {
                    if (i != 0)
                        newfile << endl;
                    newfile << op << " " << code[i] << " ";
                    if (CheckFunctionBitwise(i))
                        op += FunctionCheck::FunctionOP(stoi(code[i]));
                    else
                        op += 1;
                }

                if (decoder[i] == '1')
                {
                    // Falta ajustar para multiplos chunks sendo usados
                    int auxspace = 0;
                    int alocatedspace = 0;
                    for (int j = used; j < (signed)space.chunckSpace.size(); j++)
                    {
                        auxspace += space.chunckSpace[j];
                        if (stoi(code[i]) < auxspace)
                        {
                            newfile << stoi(code[i]) + space.chunckPlace[j] - alocatedspace << " ";
                            break;
                        }
                        alocatedspace += space.chunckSpace[j];
                    }
                }
            }
        }

        newfile.close();
    }

    void MapPrint(Chunks space, int used = 0)
    {
        int op = space.chunckPlace[used];
        int counter = 0;
        int totalSpace = space.chunckSpace[used];
        int usedspace = used;
        string decoder = codebase[0];
        for (int i = 0; i < (signed)code.size(); i++)
        {
            if (totalSpace <= i)
            {
                //used++;
                usedspace++;
                op = space.chunckPlace[usedspace];
                // opaux = op;
                totalSpace += space.chunckSpace[usedspace];
            }

            if (i != stoi(codebase[counter]))
            {
                if (i != 0)
                    cout << endl;
                cout << op << " " << code[i] << " ";
                if (i < stoi(codebase[counter]))
                    op += FunctionCheck::FunctionOP(stoi(code[i]));
                else
                    op += 1;
            }
            else
            {
                // cout << " code " << code[i] << " ";
                // Falta ajustar para multiplos chunks sendo usados
                int auxspace = 0;
                int alocatedspace = 0;
                for (int j = used; j < (signed)space.chunckSpace.size(); j++)
                {
                    auxspace += space.chunckSpace[j];
                    // cout << "Space " << auxspace << " ";
                    if (stoi(code[i]) < auxspace)
                    {
                        cout << stoi(code[i]) + space.chunckPlace[j] - alocatedspace << " ";
                        break;
                    }
                    alocatedspace += space.chunckSpace[j];
                }
                if (counter < (signed)codebase.size() - 1)
                    counter++;
            }
        }
    }

    void MapWrite(Chunks space, int used = 0)
    {

        fstream newfile;
        TokenReader a;
        string filename = codename + ".saida";

        newfile.open(filename, ios::out);

        int op = space.chunckPlace[used];
        int counter = 0;
        int totalSpace = space.chunckSpace[used];
        int usedspace = used;
        string decoder = codebase[0];

        if (newfile.is_open())
        {

            for (int i = 0; i < (signed)code.size(); i++)
            {
                if (totalSpace <= i)
                {
                    usedspace++;
                    op = space.chunckPlace[usedspace];
                    totalSpace += space.chunckSpace[usedspace];
                }

                if (i != stoi(codebase[counter]))
                {
                    if (i != 0)
                        newfile << endl;
                    newfile << op << " " << code[i] << " ";
                    if (i < stoi(codebase[counter]))
                        op += FunctionCheck::FunctionOP(stoi(code[i]));
                    else
                        op += 1;
                }
                else
                {

                    int auxspace = 0;
                    int alocatedspace = 0;
                    for (int j = used; j < (signed)space.chunckSpace.size(); j++)
                    {
                        auxspace += space.chunckSpace[j];
                        if (stoi(code[i]) < auxspace)
                        {
                            newfile << stoi(code[i]) + space.chunckPlace[j] - alocatedspace << " ";
                            break;
                        }
                        alocatedspace += space.chunckSpace[j];
                    }
                    if (counter < (signed)codebase.size() - 1)
                        counter++;
                }
            }
        }

        newfile.close();
    }

    void WriteFile(Chunks space, int used = 0)
    {
        // Define o tipo de escrita bitwise = true, mapa = false
        bool dectype = (codebase[0].length() > 1) && (codebase[0][0] = '0');

        if (dectype)
        {
            // BitwisePrint(space, used);
            BitwiseWrite(space, used);
        }
        else
        {
            // MapPrint(space, used);
            MapWrite(space, used);
        }
    }
};