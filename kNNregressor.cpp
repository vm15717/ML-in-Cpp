#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <cmath>
#include <algorithm>
#include <exception>

void readCSV(std::string &, std::vector <std::vector <double>> &);
void zscore_standardise(std::vector <std::vector <double>> &, std::vector <std::vector <double>> &);
void get_attributes(std::vector <std::vector <double>> &, std::vector <std::vector <double>> &);
void predict_output(std::vector <std::vector <double>> &, std::vector <std::vector <double>> &, int);
double avg_nearest_neighbours(std::vector <double> &, std::vector <std::vector <double>> &, int );

int main()
{
    std::string filename;
    std::vector <std::vector <double>> training_data;
    readCSV(filename, training_data);
    int k = 3;
    std::vector <std::vector <double>> test_data;
    readCSV(filename, test_data);
    predict_output(training_data, test_data, k);
    return 0;
}

void readCSV(std::string &filename, std::vector <std::vector <double>> &data)
{
    std::ifstream file(filename);
    std::string line;
    if (!file.is_open())
    {
        std::cerr << "Cannot open the file!" << filename << std::endl;
        return;
    }
    while(std::getline(file, line))
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

void get_attributes(std::vector <std::vector <double>> &data, std::vector <std::vector <double>> &attributes)
{
    int rows = data.size();
    int cols = data[0].size();
    std::vector <double> avg(cols, 0);
    std::vector <double> avg_squared(cols, 0);
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = 0; j < data[i].size() - 1; j++)
        {
            avg[j] = data[i][j] + avg[j]; 
            avg_squared[j] = (data[i][j]*data[i][j]) + avg_squared[j];
        }
    }
    for (int k = 0; k < cols - 1; k++)
    {
        avg[k] /= rows;
        avg_squared[k] = std::sqrt(avg_squared[k]/(rows-1) - avg[k]*avg[k]);
    }
    attributes.push_back(avg);
    attributes.push_back(avg_squared);
}
void zscore_standardise(std::vector <std::vector <double>> &data, std::vector <std::vector <double>> &attributes)
{
    int rows = data.size();
    int cols = data[0].size();
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols - 1; j++)
        {
            if (attributes[1][j] != 0){
                data[i][j] = (data[i][j] - attributes[0][j])/(attributes[1][j]);
            }
            else
            {
                data[i][j] = 0;
            }
        }   
    } 
}

void predict_output(std::vector <std::vector <double>> &training_data, std::vector <std::vector <double>> &test_data, int k)
{
    std::vector <std::vector <double>> attributes;
    if (training_data.empty() || test_data.empty())
    {
        throw std::invalid_argument("The training and/or the test dataset are empty");
    }
    get_attributes(training_data, attributes);
    zscore_standardise(training_data, attributes);
    zscore_standardise(test_data, attributes);
    std::vector <double> predicted_values;
    for (int i  = 0; i < test_data.size(); i++)
    {
         double predicted_value = avg_nearest_neighbours(test_data[i], training_data, k);
         predicted_values.push_back(predicted_value);
    }
}

double avg_nearest_neighbours(std::vector <double> &data_point, std::vector <std::vector <double>> &training_data, int k)
{
    std::vector <std::pair <int, double>> distance_map;
    int rows = training_data.size();
    int cols = training_data[0].size();
    for (int i = 0; i < rows; i++)
    {
        double distance = 0;
        for (int j = 0; j < cols - 1; j++)
        {
            distance += (data_point[j] - training_data[i][j])*(data_point[j] - training_data[i][j]);
        }
        distance_map.emplace_back(i, distance);
    }
    std::partial_sort(distance_map.begin(), distance_map.begin() + k , distance_map.end(), [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        return a.second < b.second;
    });
    double predicted_value = 0;
    if (k > rows)
    {
        k = rows;
    }
    for (int m = 0; m < k; m++)
    {
        predicted_value = predicted_value + training_data[distance_map[m].first][cols] / k;
    }
    return predicted_value;
}
