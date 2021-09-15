#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "..\modules\tokenvalidator.h"

using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> teste;

    teste.push_back("SPACE+52");
    // teste.push_back("TEXT");
    Validation a;

    bool base = a.CkeckTokens(teste);

    cout << "LEXAL " << base << endl;

    base = a.CheckDuplicates(teste);

    cout << "DUPLICATES " << base << endl;

    base = a.LabelFunction(teste);

    cout << "LABEL DEFINITION " << base << endl;

    base = a.CheckLastString("SPACE+52");

    cout << "LABEL WITH PLUS " << base << endl;

    return 0;
}