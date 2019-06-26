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
        unsigned char * data;
    public:
        wav()
        {
            data = NULL;
        }
        wav(const char* nameOfFile)
        {
            readFromFile(nameOfFile);
        }
        ~wav()
        {
            if(data != NULL)
                delete[] data;
        }
        bool readFromFile(const char* nameOfFile);
        bool writeInFile(const char* nameOfFile) const;
        bool writeRawData(const char* nameOfFile, int maxSamples)const;
        void genStdMathFunction(int samples);
        void printHeader();
        void changeData();
        bool checkHeader();
};
double function(double t);
#endif