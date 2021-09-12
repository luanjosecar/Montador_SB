#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "modules\tokenreader.h"
#include "modules\tokenvalidator.h"
#include "modules\symboltable.h"
#include "modules\functioncheck.h"
using namespace std;

void WriteFile(string s)
{
    fstream newfile;
    newfile.open("file.asm", ios::out);
    if (newfile.is_open())
    {
        newfile << s << "\n";
        newfile.close();
    }
}

/*
Itens que estão faltando
Fazer percorrer a tabela de penências das variáveis toda vez que ela for achada
Fazer a transformação de dados para o section data e section text
Escrever o código em um arquivo de mesmo nome que o de entrada
*/

int main(int argc, char const *argv[])
{
    fstream newfile;

    TokenReader reader;
    Validation check;
    TS symbs;
    FunctionCheck funcs;

    vector<string> write;
    int line = 0;
    int pc = 0;
    bool sectionText = false;

    newfile.open(argv[1], ios::in);

    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {
            std::istringstream ss(tp);
            reader.GenerateTokens(tp);

            // ----------------------------------------------- primeiros testes

            // Análise da estrutura lexa do sistema
            if (Validation::CkeckTokens(reader.tokens))
            {
                //cout << "   -- L1 OK";
            }
            else
            {
                cout << "  -- erro L1 " << reader.tokens.size() << endl;
            }

            // Analise sintática 1
            if (!(Validation::CheckDuplicates(reader.tokens)))
            {
                //cout << "   -- S1 OK";
            }
            else
            {
                cout << "  -- erro S1 " << reader.tokens.size() << endl;
            }

            //--------------------------------------------------
            // Validação dos valores na SECTION DATA *******************************
            if (Validation::SectionCheck(reader.tokens))
            {
                sectionText = !sectionText;
                reader.ClearTokens();
                continue;
            }

            if (sectionText)
            {
                symbs.SectionValues(reader.tokens);
            }
            //***********************************************************************

            else
            {
                // Roda a analise de funções
                funcs.Function(reader.tokens, pc);
                // Verifica se o item em análise é uma Label
                for (int i = 0; i < (signed)reader.tokens.size(); i++)
                {
                    symbs.TokenAdder(reader.tokens[i], i, line, pc, (Validation::LabelFunction(reader.tokens) && i == 0));
                    symbs.LabelSimpleSearch(reader.tokens, reader.tokens[i], i);
                }
                if (Validation::LabelFunction(reader.tokens))
                    reader.RemoveFront(2);

                reader.PrintTokens();
            }

            line++;

            reader.ClearTokens();
        }

        // // cout << endl;

        // //cout << tp << "\n";

        newfile.close(); //close the file object.
    }

    // for (int i = 0; i < (signed)write.size(); i++)
    // cout << write[i] << endl;
    // symbs.PrintTable();
    return 0;
}
