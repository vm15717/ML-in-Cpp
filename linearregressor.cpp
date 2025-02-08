#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <sstream>
#inlude <fstream>

int main()
{
    std::string filename;
    std::vector<std::vector <double>> data;
    readCSV(filename, data);
    int rows = data.size();
    int cols = data[0].size();
    Eigen::MatrixXd mat(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            mat(i, j) = data[i][j];
        }
    }
    return 0;
}

void readCSV(std::string &filename, std::vector <std::vector <double>> &data)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "The file is corrupt, cannot be opened!" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::vector <double> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ','))
        {
            try
            {
                row.push_back(std::stod(cell));
            }
            catch(const std::invalid_argument&)
            {
                throw std::exception("Invalid data in file") << std::endl;
            }
            
        }
    }
}