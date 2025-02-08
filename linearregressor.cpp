#include <iostream>
#include <string>
#include <random>
#include <Eigen/Dense>
#include <sstream>
#include <fstream>

void fisher_yates_shuffle(Eigen::MatrixXd &);
void readCSV(std::string &, std::vector <std::vector <double>> &);
void linear_regression(Eigen::MatrixXd &);
void zscore_standardise(Eigen::MatrixXd &, Eigen::MatrixXd &);
void get_attributes(Eigen::MatrixXd &, Eigen::MatrixXd &);
void predict(Eigen::MatrixXd &, Eigen::MatrixXd &, Eigen::MatrixXd &);

int main()
{
    std::string filename = "property_prices.csv";
    std::vector<std::vector <double>> data;
    readCSV(filename, data);
    if (data.empty())
    {
        std::cerr << "The data is empty" << std::endl;
    }
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
    linear_regression(data);
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
                throw std::runtime_error("Invalid data in file");
            }
            
        }
        data.push_back(row);
    }
}

void fisher_yates_shuffle(Eigen::MatrixXd &data_matrix)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    int rows = data_matrix.rows();
    for (int i = rows - 1; i >0; --i)
    {
        std::uniform_int_distribution <int> dist(0, i);
        int j = dist(gen);
        std::swap(data_matrix.row(i), data_matrix.row(j));
    }
}

void linear_regression(Eigen::MatrixXd &data_matrix)
{
    fisher_yates_shuffle(data_matrix);
    int rows = data_matrix.rows();
    int cols = data_matrix.cols();
    int train_rows = 0.6*rows;
    Eigen::MatrixXd attributes(2, cols-1);
    get_attributes(data_matrix.block(0, 0, train_rows, cols - 1), attributes);
    zscore_standardise(data_matrix, attributes);
    int test_rows = 0.2*rows;
    int valid_rows = 0.2*rows;
    // Training data
    Eigen::MatrixXd ones_column_train = Eigen::MatrixXd::Ones(train_rows, 1);
    Eigen::MatrixXd input_train_data_matrix(train_rows, cols);
    input_train_data_matrix << ones_column_train, data_matrix.block(0, 0, train_rows, cols - 1);
    Eigen::MatrixXd output_train_data_matrix = data_matrix.block(0, cols - 1, train_rows, 1);
    // Test data
    Eigen::MatrixXd input_test_data_matrix(test_rows, cols);
    Eigen::MatrixXd ones_column_test = Eigen::MatrixXd::Ones(test_rows, 1);
    input_test_data_matrix << ones_column_test, data_matrix.block(train_rows, 0, test_rows, cols - 1);
    Eigen::MatrixXd output_test_data_matrix = data_matrix.block(train_rows, cols - 1, test_rows, 1);
    // Validation data
    Eigen::MatrixXd input_valid_data_matrix(valid_rows, cols);
    Eigen::MatrixXd ones_column_valid = Eigen::MatrixXd::Ones(valid_rows, 1);
    input_valid_data_matrix << ones_column_valid, data_matrix.block(train_rows + test_rows, 0, valid_rows, cols - 1);    
    Eigen::MatrixXd output_valid_data_matrix = data_matrix.block(train_rows + test_rows, cols - 1, valid_rows, 1);
    // Parameters
    Eigen::MatrixXd parameters = (input_train_data_matrix.transpose() * input_train_data_matrix).inverse() 
                                    * input_train_data_matrix.transpose() * output_train_data_matrix;

    std::cout << "Parameters (\theta) are: " << parameters << std::endl;
    predict(parameters, input_test_data_matrix, output_test_data_matrix);
}

void get_attributes(Eigen::MatrixXd &data_matrix, Eigen::MatrixXd &attributes)
{
    Eigen::MatrixXd col_mean = data_matrix.colwise().mean();
    Eigen::MatrixXd variance = ((data_matrix.rowwise() - col_mean.transpose()).array().square().colwise().sum()) / (data_matrix.rows() - 1);
    Eigen::MatrixXd sd = variance.array().sqrt();
    attributes.row(0) = col_mean.transpose();
    attributes.row(1) = sd.transpose();
}

void zscore_standardise(Eigen::MatrixXd &data_matrix, Eigen::MatrixXd &attributes)
{
    data_matrix = (data_matrix.rowwise() - attributes.row(0).transpose()).array().rowwise() / attributes.row(1).transpose().array();
}
void predict(Eigen::MatrixXd &parameters, Eigen::MatrixXd &input_data_matrix, Eigen::MatrixXd &output_data_matrix)
{
    Eigen::MatrixXd prediction = input_data_matrix*parameters;
    double lmserror = std::sqrt(((prediction - output_data_matrix).array().square().sum())/prediction.rows());
    std::cout << "The predictions are " << prediction << std::endl;
    std::cout << "The root mean squared error is " << lmserror << std::endl;
}