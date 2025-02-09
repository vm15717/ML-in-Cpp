#include <iostream>
#include <exception>
template <typename T>

class Matrix
{
    private:
    int rows;
    int cols;
    T *data;
    public:
    Matrix(const int r, const int c, const T t) :rows(r), cols(c), data(nullptr)
    {
        if (rows * cols <= 0)
        {
            throw std::invalid_argument("The matrix cannot be empty");
        }
        else
        {
            data = new T[rows * cols];
            for (int i = 0; i < rows *cols; i++)
            {
                data[i] = t;
            }   
        }
    }
    Matrix (const std::vector <std::vector <T>> &data_matrix)
    {
        if (data_matrix.empty())
        {
            throw std::invalid_argument("The data_matrix is empty");
        }
        this->rows = data_matrix.size();
        this->cols = data_matrix[0].size();
        data = new T[rows * cols];
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                data[i*cols+j] = data_matrix[i][j];
            }
        }
    }
    ~Matrix()
    {
        delete[] data;
    }
    T at(const int i, const int j) const
    {
        if (i < 0 || i >= rows || j < 0 || j >= cols)
        {
            throw std::out_of_range("The row and column positions are out of bounds!");
        }
        else
        {
            return data[i*cols + j];
        }
    }
    int getrows() const
    {
        return rows;
    }
    int getcols() const
    {
        return cols;
    }
    Matrix operator+(const Matrix &other) const 
    {
        if (other.rows != rows || other.cols != cols)
        {
            throw std::invalid_argument("The numbers of rows and/or columns do not match to perform addition");
        }
        Matrix result(other.rows, other.cols, 0);
        for (int i = 0; i < rows*cols; i++)
        {
            result[i] = data[i] + other.data[i];
        }
        return result;
    }
    Matrix operator-(const Matrix &other)
    {
        if (other.rows != rows || other.cols != cols)
        {
            throw std::invalid_argument("The numbers of rows and/or columns do not match to perform addition");
        }
        else
        {
            Matrix result(other.rows, other.cols, 0);
            for (int i = 0; i < rows*cols; i++)
            {
                result[i] = data[i] - other.data[i];
            }
            return result;
        }
    }
    Matrix operator*(const Matrix &other)
    {
        if (cols != other.rows)
        {
            throw std::invalid_argument("Cannot multiply the matrices, the dimensions do not match");
        }
        Matrix result(rows, other.cols, 0);
        for (int i = 0; i < rows; i++)
            { 
                for (int j = 0; j < other.cols; j++)
                {
                    for (int k = 0; k < cols; k++)
                    {
                        result.data[i*other.cols+j] += data[i*cols+k]*other.data[k*other.cols+j];
                    }
                }
            }
        return result;
    }
    friend std::ostream &operator <<(std::ostream &out, const Matrix &matrix)
    {
        if (matrix.rows <= 0 || matrix.cols <=0)
        {
            throw std::invalid_argument("This matrix is invalid, cannot be printed!");
        }
        for (int i = 0; i < matrix.rows; i++)
        {
            for (int j = 0; j < matrix.cols; j++)
            {
                out << matrix.data[i * matrix.cols + j] << "\t";
            }
            out << std::endl;
        }
        return out;
    }
};