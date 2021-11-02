#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Labels
{
    int pc;
    int value;
};

struct CodeLine
{
    vector<string> tokens;
    string line;
};
enum Func
{
    ADD = 1,
    SUB,
    MUL,
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

class Simulator
{
public:
    vector<CodeLine> code;
    vector<Labels> lb;
    int ACC = 0;

    void Start()
    {
        //PrintLabels();
        for (int i = 0; i < (signed)code.size(); i++)
        {

            Simulate(code[i].tokens, i);
        }
    }

    void AddPC(vector<string> token)
    {
        vector<string> aux;
        CodeLine a;
        bool data = false;

        int pc = 0;
        for (int i = 0; i < (signed)token.size(); i++)
        {
            if (!data)
            {
                switch (atoi(token[i].c_str()))
                {
                case ADD:
                case SUB:
                case MUL:
                case DIV:
                case JMP:
                case JMPP:
                case JMPN:
                case JMPZ:
                case LOAD:
                case STORE:
                case OUTPUT:
                case INPUT:
                    aux.push_back(to_string(pc));
                    aux.push_back(token[i]);
                    aux.push_back(token[i + 1]);
                    pc = pc + 2;
                    i++;
                    break;
                case COPY:
                    aux.push_back(to_string(pc));
                    aux.push_back(token[i]);
                    aux.push_back(token[i + 1]);
                    aux.push_back(token[i + 2]);
                    pc = pc + 3;
                    i++;
                    i++;
                    break;
                case STOP:
                default:
                    aux.push_back(to_string(pc));
                    aux.push_back(token[i]);
                    pc = pc + 1;
                    data = true;
                    break;
                }

                a.tokens = aux;
                code.push_back(a);
                aux.clear();
            }
            else
            {
                aux.push_back(to_string(pc));
                aux.push_back(token[i]);
                pc = pc + 1;
                a.tokens = aux;
                code.push_back(a);
                aux.clear();
            }
        }

        SearchLabels();
    }

    void PrintCodeWithPC()
    {
        for (int i = 0; i < (signed)code.size(); i++)
        {
            for (int j = 0; j < (signed)code[i].tokens.size(); j++)
            {
                cout << code[i].tokens[j] << " ";
            }
            cout << endl;
        }
    }

    void Simulate(vector<string> tp, int &i)
    { // this->ts = ts;

        if (tp.size() == 2)
        {
            if (atoi(tp[1].c_str()) == STOP)
            {

                PrintData("STOP", tp[0]);
                //cout << "Simulação Terminada";
                exit(1);
            }
        }
        if (tp.size() >= 3)
        {

            switch (atoi(tp[1].c_str()))
            {
            case ADD:
                PrintData("ADD", tp[0]);
                ACC = ACC + MathFunc(tp);
                break;
            case SUB:
                PrintData("SUB", tp[0]);
                ACC = ACC - MathFunc(tp);
                break;
            case MUL:
                PrintData("MUL", tp[0]);
                ACC = ACC * MathFunc(tp);
                break;
            case DIV:
                PrintData("DIV", tp[0]);
                ACC = (int)(ACC / MathFunc(tp));
                break;
            case JMP:
            case JMPP:
            case JMPN:
            case JMPZ:
                i = JumpFunc(tp, i);
                break;
            case LOAD:
                PrintData("LOAD", tp[0]);
                LoadFunc(tp);
                break;
            case STORE:
                PrintData("STORE", tp[0]);
                StoreFunc(tp);
                break;
            case OUTPUT:
                PrintData("OUTPUT", tp[0]);
                OutputFunc(tp);
                break;
            case INPUT:
                PrintData("INPUT", tp[0]);
                InputFunc(tp);
                break;
            case COPY:
                PrintData("COPY", tp[0]);
                CopyFunc(tp);
                break;

            default:
                break;
            }
        }
    }

    void CopyFunc(vector<string> token)
    {
        lb[CheckLabel(token[3])].value = lb[CheckLabel(token[2])].value;
    }

    int MathFunc(vector<string> token)
    {

        for (int i = 0; i < (signed)lb.size(); i++)
        {
            if (atoi(token[2].c_str()) == lb[i].pc)
            {
                return lb[i].value;
            }
        }
        return atoi(token[2].c_str());
    }

    void LoadFunc(vector<string> token)
    {

        for (int i = 0; i < (signed)lb.size(); i++)
        {
            if (atoi(token[2].c_str()) == lb[i].pc)
                this->ACC = lb[i].value;
        }
    }

    void StoreFunc(vector<string> token)
    {

        for (int i = 0; i < (signed)lb.size(); i++)
        {
            if (atoi(token[2].c_str()) == lb[i].pc)
                lb[i].value = this->ACC;
        }
    }

    int JumpFunc(vector<string> token, int i)
    {

        if (atoi(token[1].c_str()) == JMP)
        {

            PrintData("JMP", token[0]);
            return CheckPC(token[2]);
        }
        if (atoi(token[1].c_str()) == JMPP && ACC > 0)
        {
            //Realiza Jump

            PrintData("JMPP", token[0]);
            return CheckPC(token[2]);
        }
        if (atoi(token[1].c_str()) == JMPN && ACC < 0)
        {
            PrintData("JMPN", token[0]);
            return CheckPC(token[2]);
        }
        if (atoi(token[1].c_str()) == JMPZ && ACC == 0)
        {
            PrintData("JMPZ", token[0]);
            return CheckPC(token[2]);
        }
        return i;
    }

    void InputFunc(vector<string> token)
    {
        int aux;
        cin >> aux;
        cin.ignore();
        cout << endl;
        lb[CheckLabel(token[2])].value = aux;
        cout << aux;
    }

    void OutputFunc(vector<string> token)
    {
        char aux;
        cout << endl
             << "OUTPUT " << lb[CheckLabel(token[2])].value << endl;

        while (1)
        {
            aux = cin.get();
            if (aux == '\n')
            {
                break;
            }
        }
    }

    int CheckPC(string s)
    {
        for (int i = 0; i < (signed)code.size(); i++)
        {
            if (s == code[i].tokens[0])
                return i - 1;
        }
        return atoi(s.c_str());
    }

    int CheckLabel(string s)
    {
        for (int i = 0; i < (signed)lb.size(); i++)
        {
            if (atoi(s.c_str()) == lb[i].pc)
            {
                return i;
            }
        }
        return atoi(s.c_str());
    }

    void SearchLabels()
    {
        Labels b;
        vector<string> tp;
        bool aux = false;
        for (int i = 0; i < (signed)code.size(); i++)
        {
            tp = this->code[i].tokens;

            if (tp.size() == 2 && tp[1] == "14")
                aux = true;
            if (aux)
            {
                b.pc = atoi(tp[0].c_str());
                b.value = atoi(tp[1].c_str());
                this->lb.push_back(b);
            }
        }
    }

    void PrintData(string op, string pc)
    {
        cout << "----------------------------------" << endl
             << "OP: " << op << " PC: " << pc << " ACC: " << ACC << endl;
    }

    void PrintLabels()
    {
        cout << "---------------------------------------------" << endl;
        for (int i = 0; i < (signed)lb.size(); i++)
        {
            cout << lb[i].value << " PC " << lb[i].pc << endl;
        }
    }
};