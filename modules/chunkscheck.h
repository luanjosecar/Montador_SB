
#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <regex>
#include "tokenvalidator.h"
using namespace std;

class Chunks
{
public:
    int chuncksNumber;
    vector<int> chunckSpace;
    vector<int> chunckPlace;
    vector<int> usedChunks;

    void ReadArgs(char const *arg[], int index)
    {
        chuncksNumber = stoi(arg[index]);
        for (int i = 1; i <= chuncksNumber; i++)
        {
            chunckSpace.push_back(stoi(arg[index + i]));
            chunckPlace.push_back(stoi(arg[index + i + chuncksNumber]));
        }
    }

    void PrintChunks()
    {
        for (int i = 0; i < (signed)chunckPlace.size(); i++)
        {
            cout << " CHUNK " << i << "--------------" << endl
                 << "SPACE : " << chunckSpace[i] << endl
                 << "PLACE : " << chunckPlace[i] << endl;
        }
    }

    bool CheckObjectFile(string s)
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
        if (!temp.empty() && aux1 == "obj")
        {
            return true;
        }
        return false;
    }

    int NeededSpace(int mem_size, int chunck_use = 0)
    {
        int totalSpace = 0;
        for (int i = chunck_use; i < (signed)chunckSpace.size(); i++)
        {
            totalSpace += chunckSpace[i];

            if (mem_size <= totalSpace)
            {
                //cout << "MM : " << mem_size << " Space : " << totalSpace << " i : " << i << endl;
                return i + 1;
            }
        }
        return -1;
    }

    void PrintChunckPlaces(int number, int begin)
    {
        for (int i = begin; i < number; i++)
            cout << chunckPlace[i] << " ";
    }

    void CheckTotalSize()
    {
        int total_space = 0;
        for (int i = 0; i < (signed)chunckSpace.size(); i++)
            total_space += chunckSpace[i];
        cout << "Total Chuncks space " << total_space << endl;
    }

    bool MemOverflow()
    {
        for (int i = 0; i < (signed)chunckPlace.size(); i++)
        {
            for (int j = 0; j < (signed)chunckPlace.size(); j++)
            {
                if (j == i)
                    continue;
                if (chunckPlace[i] < chunckPlace[j] && (chunckPlace[i] + chunckSpace[i]) < (chunckPlace[j] + chunckSpace[j]) && (chunckPlace[i] + chunckSpace[i]) > chunckPlace[j])
                {
                    cout << "CHUNK " << i << " PODERA SOBRESCREVER CHUNK " << j << endl;
                    return false;
                }
                if (chunckPlace[i] > chunckPlace[j] && (chunckPlace[i] + chunckSpace[i]) > (chunckPlace[j] + chunckSpace[j]) && chunckPlace[i] < (chunckPlace[j] + chunckSpace[j]))
                {
                    cout << "CHUNK " << i << " PODERA SOBRESCREVER CHUNK " << j << endl;
                    return false;
                }

                if (chunckPlace[i] < chunckPlace[j] && (chunckPlace[i] + chunckSpace[i]) > (chunckPlace[j] + chunckSpace[j]))
                {
                    cout << "CHUNK " << i << " PODERA SOBRESCREVER CHUNK " << j << endl;
                    return false;
                }
            }
        }
        return true;
    }
};