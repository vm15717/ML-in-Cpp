#include <iostream>
#include <string>
#include "Matrix.hpp"

void readCSV(std::string &);

int main()
{
    std::string filename = "lc.csv";
    std::vector <double> params;
}

void parameter_find(std::vector <std::vector <double>> &data)
{
    if (data.empty())
    {
        throw std::invalid_argument("The data is empty!");
    }
    int n = data.size();
    for (int i = 0; i < n; i++)
    {
        
    }
}