#include <iostream>
#include <vector>
#include <string>
#pragma once
#include "symboltable.h"

enum Func
{
    ADD = 1,
    SUB,
    MULT,
    DIV,
    JMP,
    JMPP,
    JMPN,
    JMPZ,
    COPY,
    LOAD,
    STORE,
    INPUT,
    OUTPUT,
    STOP
};

using namespace std;
class FunctionCheck
{
public:
    //Validation a;
    vector<string> basefunc{"ADD", "SUB", "MULT", "DIV", "JMP", "JMPP", "JMPN", "JMPZ", "COPY", "LOAD", "STORE", "INPUT", "OUTPUT", "STOP"};
    // TS ts;
    int base = 0;

    void Function(vector<string> &tokens, int &pc)
    {

        // this->ts = ts;
        bool aux = true;
        if (Validation::LabelFunction(tokens))
            base = 2;
        else
            base = 0;

        for (int i = 0; i < (signed)basefunc.size(); i++)
        {
            if (tokens[base] == basefunc[i])
            {
                tokens[base] = to_string(i + 1);
                switch (i + 1)
                {
                case ADD:
                case SUB:
                case MULT:
                case DIV:
                case JMP:
                case JMPP:
                case JMPN:
                case JMPZ:
                case LOAD:
                case STORE:
                    aux = FuncTypeA(tokens);
                    pc = pc + 2;
                    break;
                case COPY:
                    aux = FuncTypeC(tokens);
                    pc = pc + 3;
                    break;
                case INPUT:
                case OUTPUT:
                    aux = FuncTypeB(tokens);
                    pc = pc + 2;
                    break;
                case STOP:
                    pc++;
                    break;
                default:
                    aux = false;
                    // Erro função não encontrada
                    break;
                }
            }
        }
        if (aux == false)
        {
            //cout << "\nFunção não definida ou com erro" << tokens[0];
        }
    }

    bool FuncTypeA(vector<string> &tokens)
    {
        if ((signed)tokens.size() == (2 + base))
        {
            // Parte substituida para a criação do sistema
            // if (!Validation::CheckNumber(tokens[1]))
            // {
            //     if (TokenValue(tokens[1]) != "")
            //     {
            //         tokens[1] = TokenValue(tokens[1]);
            //     }
            // }
            return true;
        }
        else
        {
            return false;
        }
    }

    bool FuncTypeB(vector<string> &tokens)
    {
        if ((signed)tokens.size() == (1 + base))
        {
            return true;
        }
        else
            return false;
    }

    bool FuncTypeC(vector<string> &tokens)
    {
        // cout << "  " << tokens[0] << endl;
        if ((signed)tokens.size() == (4 + base))
        {
            if (tokens[2 + base] == ",")
            {
                // cout << "  " << tokens[1] << endl;
                // cout << "  " << tokens[3] << endl;

                // Substituição direta na função

                // if (!Validation::CheckNumber(tokens[1]) && TokenValue(tokens[1]) != "")
                // {

                //     tokens[1] = TokenValue(tokens[1]);
                // }
                // if (!Validation::CheckNumber(tokens[3]) && TokenValue(tokens[3]) != "")
                // {
                //     tokens[3] = TokenValue(tokens[3]);
                // }
                tokens.erase(tokens.begin() + 2 + base);
                return true;
            }
        }
        return false;
    }

    // string TokenValue(string name)
    // {
    //     for (int i = 0; i < (signed)ts.symbs.size(); i++)
    //     {
    //         if (name == ts.symbs[i].name && ts.symbs[i].status && !ts.symbs[i].secData)
    //             return ts.symbs[i].base;
    //     }
    //     return "";
    // }
};