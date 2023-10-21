#include "matrix.hpp"

int main() {
    size_t size_x, size_y;
    std::cin >> size_x >> size_y;

    matrix_template::Matrix<double> matrix(size_x, size_y);


    for (size_t i = 0; i < size_y; i++) {
        for (size_t j = 0; j < size_x; j++) {
            std::cin >> matrix[i][j];
        }
    }
//    matrix.transpose(matrix);
//    for (size_t i = 0; i < size_y; i++) {
//        for (size_t j = 0; j < size_x; j++) {
//            std::cout << matrix[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
    double det = matrix.determinant();

    std::cout << det << std::endl;

//    Matrix<int> matrix1(3,4);
//    Matrix<int> matrix2(4, 4);
//
//    for (int i = 0; i < matrix1.Size(); i++){
//        for (int j = 0; j < matrix1[0].Size();j++){
//            matrix1[i][j] = 2;
//        }
//    }
//    for (int i = 0; i < matrix2.Size(); i++){
//        for (int j = 0; j < matrix2[0].Size();j++){
//            matrix2[i][j] = 3;
//        }
//    }
//
//     matrix = matrix + matrix;
//    for (int i = 0; i < matrix.Size(); i++){
//        for (int j = 0; j < matrix[0].Size();j++){
//            std::cout << matrix[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }


    return 0;
}