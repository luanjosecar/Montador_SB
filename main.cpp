#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "modules\symboltable.h"
#include "modules\tokenreader.h"
#include "modules\tokenvalidator.h"
#include "modules\erros.h"

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
    TS symbs;
    FunctionCheck funcs;
    ErrHandler err;

    vector<string> writer;
    int line = 0;
    int pc = 0;
    int line_file = 0;
    int aux = 0;
    bool sectionText = false;

    newfile.open(argv[1], ios::in);

    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {
            std::istringstream ss(tp);
            reader.GenerateTokens(tp);
            if (reader.tokens[0] == "" || reader.tokens.size() == 0)
            {
                reader.ClearTokens();
                continue;
            }

            // ----------------------------------------------- primeiros testes

            // Análise da estrutura lexa do sistema
            if (!Validation::CkeckTokens(reader.tokens))
            {
                err.InvalidStruc(line_file);
            }

            // Analise sintática 1
            if ((Validation::CheckDuplicates(reader.tokens)))
            {
                err.DuplicatedRotules(line_file);
            }

            //--------------------------------------------------
            // Validação dos valores na SECTION DATA *******************************
            if (Validation::SectionCheck(reader.tokens) == 1)
            {
                sectionText = false;
                reader.ClearTokens();
                continue;
            }
            if (Validation::SectionCheck(reader.tokens) == 2)
            {
                sectionText = true;
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
                {

                    symbs.CheckTokenCS(reader.tokens);
                    reader.PrintTokens();
                    symbs.RoolBack(writer, reader.tokens[0]);
                    if (Validation::LabelOnly(reader.tokens))
                    {
                        reader.ClearTokens();
                        continue;
                    }
                    reader.RemoveFront(2);
                    symbs.ConstSpaceFunc(reader.tokens, pc);
                }

                writer.push_back(reader.LineWrite(to_string(aux)));
                aux = pc;
                line++;
                // reader.PrintTokens();
            }

            line_file++;

            reader.ClearTokens();
        }

        symbs.AddTextData(pc, writer);
        newfile.close(); //close the file object.
    }
    reader.PrintWriter(writer);
    // symbs.PrintTable();
    return 0;
}
