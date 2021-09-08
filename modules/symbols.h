#include <iostream>
#include <vector>
#include <string>
#pragma once
using namespace std;

class Symbols
{
public:
    string name;
    vector<int> lines;
    vector<int> positions;
    vector<int> value;
    string base;
    string constValue;
    bool constFunc;
    bool secData = false;
    bool status = false;

    void UpdateSymbolValue(int line, int pos, int value, bool status)
    {
        this->lines.push_back(line);
        this->positions.push_back(pos);
        this->value.push_back(value);
        this->status = status || (this->status);
        if ((this->status) && this->secData)
        {
            this->base = to_string(value);
        }
    }

    void SetValues(string name, int line, int pos, int value, bool status)
    {
        this->name = name;
        this->value.push_back(value);
        this->lines.push_back(line);
        this->positions.push_back(pos);
        this->status = status;
        if (status)
        {
            this->base = to_string(value);
        }
    }

    void SetSection(string consValue, bool constState)
    {
        this->constFunc = constState;
        if (constState)
        {
            this->constValue = consValue;
        }
        this->secData = true;
    }
};
