#include <iostream>
#include <cstring>
#include<utility>
#include<cmath>
#include"Vector.hpp"


namespace matrix_template {
    template<numeric_type T>
    class Matrix{
    public:
        Matrix(Vector<T> *arr, size_t size_x, size_t size_y) : Matrix(size_x, size_y) {
            if (arr) {
                for (size_t i = 0; i < size_y; i++){
                    data[i] = arr[i];
                }
            }
        }

        Matrix(size_t size_x, size_t size_y) : size_x(size_x), size_y(size_y) {
            if (size_y && size_x) {
                data = new Vector<T>[size_y];
                for (size_t i = 0; i < size_y; i++) {
                    data[i] = Vector<T>(size_x);
                }
            }
            else{
                std::cerr << "attempt create matrix of zero size" << std::endl;
            }
        }

        ~Matrix() {
            delete[] data;
        }

        Matrix(const Matrix& rhs): Matrix(rhs.data, rhs.size_x, rhs.size_y){}

        Matrix(Matrix&& rhs): data(std::exchange(rhs.data, nullptr)), size_x(rhs.size_x), size_y(rhs.size_y){}

        Matrix& operator=(const Matrix& rhs){
            for (size_t i = 0; i < size_y; i++) {
                data[i] = rhs[i];
            }
            return *this;
        }

        Matrix& operator=(Matrix&& rhs){
            std::swap(data, rhs.data);
            std::swap(size_x, rhs.size_x);
            std::swap(size_y, rhs.size_y);
            return *this;
        }

        Vector<T> &operator[](const size_t num){
            return data[num];
        }

        const Vector<T> &operator[](const size_t num) const{
            return data[num];
        }

        Matrix operator+(const Matrix &rhs) const {
            if (rhs.Size() != size_y || rhs[0].Size() != data[0].Size()) {
                std::cerr << "error: attempt to add matrices of different sizes" << std::endl;
            }

            Matrix result(size_y, size_y);
            for (size_t i = 0; i < size_y; i++) {
                result[i] = data[i] + rhs[i];
            }
            return result;
        }

        Matrix operator-() const{
            matrix_template::Matrix<T> result(size_y,size_x);
            for (int i = 0; i < size_y; i++){
                result[i] = -data[i];
            }

            return result;
        }

        Matrix operator-(const Matrix &rhs) const {

            if ((rhs.Size() != size_y) && (rhs[0].Size() != size_y)) {
                std::cerr << "error: attempt to subtract matrices of different sizes" << std::endl;
            }

            return (*this) + (-rhs);
        }

        Matrix operator*(const T &num) const {
            Matrix result(size_y, size_x);
            for (size_t i = 0; i < size_y; i++) {
                result[i] = data[i] * num;
            }
            return result;
        }

        Matrix operator*(const Matrix &rhs) const {
            if (size_y != rhs.Size()) {
                std::cerr << "error: attempt to multiply inconsistent matrices" << std::endl;
            }

            Matrix<T> result(size_y, rhs[0].Size());
            for (int i = 0; i < size_y; i++) {
                for (int j = 0; j < rhs[0].Size(); j++) {

                    int now = 0;
                    for (int k = 0; k < size_x; k++) {
                        now += data[i][k] * rhs[k][j];
                    }
                    result[i][j] = now;
                }
            }

            return result;
        }

        double determinant() const {
            if (size_x == 0){
                return 0;
            }
            if (size_y != size_x) {
                std::cerr << "error:attempt to calculate the determinant of a non-square matrix" << std::endl;
            }

            const unsigned int n = size_x;
            double det = 1.0;

            Matrix<double> data_copy(size_x, size_y);
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    data_copy[i][j] = static_cast<double>(data[i][j]);;

                }
            }

            for (int i = 0; i < n; i++) {
                auto max_el = data_copy[i][i];
                int index = i;

                for (int j = i; j < n; j++) {
                    if (fabs(data_copy[j][i]) > fabs(max_el)) {
                        max_el = data_copy[j][i];
                        index = j;
                    }
                }

                if (index != i) {
                    det = det * (-1);
                    Vector<double> vec = data_copy[i];
                    data_copy[i] = data_copy[index];
                    data_copy[index] = vec;
                }

                for (int j = i + 1; j < n; j++) {
                    if (data_copy[i][i] == 0.0) return 0.0;
                    auto factor = data_copy[j][i] / data_copy[i][i];
                    data_copy[j] = data_copy[j] - data_copy[i] * factor;
                }

                det = det * data_copy[i][i];

            }

            return det;
        }

        void transpose(Matrix &matrix) {
            if (size_y != size_x) {
                std::cerr << "error:attempt to transpose a non-square matrix" << std::endl;
            }

            for (int i = 0; i < size_x; i++) {
                for (int j = i; j < size_x; j++) {
                    auto now = matrix[i][j];
                    matrix[i][j] = matrix[j][i];
                    matrix[j][i] = now;
                }
            }
        }

    private:
        size_t size_y = 0;
        size_t size_x = 0;
        Vector<T> *data = nullptr;

    };

    template<numeric_type T>
    Matrix<T> operator*(const T &num, const Matrix<T> &matrix) {
        Matrix<T> result(matrix.size_x, matrix.size_y);
        for (size_t i = 0; i < matrix.size_y; i++) {
            result[i] = matrix[i] * num;
        }
        return result;
    }
}