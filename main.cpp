#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include "wav.hpp"
using namespace std;
int main()
{
    wav w1;
    //w1.genStdMathFunction(100000);
    //w1.printHeader();
    //w1.writeInFile("funk1000.wav");
    w1.readFromFile("pcm1616k.wav"); 
    w1.printHeader();
    //w1.changeData();
    w1.writeRawData("sineRaw.dat", 120000);
    w1.writeInFile("test.wav");
    return 0;
}