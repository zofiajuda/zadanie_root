//Zofia Juda 05.11.2025
#include <iostream>

void RewriteFile(string name = "Cs-137.dat", string outputname = "output.bin")
{

    ifstream file;
    file.open(name, ios_base::in);
    fstream outfile;
    outfile.open(outputname, ios::binary | ios::out);
    int j = 0;
    if (file.is_open())
    {
        string line;
        while (!file.eof())
        {
            getline(file, line);
            // cout << line << endl;
            stringstream ss(line);
            float x = 0;
            ss >> x;
            outfile.write((char *)&x, sizeof(float));
            j++;
        }
        file.close();
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
}
