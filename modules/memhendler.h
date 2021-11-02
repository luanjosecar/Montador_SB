
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <regex>
#include "tokenreader.h"
#include "memory.h"
#include "chunkscheck.h"

using namespace std;

class MemHandler
{
public:
    vector<Memory> mem_vec;
    //vector<int> usedchunks;

    void AlocateMem(string arg)
    {
        Memory mem_aux;
        mem_aux.DefineVariables(arg);
        mem_vec.push_back(mem_aux);
    }

    void PrintMemory()
    {
        for (int i = 0; i < (signed)mem_vec.size(); i++)
        {
            mem_vec[i].PrintMemory();
            cout << endl;
        }
    }

    bool VerifySizes(Chunks space)
    {
        int total = 0;
        int aux = 0;
        for (int i = 0; i < (signed)mem_vec.size(); i++)
        {
            aux = space.NeededSpace(mem_vec[i].space, total);
            if (aux < 0)
            {
                cout << mem_vec[i].codename << " NAO FOI POSSIVEL ALOCAR" << endl;
                return false;
            }

            total += aux;

            //cout << "Total : " << total << " aux : " << aux << endl;
            mem_vec[i].chunksused = aux;
            //usedchunks.push_back(aux);
        }
        return true;
    }

    void PrintUsedChunks(Chunks space)
    {
        int used = 0;
        for (int i = 0; i < (signed)mem_vec.size(); i++)
        {
            cout << mem_vec[i].codename << " utilizando " << mem_vec[i].chunksused - used << " CHUNKS. Enderecos iniciais em : ";
            space.PrintChunckPlaces(mem_vec[i].chunksused, used);
            cout << endl;
            used = mem_vec[i].chunksused;
        }
    }

    void WriteFile(Chunks space)
    {
        int used = 0;
        for (int i = 0; i < (signed)mem_vec.size(); i++)
        {
            mem_vec[i].WriteFile(space, used);
            used = mem_vec[i].chunksused;
        }
    }
};