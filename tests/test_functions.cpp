#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "..\modules\functioncheck.h"
#include "..\modules\tokenreader.h"
#include "..\modules\symboltable.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string teste = "COPY A,B";
    TokenReader b;
    FunctionCheck a;
    TS ts;
    int pc = 0;

    // Teste TS vazia
    b.GenerateTokens(teste);
    a.Function(b.tokens, pc);
    b.PrintTokens();
    cout << " -- Valor do PC " << pc << endl;
    b.ClearTokens();

    // Dfinindo um valor para A
    pc = 0;
    ts.AddSymbol("A", 1, 0, 4, true);
    b.GenerateTokens(teste);
    a.Function(b.tokens, pc);
    ts.LabelSimpleSearch(b.tokens, "A", 1);
    b.PrintTokens();
    cout << " -- Valor do PC " << pc << endl;
    b.ClearTokens();

    teste = "COPY B, A";
    pc = 0;
    ts.AddSymbol("A", 1, 0, 4, true);
    b.GenerateTokens(teste);
    a.Function(b.tokens, pc);
    ts.LabelSimpleSearch(b.tokens, "A", 2);
    b.PrintTokens();
    cout << " -- Valor do PC " << pc << endl;
    b.ClearTokens();

    teste = "ADD A";
    pc = 0;
    ts.AddSymbol("A", 1, 0, 4, true);
    b.GenerateTokens(teste);
    a.Function(b.tokens, pc);
    ts.LabelSimpleSearch(b.tokens, "A", 1);
    b.PrintTokens();
    cout << " -- Valor do PC " << pc << endl;
    b.ClearTokens();

    teste = "ADD B";
    pc = 0;
    ts.AddSymbol("A", 1, 0, 4, true);
    b.GenerateTokens(teste);
    a.Function(b.tokens, pc);
    b.PrintTokens();
    cout << " -- Valor do PC " << pc << endl;
    b.ClearTokens();

    teste = "STOP";
    pc = 0;
    ts.AddSymbol("A", 1, 0, 4, true);
    b.GenerateTokens(teste);
    a.Function(b.tokens, pc);
    b.PrintTokens();
    cout << " -- Valor do PC " << pc << endl;
    b.ClearTokens();

    return 0;
}