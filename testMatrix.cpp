#include "Matrix.cpp"

int main()
{
    Matrix<int> mat1(2,2,1);
    Matrix<int> mat2(2,2,2);
    Matrix<int> mat3 = mat1*mat2;
    std::vector <std::vector <double>> matrix(3, std::vector <double>(3, 0));
    Matrix <double> mat4(matrix);
    std::cout << mat3;
    std::cout << mat4;
    return 0;
    
}