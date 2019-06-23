#include <iostream>
#include "wav.hpp"
#include <algorithm>
using namespace std;
bool wav::readFromFile(const char* nameOfFile)
{
    FILE * input = fopen(nameOfFile, "rb");
    if(input == NULL)
        return false;
    if(fread(&header, sizeof(WAVHEADER), 1, input) != 1)
    {
        cout << "Cannot read header" << endl;
        return false;
    }
    while(header.subchunk2Id[0] != 'd' && header.subchunk2Id[1] != 'a' && header.subchunk2Id[2] != 't' && header.subchunk2Id[3] != 'a')
    {
        fseek(input, header.subchunk2Size, SEEK_CUR);
        fread(header.subchunk2Id, sizeof(char), 4, input);
        fread(&(header.subchunk2Size), sizeof(unsigned int), 1, input);
    }
    short tmp;
    for(int i = 0; i < header.subchunk2Size; i += 16)
    {  
        fread(&tmp, sizeof(short), 1, input);
        //cout << tmp << endl;
        data.push_back(tmp);        
    }
    fclose(input);
    return true;
 }
 void wav::printHeader()
 {
     cout << "header.chunkId - " << header.chunkId[0] << header.chunkId[1] << header.chunkId[2] << header.chunkId[3] << endl;
     cout << "header.chunkSize - " << header.chunkSize << endl;
     cout << "header.format - " << header.format[0] << header.format[1] << header.format[2] << header.format[3] << endl;
     cout << "header.subchunk1Id - " << header.subchunk1Id[0] << header.subchunk1Id[1] << header.subchunk1Id[2] << header.subchunk1Id[3] << endl;
     cout << "header.subchunk1Size - " << header.subchunk1Size << endl;
     cout << "header.audioFormat - " << header.audioFormat << endl;
     cout << "header.numChannels - " << header.numChannels << endl;
     cout << "header.sampleRate - " << header.sampleRate << endl;
     cout << "header.byteRate - " << header.byteRate << endl;
     cout << "header.blockAlign - " << header.blockAlign << endl;
     cout << "header.bitsPerSample - " << header.bitsPerSample << endl;
     cout << "header.subchunk2Id - " << header.subchunk2Id[0] << header.subchunk2Id[1] << header.subchunk2Id[2] << header.subchunk2Id[3] << endl;
     cout << "header.subchunk2Size - " << header.subchunk2Size << endl;
     cout << endl;
}
bool wav::writeRawData(const char* nameOfFile)const
{
    FILE * output = fopen(nameOfFile, "w");
    if(output == NULL)
    {
        cout << "Cannot open file to write" << endl;
        return false;
    }
    for(int i = 0; i < min((int)data.size(), 1000); i++)
    {
        fprintf(output, "%d %d \n", i, data[i]);
    }
    fclose(output);
    return true;
}
bool wav::writeInFile(const char* nameOfFile)const
{
    FILE * output = fopen(nameOfFile, "wb");
    if(output == NULL)
    {
        cout << "Cannot open file to write" << endl;
        return false;
    }
    fwrite(&header, sizeof(WAVHEADER), 1, output);
    for(int i = 0 ; i < data.size(); i++)
    {
        cout << data[i] << endl;
        fwrite(&(data[i]), sizeof(short), 1, output);
    }
    fclose(output);
    return true;
}
void wav::genStdMathFunction(int samples)
{
    header.chunkId[0] = 'R'; header.chunkId[1] = 'I'; header.chunkId[2] = 'F'; header.chunkId[3] = 'F';
    header.chunkSize = samples*2 + 36;
    header.format[0] = 'W'; header.format[1] = 'A'; header.format[2] = 'V'; header.format[3] = 'E';
    header.subchunk1Id[0] = 'f'; header.subchunk1Id[1] = 'm', header.subchunk1Id[2] = 't'; header.subchunk1Id[3] = 32;
    header.subchunk1Size = 16;
    header.audioFormat = 1;
    header.numChannels = 1;
    header.sampleRate = 44100;
    header.byteRate = 88200;
    header.blockAlign = 2;
    header.bitsPerSample = 16;
    header.subchunk2Id[0] = 'd'; header.subchunk2Id[1] = 'a'; header.subchunk2Id[2] = 't'; header.subchunk2Id[3] = 'a';
    header.subchunk2Size = samples*2;
    data.clear();
    for(int i = 0; i < samples; i++)
    {
        data.push_back(60000*function(((double)(i))/44100.));
    }
}
void wav::changeData()
{
    for(int i = 0; i < data.size(); i++)
        data[i] = 60000*function(((double)i)/44100.);
}
double function(double t)
{
    return sin(10000*t);
}