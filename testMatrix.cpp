#include "Matrix.cpp"

int main()
{
    Matrix<double> mat1(2,2,1);
    Matrix<double> mat2(2,2,2);
    mat2.insert(1, 1, 3);
    //mat2.insert(0, 1, 2);
    //Matrix<int> mat3 = mat1*mat2;
    //std::vector <std::vector <double>> matrix(3, std::vector <double>(3, 0));
    //Matrix <double> mat4(matrix);
    //std::cout << mat3;
    //std::cout << mat4;
    //std::cout << mat3.transpose();
    std::string type = "eye";
    Matrix <int> mat5(2, type);
    //std::cout << mat5;
    std::cout << mat2;
    std::cout << mat2.inverse();
    return 0;
    
}