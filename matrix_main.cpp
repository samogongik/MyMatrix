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

    double det = matrix.determinant();

    std::cout << det << std::endl;




    return 0;
}