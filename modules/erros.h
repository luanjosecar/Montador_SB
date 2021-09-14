#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class ErrHandler
{
public:
    vector<string> message;

    void MissingRotules()
    {
        string msg;
        msg = "Erro Semântico - Declaração de rótulos ausentes na linha ";
        message.push_back(msg);
    };

    void DuplicatedRotules(int line)
    {
        string msg;
        msg = "Erro Semântico - Dois Rótulos na mesma linha " + to_string(line);
        message.push_back(msg);
    };

    void RepetitiveRotules(int line)
    {
        string msg;
        msg = "Erro Semântico - Declaração de Rótulos repetidos  " + to_string(line);
        message.push_back(msg);
    };

    void InvalidDirective(int line)
    {
        string msg;
        msg = "Erro Semântico - Diretivas Invalidas na linha " + to_string(line);
        message.push_back(msg);
    };

    void InvalidFunc(int line)
    {
        string msg;
        msg = "Erro Sintático - Instrução invalida " + to_string(line);
        message.push_back(msg);
    };

    void InvalidStruc(int line)
    {
        string msg;
        msg = "Erro sintático - Instrução com a quantidade de operandos errada " + to_string(line);
        message.push_back(msg);
    };

    void InvalidToken(int line)
    {
        string msg;
        msg = "Erro Lexo - Token Invalido na linha " + to_string(line);
        message.push_back(msg);
    };

    void PrintErros()
    {
        for (int i = 0; i < (signed)message.size(); i++)
        {
            cout << message[i] << endl;
        }
    }
};