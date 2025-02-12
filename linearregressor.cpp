#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <random>
#include "Matrix.hpp"

void readCSV(const std::string &, std::vector<std::vector<double>> &);
void fisher_yates_shuffle(std::vector <std::vector <double>> &);
void regression(Matrix <double> &);
int main()
{
    std::string filename = "property_prices.csv";
    std::vector<std::vector<double>> data;
    readCSV(filename, data);
    fisher_yates_shuffle(data);
    Matrix<double> data_matrix(data);
    regression(data_matrix);
    std::cout << data_matrix;
    return 0;
}

void readCSV(const std::string &filename, std::vector<std::vector<double>> &data)
{
    std::ifstream file(filename);
    std::string line;
    while(std::getline(file, line))
    {
        std::vector<double> row;
        std::stringstream ss(line);
        std::string token;
        while(std::getline(ss, token, ','))
        {
            try{
                row.push_back(std::stod(token));
            }
            catch(const std::exception &e)
            {
                std::cerr << "Error parsing token: " << token << std::endl;
            }
        }
        data.push_back(row);
    }
}

void fisher_yates_shuffle(std::vector <std::vector <double>> &data)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    int n = data.size();
    for (int i = n - 1;i > 0; --i)
    {
        std::uniform_int_distribution <int> dist(0, i);
        int j = dist(gen);
        std::swap(data[i], data[j]);
    }   
}

void regression(Matrix <double> &data_matrix)
{
    int rows = data_matrix.getrows();
    int cols = data_matrix.getcols();
    Matrix <double> input_data = data_matrix.block(0, 0, rows, cols - 1);
    Matrix <double> output_data = data_matrix.block(0, cols - 1, rows, cols);
    Matrix <double> ones(rows, 1, 1);
    Matrix <double> train_data = input_data.hstack(ones);
    Matrix <double> train_data_tp = train_data.transpose();
    Matrix <double> parameters = (train_data_tp * train_data).inverse() * train_data_tp * output_data;
    std::cout << parameters << std::endl;
}