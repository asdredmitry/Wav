#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    unsigned char * data = new unsigned char[100];
    fill(data, data + 100, 2);
    int * tmp = (int *)(data + 4);
    cout << *tmp << endl;
}