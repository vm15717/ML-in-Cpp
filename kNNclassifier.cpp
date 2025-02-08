#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <cmath>
#include <random>
#include <algorithm>
#include <map>

void readCSV(std::string &, std::vector <std::vector <double>> &);
void fisher_yates_shuffle(std::vector <std::vector <double>> &);
void predict_output(std::vector <std::vector <double>> &, int);
void get_attributes(std::vector <std::vector <double>> &, std::vector <std::vector <double>> &);
void zscore_standardise(std::vector <std::vector <double>> &, std::vector <std::vector <double>> &);
int nearest_neighbours(std::vector <double> &, std::vector <std::vector <double>> &, int);

int main()
{
    std::string filename;
    std::vector <std::vector <double>> data;
    readCSV(filename, data);
    predict_output(data, 3);
    return 0;
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
            try {
                row.push_back(std::stod(cell));
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: Invalid data in file!" << std::endl;
                return;
            }
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
        std::uniform_int_distribution<int> dist(0, i-1);
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
    zscore_standardise(validation_data, attributes);
    std::vector <int> predicted_classes;
    for (int i = 0; i < test_rows; i++)
    {
        int predicted_class = nearest_neighbours(test_data[i], training_data, k);
        predicted_classes.push_back(predicted_class);
        std::cout << "The predicted class is " << predicted_class << std::endl;
    }
}

void get_attributes(std::vector <std::vector <double>> &data, std::vector <std::vector <double>> &attributes)
{
    int rows = data.size();
    int cols = data[0].size();
    std::vector <double> avg(cols, 0);
    std::vector <double> avg_squared(cols, 0);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols-1; j++)
        {
            avg[j] += data[i][j];
            avg_squared[j] += data[i][j]*data[i][j];
        }
    }
    for (int k = 0; k < cols-1; k++)
    {
        avg[k] /= rows;
        avg_squared[k] = std::sqrt(avg_squared[k]/rows - avg[k]*avg[k]);
    }
    attributes.push_back(avg);
    attributes.push_back(avg_squared);
}

void zscore_standardise(std::vector <std::vector <double>> &data, 
    std::vector <std::vector <double>> &attributes)
{
    int rows = data.size();
    int cols = data[0].size();
    for(int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols - 1; j++)
        {
            if (std::fabs(attributes[1][j]) > 1e-9)
            {
                data[i][j] = (data[i][j] - attributes[0][j])/attributes[1][j];
            }
            else
            {
                data[i][j] = 0;
            }
        }
    }
}

int nearest_neighbours(std::vector <double> &data_point, std::vector <std::vector <double>> &data, int k)
{
    int rows = data.size();
    int cols = data[0].size();
    if (k > rows)
    {
        k = rows;
    }
    std::vector<std::pair <int, double>> distance_map;
    for (int i = 0; i < rows; i++)
    {
        double distance = 0;
        for (int j = 0; j < cols - 1; j++)
        {
            distance = std::hypot(distance, data_point[j] - data[i][j]);
        }
        distance_map.push_back({i, distance});
    }
    std::partial_sort(distance_map.begin(), distance_map.begin() + k, distance_map.end(), 
    [](const std::pair <int, double> &a, const std::pair <int, double> &b) 
    {
        return a.second < b.second;
    });
    std::map <int, int> best_class;
    for (int i = 0; i < k; i++)
    {
        best_class[data[distance_map[i].first][cols-1]]++; 
    }
    std::vector<std::pair<int, int>> class_vector(best_class.begin(), best_class.end());
    std::partial_sort(class_vector.begin(), class_vector.begin() + 1, class_vector.end(), 
    [](const std::pair <int, int> &a, const std::pair <int, int> &b) 
    {
        return a.second > b.second;
    });
    return class_vector[0].first;
}