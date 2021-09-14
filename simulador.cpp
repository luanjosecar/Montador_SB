#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "modules/tokenreader.h"

using namespace std;
int main(int argc, char const *argv[])
{

    fstream newfile;
    newfile.open(argv[1], ios::in);

    int line_file = 0;
    int ADC = 0;
    TokenReader tr;

    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {
            line_file++;
            std::istringstream ss(tp);
            tr.GenerateTokens(tp);
        }
    }
    return 0;
}