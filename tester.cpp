#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "modules\tokenreader.h"
#include "modules\tokenvalidator.h"
#include "modules\symboltable.h"
#include "modules\functioncheck.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string teste;
    teste = "ADD ALGO, ALGO2 MAISALGO";
    TokenReader a;
    a.GenerateTokens(teste);
    a.PrintTokens();
    return 0;
}
