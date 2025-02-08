#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <random>

void readCSV(std::string &, std::vector <std::vector <double>> &);


int main()
{
    std::string filename;
    std::vector <std::vector <double>> data;
    readCSV(filename, data);
    predict_output(data, 3);
}

void readCSV(std::string &filename, std::vector <std::vector <double>> &data)
{
    std::string line;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "The file cannot be opened!" << filename << std::endl;
        return; 
    }
    while (std::getline(file, line))
    {
        std::vector <double> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ','))
        {
            row.push_back(std::stod(cell));
        }
        data.push_back(row);
    }
    file.close();
}

void fisher_yates_shuffle(std::vector <std::vector <double>> &data)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    int rows = data.size();
    for (int i = rows-1; i > 0; --i)
    {
        std::uniform_int_distribution dist(0, i);
        int j = dist(gen);
        std::swap(data[j], data[i]);
    }   
}


void predict_output(std::vector <std::vector <double>> &data, int k)
{
    if (data.empty())
    {
        std::cerr << "The data is empty!";
    }
    //shuffle the data
    fisher_yates_shuffle(data);
    std::vector <std::vector <double>> training_data;
    std::vector <std::vector <double>> test_data;
    std::vector <std::vector <double>> validation_data;
    int train_rows = 0.6*data.size();
    int test_rows = 0.2*data.size();
    int valid_rows = 0.2*data.size();
    for (int i = 0; i < train_rows; i++)
    {
        training_data.push_back(data[i]);
    }
    for (int j = train_rows; j < train_rows + test_rows; j++)
    {
        test_data.push_back(data[j]);
    }
    for (int k = train_rows + test_rows; k < train_rows+test_rows+valid_rows; k++)
    {
        validation_data.push_back(data[k]);
    }
    std::vector <std::vector <double>> attributes;
    get_attributes(training_data, attributes);
    zscore_standardise(training_data, attributes);
    zscore_standardise(test_data, attributes);
    zscore_standardise(validation_attributes);
    std::vector <int> predicted_classes;
    for (int i = 0; i < test_rows; i++)
    {
        dou
    }
}