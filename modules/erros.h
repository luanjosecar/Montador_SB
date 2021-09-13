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

    void PrintError(){

    };

    void MissingRotules(int line)
    {
        string msg;
        msg = "Missing Rotules to be identified in line " + to_string(line);
        message.push_back(msg);
    };

    void DuplicatedRotules(int line)
    {
        string msg;
        msg = "Rotule already declareted at line " + line;
        message.push_back(msg);
    };

    void RepetitiveRotules(int line)
    {
        string msg;
        msg = "Douplicated rotule at line  " + line;
        message.push_back(msg);
    };

    void InvalidDirective(int line)
    {
        string msg;
        msg = "Invalid Directive at Line " + line;
        message.push_back(msg);
    };

    void InvalidFunc(int line)
    {
        string msg;
        msg = "Invalid Instruction at line " + line;
        message.push_back(msg);
    };

    void InvalidStruc(int line)
    {
        string msg;
        msg = "Invalid Instructions Structure at line " + line;
        message.push_back(msg);
    };

    void InvalidToken(int line)
    {
        string msg;
        msg = "Invalid Token at line " + line;
        message.push_back(msg);
    };
};