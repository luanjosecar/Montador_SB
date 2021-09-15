#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "..\modules\symboltable.h"

using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> teste;
    teste.push_back("Labe2l");
    teste.push_back(":");
    teste.push_back("SPACE+5");
    TS a;

    a.SectionValues(teste);
    a.PrintTable();
    return 0;
}