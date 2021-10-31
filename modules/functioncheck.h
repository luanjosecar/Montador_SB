#include <iostream>
#include <vector>
#include <string>
#pragma once

enum Func
{
    ADD = 1,
    SUB,
    MULT,
    DIV,
    JMP,
    JMPN,
    JMPP,
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
    vector<string> basefunc{"ADD", "SUB", "MULT", "DIV", "JMP", "JMPN", "JMPP", "JMPZ", "COPY", "LOAD", "STORE", "INPUT", "OUTPUT", "STOP"};
    //ErrHandler err;
    int base = 0;

    bool Function(vector<string> &tokens, int &pc)
    {

        // this->ts = ts;
        bool aux = true;
        if (tokens.size() == 2 && tokens[1] == ":")
            return true;
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
                case OUTPUT:
                case INPUT:
                    aux = FuncTypeA(tokens);
                    pc = pc + 2;
                    if (!aux)
                        base = -1;
                    return aux;
                    break;
                case COPY:
                    aux = FuncTypeC(tokens);
                    pc = pc + 3;
                    if (!aux)
                        base = -1;
                    return aux;
                    break;
                case STOP:
                    aux = FuncTypeB(tokens);
                    pc = pc + 1;
                    if (!aux)
                        base = -1;
                    return aux;
                    break;
                default:
                    base = -2;
                    return false;
                    // Erro função não encontrada
                    break;
                }
            }
            if (tokens[base] == "SPACE" || tokens[base] == "CONST" || Validation::CheckLastString(tokens[base]))
            {
                return true;
            }
        }
        base = 0;
        return false;
    }
    // Verificação de funções de 2 elementos
    bool FuncTypeA(vector<string> &tokens)
    {
        if ((signed)tokens.size() == (2 + base))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    // Verificação de funções com 1 elemento
    bool FuncTypeB(vector<string> &tokens)
    {
        if ((signed)tokens.size() == (1 + base))
        {
            return true;
        }
        else
            return false;
    }
    // Verificação de funções com 3 elementos
    bool FuncTypeC(vector<string> &tokens)
    {
        if ((signed)tokens.size() == (4 + base))
        {
            if (tokens[2 + base] == ",")
            {
                tokens.erase(tokens.begin() + 2 + base);
                return true;
            }
        }
        return false;
    }

    static int FunctionOP(int name)
    {
        switch (name)
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
        case OUTPUT:
        case INPUT:
            return 2;
        case COPY:
            return 3;
        case STOP:
            return 1;
        default:
            return 1;
            // Erro função não encontrada
            break;
        }
    }
};