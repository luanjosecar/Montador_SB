#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Labels
{
    int pc;
    int value;
};
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

class Simulator
{
public:
    vector<string> lines;

    void Simulate(vector<string> tp, string line)
    { // this->ts = ts;

        int aux;
        if (tp.size() == 2)
        {
            if (atoi(tp[1].c_str()) == STOP)
            {
                cout << "Simulação Terminada";
            }
            if (tp.size() >= 3)
            {

                switch (atoi(tp[1].c_str()))
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
                case COPY:
                case STOP:
                default:
                }
            }
        }
    }

    void
};