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
    if(!checkHeader())
        return false;
    if(data != NULL)
        delete[] data;
    data = new unsigned char[header.subchunk2Size];
    if(fread(data, sizeof(unsigned char), header.subchunk2Size, input) != header.subchunk2Size)
    {
        cout << "Cannot read samples " << endl;
        return false;
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
bool wav::checkHeader()
{
    if(header.bitsPerSample != 8 && header.bitsPerSample != 16)
    {
        cout << endl;
        cout << "Unexpected bitsPerSample " << header.bitsPerSample << endl; 
        cout << endl;
        return false;
    }
    else if(header.numChannels != 1 && header.numChannels != 2)
    {
        cout << endl;
        cout << "Unexpected numChannels " << header.numChannels << endl;
        cout << endl;
        return false;
    }
    else if(header.audioFormat != 1)
    {
        cout << endl;
        cout << "Unexpected format " << header.audioFormat << endl;
        cout << endl;
        return false;
    }
    return true;
}
bool wav::writeRawData(const char* nameOfFile, int maxSamples)const
{
    FILE * output = fopen(nameOfFile, "w");
    if(output == NULL)
    {
        cout << "Cannot open file to write" << endl;
        return false;
    }
    if(header.bitsPerSample == 8)
    {
        for(int i = 0; i < header.subchunk2Size; i++)
        {
            if(i % header.numChannels == 0)
                fprintf(output, "%d %d ", i, data[i]);
            else if(i % header.numChannels == 1)
                fprintf(output, "%d %d \n", i, data[i]);
            if(header.numChannels == 1)
                fprintf(output, "\n");
        }
    }
    else if(header.bitsPerSample == 16)
    {
        short * data16 = (short *)data;
        for(int i = 0; i < header.subchunk2Size/2; i++)
        {
            if(i % header.numChannels == 0)
                fprintf(output, "%d %d ", i, data16[i]);
            else if(i % header.numChannels == 1)
                fprintf(output, "%d %d \n", i, data16[i]);
            if(header.numChannels == 1)
                fprintf(output, "\n");
        }
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
    if(fwrite(&header, sizeof(WAVHEADER), 1, output) != 1)
        cout << "Cannot write header " << endl;
    if(fwrite(data, sizeof(unsigned char), header.subchunk2Size, output) != header.subchunk2Size)
        cout << "Cannot write data" << endl;    
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
    if(data != NULL)
        delete [] data;
    data = new unsigned char[samples*2];
    short * data16 = (short*)data;
    for(int i = 0; i < samples; i++)
    {
        data16[i] = 60000*function(((double)(i))/44100.);
    }
}
void wav::changeData()
{
    if(header.bitsPerSample == 8)
    {
        for(int i = 0; i < header.subchunk2Size; i++)
        {
            if(i%header.numChannels == 0)
            {
                data[i] = 0;
            }
            else if(i%header.numChannels == 1) 
            {
                data[i] += 1;
            }
        }
    }
    else if(header.bitsPerSample == 16)
    {
        short * data16 = (short *)data;
        for(int i = 0; i < header.subchunk2Size/2; i++)
        {
            if(i%header.numChannels == 0)
            {
                data16[i] = 0;
            } 
            else 
            {
                data16[i] += 1;
            }
        }
    }
}
double function(double t)
{ 

    return sin(100*t*((int)(t*10) + 1));
}