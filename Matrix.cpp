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
    T at(int i, int j)
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
};