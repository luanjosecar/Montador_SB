#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class ErHandler
{
public:
    string message;

    void PrintError()
    {
        cout << "\n"
             << message;
    };

    void MissingRotules(int line)
    {
        cout << "Missing Rotules to be identified";
    };

    void DuplicatedRotules(int line)
    {
        cout << "Rotule already declareted at line " << line;
    };

    void RepetitiveRotules(int line)
    {
        cout << "Douplicated rotule at line  " << line;
    };

    void InvalidDirective(int line)
    {
        cout << "Invalid Directive at Line " << line;
    };

    void InvalidFunc(int line)
    {
        cout << "Invalid Instruction at line " << line;
    };

    void InvalidStruc(int line)
    {
        cout << "Invalid Instructions Structure at line " << line;
    };

    void InvalidToken(int line)
    {
        cout << "Invalid Token at line " << line;
    };
};