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
#include "modules\memhendler.h"
using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> files;
    Chunks chunks;
    HeaderCheck header;
    MemHandler mem;
    int chunkIndice;
    for (int i = 0; i < argc; i++)
    {
        if (chunks.CheckObjectFile(argv[i]))
        {
            mem.AlocateMem(argv[i]);
            continue;
        }
        if (Validation::CheckNumber(argv[i]))
        {
            chunkIndice = i;
            break;
        }
    }

    chunks.ReadArgs(argv, chunkIndice);
    //chunks.PrintChunks();
    //mem.PrintMemory();

    if (!mem.VerifySizes(chunks))
    {
        return 0;
    }

    mem.PrintUsedChunks(chunks);

    mem.WriteFile(chunks);

    return 0;
}
