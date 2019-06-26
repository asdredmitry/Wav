#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include "wav.hpp"
using namespace std;
int main()
{
    wav w1;
    w1.genStdMathFunction(1000000);
    w1.writeInFile("CheckStdMathFunction.wav");
    w1.writeRawData("DifferentFreq.dat", 100000);
    return 0;
}