#include <random>
#include "matrix.hpp"

int main(){
    std::random_device rd;
    std::mt19937 gen(rd());

    double min = -200.0;
    double max = 200.0;

    std::uniform_real_distribution<double> distribution_real(min, max);

    for (int i = 1; i <= 100; i++){
        matrix_template::Matrix<double> matrix(100,100);
        double det_correct = 1.0;

        for (size_t j = 0; j < 100; j++){
            for (size_t k = 0; k < 100; k++ ){
                if (j == k) {
                    matrix[j][k] = distribution_real(gen);
                    det_correct = det_correct * matrix[j][k];
                }
                else matrix[j][k] = 0.0;
            }
        }

        for (size_t i = 0; i < 99; i++){
            matrix[i+1] = matrix[i+1] + matrix[i];
        }

        for (size_t i = 0; i < 99; i--){
<<<<<<< HEAD
            matrix[i] = matrix[i] + matrix[99] ;
        }

        double det = matrix.determinant();
        if (abs(det) < 0.0001){
            if (abs(det - det_correct < 0.0001)){
                std::cout << "Test" <<" "<< i << " " << "passed" << std::endl;
            }
            else{
                std::cout << "Test" << " " << i <<" " << "failed. Expected answer ="
                          << " " <<  det_correct << "Result of the program =" << " "
                          << det << std::endl;
            }
        }
        else{
            double delta = abs(det / det_correct);

            if (abs(1 - delta) < 0.0001){
                std::cout << "Test" <<" "<< i << " " << "passed" << std::endl;
            }
            else{
                std::cout << "Test" << " " << i <<" " << "failed. Expected answer ="
                          << " " <<  det_correct << "Result of the program =" << " "
                          << det << std::endl;
            }
        }
=======
            matrix[i] = matrix[i] + matrix[99] * 2 ;
        }

        double det = matrix.determinant();
        double result = det_correct / det;
        if ((result - 1) < 0.000001){
            std::cout << "Test" <<" "<< i << " " << "passed" << std::endl;
        }
        else{
//            std::cout << "Test" << " " << i <<" " << "failed. Expected answer ="
//                      << " " <<  det_correct << "Result of the program =" << " "
//                      << det << std::endl ;
                std::cout << result << std::endl;
        }

>>>>>>> 8ba9e34 (Initial commit)
    }
};