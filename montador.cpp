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

bool PRINTER = true;

int main(int argc, char const *argv[])
{

    fstream newfile;

    TokenReader reader;
    TS symbs;
    FunctionCheck funcs;
    ErrHandler err;
    HeaderCheck header;

    vector<string>
        writer;
    int line = 0;
    int pc = 0;
    int line_file = 0;
    int aux = 0;
    bool sectionText = false;
    string labelaux = "";

    if (!header.ValidateArgs(argc, argv))
    {
        cout << "Argumentos de entrada invalidos " << endl;
        return 0;
    }

    //header.ValidateArgs(argc, argv);

    newfile.open(header.filename, ios::in);

    if (newfile.is_open())
    {
        string tp;
        while (getline(newfile, tp))
        {
            line_file++;
            std::istringstream ss(tp);
            reader.GenerateTokens(tp);
            if (reader.tokens[0] == "" || reader.tokens.size() == 0)
            {
                reader.ClearTokens();
                continue;
            }

            // ----------------------------------------------- primeiros testes

            // Verifica Tokens Invalidos
            if (!Validation::CkeckTokens(reader.tokens))
            {
                err.InvalidToken(line_file);
                reader.ClearTokens();
                continue;
            }

            // Verifica se há rótulos declarados na mesma instância
            if ((Validation::CheckDuplicates(reader.tokens)))
            {
                err.RepetitiveRotules(line_file);
                reader.ClearTokens();
                continue;
            }

            // Verifica se há declaração repetida de rótulos
            if (Validation::LabelFunction(reader.tokens) && symbs.CheckToken(reader.tokens[0]))
                if (symbs.symbs[symbs.CheckTokenValue(reader.tokens[0])].status || symbs.symbs[symbs.CheckTokenValue(reader.tokens[0])].secData)
                {
                    err.DuplicatedRotules(line_file);

                    reader.ClearTokens();
                    continue;
                }

            if (Validation::LabelFunction(reader.tokens) && labelaux != "")
            {
                err.DuplicatedRotules(line_file);

                reader.ClearTokens();
                continue;
            }

            if (Validation::SectionCheck(reader.tokens) == -1)
            {
                err.InvalidDirective(line_file);
                reader.ClearTokens();
                continue;
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
                if (Validation::LabelOnly(reader.tokens))
                {
                    labelaux = reader.tokens[0];
                    reader.ClearTokens();
                    continue;
                }
                if (labelaux != "")
                {
                    reader.tokens.insert(reader.tokens.begin(), ":");
                    reader.tokens.insert(reader.tokens.begin(), labelaux);
                    labelaux = "";
                }
                symbs.SectionValues(reader.tokens);
            }
            //***********************************************************************
            else
            {

                // Caso para o Label Tenha sido declara na função anterior
                if (labelaux != "" && (reader.tokens[0] == "CONST" || Validation::CheckLastString(reader.tokens[0]) || reader.tokens[0] == "SPACE"))
                {
                    if (!Validation::LabelConstSpaceSize(reader.tokens))
                    {
                        err.InvalidStruc(line_file);

                        reader.ClearTokens();
                        continue;
                    }
                    symbs.RoolLabel(reader.tokens, labelaux, pc, writer);
                    labelaux = "";
                    reader.ClearTokens();
                    continue;
                }
                // Roda a analise de funções
                if (!funcs.Function(reader.tokens, pc))
                {
                    if (funcs.base == -2) // Função não existe
                        err.InvalidFunc(line_file);
                    if (funcs.base == -1) // Função Existe porem tem um erro na estrutura
                        err.InvalidStruc(line_file);
                    if (funcs.base == 0) // Diretiva Invalida
                        err.InvalidDirective(line_file);

                    reader.ClearTokens();
                    continue;
                }
                // Verifica se o item em análise é uma Label
                for (int i = 0; i < (signed)reader.tokens.size(); i++)
                {
                    if (Validation::CheckLastString(reader.tokens[i])) // Verifica se a Estrutura da Label tem um +
                    {
                        symbs.TokenAdder(Validation::CheckPlusLabelToken(reader.tokens[i]), i, line, aux, (Validation::LabelFunction(reader.tokens) && i == 0));
                        symbs.LabelSimpleSearch(reader.tokens, Validation::CheckPlusLabelToken(reader.tokens[i]), i);
                    }
                    else
                    {
                        symbs.TokenAdder(reader.tokens[i], i, line, aux, (Validation::LabelFunction(reader.tokens) && i == 0));
                        symbs.LabelSimpleSearch(reader.tokens, reader.tokens[i], i);
                    }
                }
                // Caso de analise para a Label definida
                if (Validation::LabelFunction(reader.tokens))
                {

                    symbs.CheckTokenCS(reader.tokens);
                    symbs.RoolBack(writer, reader.tokens[0]);

                    // Label sendo a unica função
                    if (Validation::LabelOnly(reader.tokens))
                    {

                        labelaux = reader.tokens[0];
                        reader.ClearTokens();
                        continue;
                    }

                    reader.RemoveFront(2);
                    symbs.ConstSpaceFunc(reader.tokens, pc, writer, aux);
                }

                writer.push_back(reader.LineWrite(to_string(aux)));
                aux = pc;
                line++;
            }

            // Verificação do novo modelo do montador
            if (header.execution == 2)
                header.Bitmap(reader.tokens);
            if (header.execution == 3)
                header.Realocacao(reader.tokens);

            reader.ClearTokens();
        }

        symbs.AddTextData(pc, writer);
        newfile.close(); //close the file object.
    }

    // reader.PrintWriter(writer);
    // symbs.PrintTable();
    header.filesize = symbs.ProgramSize();
    header.code = writer;
    symbs.NonDef(err.message);

    switch (header.execution)
    {
    case 1:
        // Modelo de impressão anterior --------------------------------------------------
        if (err.message.size() > 0)
            err.PrintErros();
        else
        {
            if (PRINTER)
                reader.WriteFile(writer, argv[1]);
            else
                reader.Writer(writer, argv[1]);
        }
        //------------------------------------------------------------------------------

        break;
    case 2:
    case 3:
        if (strcmp(argv[1], "-e") && err.message.size() > 0)
            err.PrintErros();
        else
            header.WriteFile();
        break;
    default:
        break;
    }

    // symbs.PrintTable();
    return 0;
}
