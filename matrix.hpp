#include <iostream>
#include <vector>


namespace matrix_template {
    template<typename T>
    concept numeric_type = std::copy_constructible<T> &&
                           std::copyable<T> && requires(T num, std::size_t n){
        { num + num } -> std::convertible_to<T>;
        { num - num } -> std::convertible_to<T>;
        { num * num } -> std::convertible_to<T>;
        { num / num } -> std::convertible_to<T>;

        { num != num } -> std::convertible_to<bool>;
        { num == num } -> std::convertible_to<bool>;

        { delete new(T) };
        { T(0) };
        { T(1) };
    };


    template<numeric_type T>
    class Vector {
    public:
        Vector() = default;

        Vector(const std::vector<T> &arr) : data(arr) {}

        size_t Size() const {
            return data.size();
        }

        T &operator[](const size_t num) {
            return data[num];
        }

        const T &operator[](const size_t num) const {
            return data[num];
        }

        Vector operator+(const Vector &vec) const {
            if (vec.Size() != data.size()) {
                std::cerr << "error: trying to add objects of different sizes" << std::endl;
            }

            std::vector<T> res(Size());
            for (int i = 0; i < Size(); i++) {
                res[i] = data[i] + vec[i];
            }

            return Vector(res);
        }

        Vector operator-(const Vector &vec) const {

            if (vec.Size() != data.size()) {
                std::cerr << "error: trying to subtract objects of different sizes" << std::endl;
            }

            std::vector<T> res(Size());
            for (int i = 0; i < Size(); i++) {
                res[i] = data[i] - vec[i];
            }
            return Vector(res);
        }

        Vector operator*(const T &num) const {
            std::vector<T> res(Size());
            for (int i = 0; i < Size(); i++) {
                res[i] = data[i] * num;
            }
            return Vector(res);
        }

        Vector operator/(const T &num) const {
            if (num == 0) {
                std::cerr << "error: attempt to divide by zero" << std::endl;
            }

            std::vector<T> res;
            for (int i = 0; i < data.size(); i++) {
                res[i] = data[i] / num;
            }
            return Vector(res);
        }

    private:
        std::vector<T> data;
    };

    template<numeric_type T>
    Vector<T> operator*(const T &num, const Vector<T> &vec) {
        std::vector<T> res(vec.Size());

        for (int i = 0; i < vec.Size(); i++) {
            res[i] = vec[i] * num;
        }
        return Vector<T>(res);
    }

    template<numeric_type T>
    class Matrix {
    public:
        Matrix(size_t size_x, size_t size_y) : size_x(size_x), size_y(size_y), data(size_x) {


            for (size_t i = 0; i < size_x; i++) {
                data[i] = Vector<T>(std::vector<T>(size_y));
            }
        }

        size_t Size() const {
            return data.size();
        }

        Vector<T> &operator[](const size_t num) {
            return data[num];
        }

        const Vector<T> &operator[](const size_t num) const {
            return data[num];
        }

        Matrix operator+(const Matrix &rhs) const {
            if (rhs.Size() != data.size() || rhs[0].Size() != data[0].Size()) {
                std::cerr << "error: attempt to add matrices of different sizes" << std::endl;
            }

            Matrix result(size_x, size_y);
            for (size_t i = 0; i < size_x; i++) {
                result[i] = data[i] + rhs[i];
            }
            return result;
        }

        Matrix operator-(const Matrix &rhs) const {

            if ((rhs.Size() != size_x) && (rhs[0].Size() != size_y)) {
                std::cerr << "error: attempt to subtract matrices of different sizes" << std::endl;
            }

            Matrix result(size_x, size_y);
            for (size_t i = 0; i < size_x; i++) {
                result[i] = data[i] - rhs[i];
            }
            return result;
        }

        Matrix operator*(const T &num) const {
            Matrix result(size_x, size_y);
            for (size_t i = 0; i < size_y; i++) {
                result[i] = data[i] * num;
            }
            return result;
        }

        Matrix operator*(const Matrix &rhs) const {
            if (size_y != rhs.Size()) {
                std::cerr << "error: attempt to multiply inconsistent matrices" << std::endl;
            }

            Matrix<T> result(size_x, rhs[0].Size());
            for (int i = 0; i < size_x; i++) {
                for (int j = 0; j < rhs[0].Size(); j++) {

                    int now = 0;
                    for (int k = 0; k < size_y; k++) {
                        now += data[i][k] * rhs[k][j];
                    }
                    result[i][j] = now;
                }
            }

            return result;
        }

        double determinant() const {

            if (size_y != size_x) {
                std::cerr << "error:attempt to calculate the determinant of a non-square matrix" << std::endl;
            }

            const unsigned int n = size_x;
            double det = 1.0;

            matrix_template::Matrix<T> data_copy(size_x, size_y);

            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    data_copy[i][j] = data[i][j];
                }
            }

            for (int i = 0; i < n; i++) {
                auto max_el = data_copy[i][i];
                int index = i;

                for (int j = i; j < n; j++) {
                    if (abs(data_copy[j][i]) > abs(max_el)) {
                        max_el = data_copy[j][i];
                        index = j;
                    }
                }

                if (index != i) {
                    det = det * (-1);
                    Vector<T> vec = data_copy[i];
                    data_copy[i] = data_copy[index];
                    data_copy[index] = vec;
                }

                for (int j = i + 1; j < n; j++) {
                    if (data_copy[i][i] == 0) return 0.0;
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
        size_t size_x;
        size_t size_y;
        std::vector<Vector<T>> data;

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

