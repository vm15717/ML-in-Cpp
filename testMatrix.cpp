#include "Matrix.hpp"
#include <random>
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    Matrix<double> mat1(3,3,1);
    Matrix<double> mat2(3,3,1);
    mat2.insert(1, 1, 3);
    mat2.insert(0, 1, 2);
    mat2.insert(2, 2, 0);
    std::string type = "eye";
    Matrix <int> mat5(2, type);
    Matrix <double> mat4(5,1,1);
    Matrix <double> mat6(5,4,0);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::uniform_real_distribution <double> dist(0, 5);
            double k = dist(gen);
            mat6.insert(i, j, k);
        }
    }
    std::cout << mat6 << std::endl;
    //std::cout << mat6.getcols() << std::endl;
    //std::cout << mat6.getrows() << std::endl;
    Matrix <double> mat7 = mat6.block(0, 0, 5, 3);
    std::cout << mat7 << std::endl;
    Matrix <double> mat8(5, 1, 1);
    Matrix <double> mat9 = mat7.hstack(mat8);
    std::cout << mat9 << std::endl;
    std::cout << (mat9.transpose()*mat9).inverse() << std::endl;
    return 0;
}