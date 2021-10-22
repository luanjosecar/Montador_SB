#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "modules\symboltable.h"
#include "modules\tokenreader.h"
#include "modules\tokenvalidator.h"
#include "modules\erros.h"
#include "modules\functioncheck.h"
#include "modules\header.h"

using namespace std;
int main(int argc, char const *argv[])
{
    HeaderCheck header;
    TokenReader token;

    cout << header.ValidateArgs(argc, argv);
    // cout << argc << endl;
    // for (int i = 0; i <= argc; i++)
    // {
    //     cout << argv[i] << endl;
    // }
    return 0;
}
