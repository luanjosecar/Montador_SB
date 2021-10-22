#include <iostream>
#include <vector>
#include <string>

#include "tokenvalidator.h"
using namespace std;
class HeaderCheck
{
public:
    string filename;
    vector<string> filemodel;
    vector<string> code;
    int filesize;
    int contador = 0;
    int execution;

    bool ValidateArgs(int argc, char const *argv[])
    {

        switch (argc)
        {
        case 2: // Caso de argumento simples apenas o nome do arquivo
            execution = 1;
            return FilenameValidation(argv[1]);
            break;
        case 4:
            if (strcmp(argv[1], "1"))
                execution = 2;

            if (strcmp(argv[2], "0"))
                execution = 3;
            return CheckStructure(argv);
            break;
        default:
            return false;
            break;
        }
    }

    bool CheckStructure(char const *argv[])
    {

        if (!(strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "-e") == 0))
        {

            return false;
        }

        if (!(strcmp(argv[2], "1") == 0 || strcmp(argv[2], "0") == 0))
        {

            return false;
        }

        return FilenameValidation(argv[3]);
    }

    bool FilenameValidation(string s)
    {
        string temp = "";
        string aux1 = "";
        bool aux2 = false;
        for (int i = 0; i < (signed)s.length(); ++i)
        {
            char up = s[i];
            if (up == '.')
            {
                aux2 = true;
                continue;
            }
            if (aux2)
                aux1.push_back(up);
            else
                temp.push_back(up);
        }
        if (!temp.empty() && aux1 == "asm")
        {
            filename = s;
            filename.resize(filename.size() - 3);
            return true;
        }
        return false;
    }

    void Bitmap(vector<string> tokens)
    {
        for (int i = 0; i < (signed)tokens.size(); i++)
        {
            if (Validation::CheckNumber(tokens[i]))
                filemodel.push_back("0");
            else
                filemodel.push_back("1");
        }
    }

    void Realocacao(vector<string> tokens)
    {

        for (int i = 0; i < (signed)tokens.size(); i++)
        {
            if (!Validation::CheckNumber(tokens[i]))
                filemodel.push_back(to_string(contador));
            contador++;
        }
    }

    void WriteFile()
    {
        fstream newfile;
        TokenReader a;
        string name = filename;
        name.resize(name.size() - 1);
        this->filename = this->filename + "obj";
        newfile.open(filename, ios::out);
        if (newfile.is_open())
        {
            newfile << "T : " << name << endl;
            newfile << "T : " << filesize << endl;
            newfile << "T : ";
            for (int i = 0; i < (signed)filemodel.size(); i++)
            {
                newfile << filemodel[i];
            }
            newfile << endl
                    << "H : ";
            for (int i = 0; i < (signed)code.size(); i++)
            {
                a.GenerateTokens(code[i]);

                for (int j = 0; j < (signed)a.tokens.size(); j++)
                {
                    if (j != 0)
                    {
                        newfile << a.tokens[j] << " ";
                    }
                }
                a.ClearTokens();
            }
            newfile.close();
        }
    }
};