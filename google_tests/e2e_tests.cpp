#include <gtest/gtest.h>
#include "../matrix.hpp"

TEST(e2e_test, first_test){
    matrix_template::Matrix<double> matrix(4,4);
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; j++){
            matrix[i][j] = 1;
        }
    }

    double det_correct = 0;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}

TEST(e2e_test, second_test){
    matrix_template::Matrix<double> matrix(4,4);
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; j++){
            matrix[i][j] = 0;
        }
    }

    double det_correct = 0;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}

TEST(e2e_test, thirth_test){
    matrix_template::Matrix<double> matrix(4,4);
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; j++){
            if (i == j){
                matrix[i][j] = 1;
            }
            else {
                matrix[i][j] = 0;
            }
        }
    }

    double det_correct = 1;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}

TEST(e2e_test, fourth_test){
    matrix_template::Matrix<double> matrix(3,3);
    matrix[0][0] = 0; matrix[0][1] = 0; matrix[0][2] = 1;
    matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0;
    matrix[2][0] = 1; matrix[2][1] = 0; matrix[2][2] = 0;

    double det_correct = -1;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}

TEST(e2e_test, fifth_test){
    matrix_template::Matrix<double> matrix(3,3);
    matrix[0][0] = 1; matrix[0][1] = 2; matrix[0][2] = 7;
    matrix[1][0] = 9; matrix[1][1] = 8; matrix[1][2] = 6;
    matrix[2][0] = 5; matrix[2][1] = 0; matrix[2][2] = 4;

    double det_correct = -260;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}

TEST(e2e_test, sixth_test){
    matrix_template::Matrix<double> matrix(3,3);
    matrix[0][0] = 2; matrix[0][1] = 12; matrix[0][2] = -1;
    matrix[1][0] = 5; matrix[1][1] = 4; matrix[1][2] = 0;
    matrix[2][0] = 1; matrix[2][1] = 2; matrix[2][2] = 1;

    double det_correct = -58;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}

TEST(e2e_test, seventh_test){
    matrix_template::Matrix<double> matrix(3,3);
    matrix[0][0] = 2.5; matrix[0][1] = 3.6; matrix[0][2] = -1.8;
    matrix[1][0] = 12.4; matrix[1][1] = 142.2; matrix[1][2] = 54.1;
    matrix[2][0] = 136.8; matrix[2][1] = -12.6; matrix[2][2] = 10.8;

    double det_correct = 67001.166;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}

TEST(e2e_test, eigth_test){
    matrix_template::Matrix<double> matrix(3,3);
    matrix[0][0] = 0; matrix[0][1] = 2; matrix[0][2] = 3;
    matrix[1][0] = 0; matrix[1][1] = 5; matrix[1][2] = 4;
    matrix[2][0] = 0; matrix[2][1] = 8; matrix[2][2] = 9;

    double det_correct = 0;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}

TEST(e2e_test, nineth_test){
    matrix_template::Matrix<double> matrix(3,3);
    matrix[0][0] = 2; matrix[0][1] = 12; matrix[0][2] = -1;
    matrix[1][0] = 0; matrix[1][1] = 4; matrix[1][2] = 0;
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 1;

    double det_correct = 8;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}

TEST(e2e_test, tenth_test){
    matrix_template::Matrix<double> matrix(3,3);
    matrix[0][0] = 2; matrix[0][1] = 0; matrix[0][2] = 0;
    matrix[1][0] = 5; matrix[1][1] = 4; matrix[1][2] = 0;
    matrix[2][0] = 1; matrix[2][1] = 2; matrix[2][2] = 1;

    double det_correct = 8;
    double det = matrix.determinant();
    ASSERT_EQ(det_correct, det) << "Test failed";
}