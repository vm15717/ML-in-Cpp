#include "Matrix.hpp"

int main()
{
    Matrix<double> mat1(3,3,1);
    Matrix<double> mat2(3,3,1);
    mat2.insert(1, 1, 3);
    mat2.insert(0, 1, 2);
    mat2.insert(2, 2, 0);
    std::string type = "eye";
    Matrix <int> mat5(2, type);
    Matrix <double> mat4(5,1,1);
    Matrix <double> mat6(3,3,1);
    mat6.insert(2, 2, 0);
    mat6.insert(2, 1, 0);
    std::cout << mat6 << std::endl;
    std::cout << mat6.block(1, 0, 2, 3);
    return 0;
}