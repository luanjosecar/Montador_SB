#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "modules/tokenreader.h"
#include "modules/simulator.h"

using namespace std;
int main(int argc, char const *argv[])
{

    fstream newfile;
    newfile.open(argv[1], ios::in);

    TokenReader tr;
    Simulator sm;

    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {
            std::istringstream ss(tp);
            tr.GenerateTokens(tp);
            sm.AddPC(tr.tokens);
            tr.ClearTokens();
        }

        sm.Start();
        newfile.close(); //close the file object.
    }

    return 0;
}