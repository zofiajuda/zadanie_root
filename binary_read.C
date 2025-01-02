#include <fstream>
void binary_read(float *dane, string name = "Cs137.bin")
{
    // float dane[10000];
    fstream myfile;
    myfile.open(name, ios::binary | ios::in);
    int k = 0;
    while (!myfile.eof())
    {
        float x;
        myfile.read((char *)&x, sizeof(float));
        dane[k] = x;
        k++;
    }
}