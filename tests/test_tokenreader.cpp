#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "..\modules\tokenreader.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string teste;
    teste = ";";
    TokenReader a;
    a.GenerateTokens(teste);
    cout << "Tokens Size " << a.tokens.size() << endl;
    a.PrintTokens();
    return 0;
}
