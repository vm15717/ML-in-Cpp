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
    Matrix (int n, std::string &mattype)
    {
        if (n <= 0)
        {
            throw std::invalid_argument("The number of rows or cols have to be > 0");
        }
        rows = n;
        cols = n;
        data = new T[n*n];
        std::fill(data, data+rows*cols, 0);
        if (mattype == "eye")
        {
            for (int i = 0; i < rows; i++)
            {
                data[i*cols+i] = 1;
            }
        }
    }
    ~Matrix()
    {
        delete[] data;
    }
    Matrix (const Matrix &other)
    {
        rows = other.rows;
        cols = other.cols;
        data = new T[rows*cols];
        for (int i = 0; i < rows*cols; i++)
        {
            data[i] =  other.data[i];
        }
    }
    Matrix inverse()
    {
        if (rows != cols)
        {
            throw std::invalid_argument("The matrix is not square!, cannot calculate the inverse.");
        }
        std::string mattype = "eye";
        Matrix <double> identity(rows, mattype);
        Matrix result = *this;
        for (int i = 0; i < rows; i++)
        {
            T factor = result.data[i*cols+i];
            if (factor == 0)
            {
                throw std::invalid_argument("Matrix is singular");
            }
            for (int j = 0; j < cols; j++)
            {
                result.data[i*cols+j] /= factor;
                identity.data[i*cols+j] /= factor;
            }
            std::cout << identity << std::endl;
            for (int k = 0; k < rows; k++)
            {
                if (i != k)
                {   
                    T subval = result.data[k*cols+i]/result.data[i*cols+i];
                    for (int l = 0; l < cols; l++)
                    {
                        result.data[k*cols+l] -= subval*result.data[i*cols+l];
                        identity.data[k*cols+l] -= subval*identity.data[i*cols+l]; 
                    }
                }
            }
        }
        return identity;
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
    Matrix operator-(const Matrix &other) const
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
    Matrix operator*(const Matrix &other) const
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
    void insert(const int row, const int col, T val)
    {
        if (row < 0 || row >= rows || col < 0 || col >= rows)
        {
            throw std::out_of_range("Out of bounds");
        }
        this->data[row*cols+col] = val;
    }
    Matrix transpose() const
    {
        Matrix result(cols, rows, 0);
        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                result.data[i*rows+j] = data[i + j*cols];
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