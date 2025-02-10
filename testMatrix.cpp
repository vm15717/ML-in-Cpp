#include "Matrix.cpp"

int main()
{
    Matrix<int> mat1(2,2,1);
    Matrix<int> mat2(2,2,2);
    mat1.insert(1,2, 0);
    mat2.insert(1,1, 3);
    Matrix<int> mat3 = mat1*mat2;
    std::vector <std::vector <double>> matrix(3, std::vector <double>(3, 0));
    Matrix <double> mat4(matrix);
    std::cout << mat3;
    std::cout << mat4;
    std::cout << mat3.transpose();
    return 0;
    
}