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
#include "modules\chunkscheck.h"
#include "modules\memory.h"
using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> files;
    Chunks chunks;
    HeaderCheck header;
    Memory aux_mem;
    vector<Memory> mem;
    int chunkIndice;
    for (int i = 0; i < argc; i++)
    {
        if (chunks.CheckObjectFile(argv[i]))
        {
            aux_mem.DefineVariables(argv[i]);
            mem.push_back(aux_mem);
            continue;
        }
        if (Validation::CheckNumber(argv[i]))
        {
            chunkIndice = i;
            break;
        }
    }

    chunks.ReadArgs(argv, chunkIndice);
    chunks.PrintChunks();

    for (int i = 0; i < (signed)mem.size(); i++)
    {
        mem[i].PrintMemory();
    }
    return 0;
}
