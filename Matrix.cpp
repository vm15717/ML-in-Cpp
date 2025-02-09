#include <iostream>

template <typename T>

class Matrix
{
    private:
    int rows;
    int cols;
    T *data;
    public:
    Matrix(int r, int c, T t) :rows(r), cols(c)
    {
        if (rows * cols <= 0)
        {
            std::cerr << "The matrix cannot be empty" << std::endl;
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
    ~Matrix()
    {
        delete []data;
    }

    T at(const int i, const int j) const
    {
        if (i < 0 || i > rows || j < 0 || j > cols)
        {
            std::cerr << "The row and column positions are out of bounds!" << std::endl;
        }
        else
        {
            return data[i*cols + j];
        }
    }
    Matrix operator+(const Matrix &other) const 
    {
        if (other.rows != rows || other.cols != cols)
        {
            std::cerr << "The numbers of rows and/or columns do not match to perform addition";
            return;
        }
        else
        {
            Matrix result(other.rows, other.cols, 0);
            for (int i = 0; i < rows*cols; i++)
            {
                result[i] = data[i] + other.data[i];
            }
            return result;
        }
    }
    Matrix operator-(const Matrix &other)
    {
        for (int i = 0; i < other.rows * other.cols; i++)
        {
            other.data[i] = -1*other.data[i];
        }
        return other;
    }
    Matrix operator-(const Matrix &other)
    {
        if (other.rows != rows || other.cols != cols)
        {
            std::cerr << "The numbers of rows and/or columns do not match to perform addition";
            return;
        }
        else
        {
            Matrix result(other.rows, other.cols, 0);
            result = this + (-other);
            return result;
        }
    }
};