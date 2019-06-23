#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include "wav.hpp"
using namespace std;
int main()
{
    wav w1;
    w1.genStdMathFunction(100000);
    w1.printHeader();
    w1.writeInFile("mathFUnc.wav");
    wav w2;
    w2.readFromFile("sine.wav");
    w2.printHeader();
    return 0;
}