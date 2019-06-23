#ifndef WAV_HPP
#define WAV_HPP
#include "wav_header.hpp"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
using namespace std;
class wav
{
    private:
        WAVHEADER header;
        vector<short> data;
    public:
        wav()
        {}
        wav(const char* nameOfFile)
        {
            readFromFile(nameOfFile);
        }
        ~wav()
        {}
        bool readFromFile(const char* nameOfFile);
        bool writeInFile(const char* nameOfFile) const;
        bool writeRawData(const char* nameOfFile)const;
        void genStdMathFunction(int samples);
        void printHeader();
        void changeData();
};
double function(double t);
#endif