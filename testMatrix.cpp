#include "Matrix.cpp"

int main()
{
    Matrix<int> mat1(2,2,1);
    Matrix<int> mat2(2,2,2);
    Matrix<int> mat3 = mat1*mat2;
    std::cout << mat3 << std::endl;
    return 0;
    
}