#include <iostream>
#include <cstring>
#include<utility>
#include<cmath>


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
    class Vector{
    public:
        Vector(const T* arr, const size_t size_x): Vector(size_x){
            if (arr) {
                for (size_t i = 0; i < size_x; i++){
                    data[i] = arr[i];
                }
            }
        }

        Vector(const size_t size_x): size_x(size_x) {
            data = new T[size_x];
        }

        Vector() = default;

        ~Vector(){
            delete[] data;
        }

        Vector(const Vector& rhs): Vector(rhs.data, rhs.size_x){}

        Vector(Vector&& rhs): data(std::exchange(rhs.data, nullptr)), size_x(rhs.size_x){}

        Vector& operator=(const Vector& rhs){
            for(size_t i = 0; i < size_x; i++) {
                data[i] = rhs[i];
            }
            return *this;
        }

        Vector& operator=(Vector&& rhs){
            std::swap(data, rhs.data);
            std::swap(size_x, rhs.size_x);
            return *this;
        }

        size_t Size() const{
            return size_x;
        }

        T &operator[](const size_t num){
            return data[num];
        }

        const T &operator[](const size_t num) const{
            return data[num];
        }

        Vector operator+(const Vector& rhs) const{
            if (rhs.Size() != size_x ) {
                std::cerr << "error: trying to add objects of different sizes" << std::endl;
            }

            Vector<T> result(data, size_x);
            for (int i = 0; i < size_x; i++){
                result[i] = data[i] + rhs[i];
            }

            return result;
        }

        Vector operator-() const {
            Vector<T> result(data, size_x);
            for (int i = 0; i < Size(); i++) {
                result[i] = -data[i];
            }
            return Vector(result);
        }

        Vector operator-(const Vector &vec) const {
            if (vec.Size() != size_x) {
                std::cerr << "error: trying to subtract objects of different sizes" << std::endl;
            }

            return (*this) + (-vec);
        }

        Vector operator*(const T &num) const {
            Vector<T> result(data, size_x);
            for (int i = 0; i < Size(); i++) {
                result[i] = data[i] * num;
            }
            return Vector(result);
        }

        Vector operator/(const T &num) const {
            if (num == 0) {
                std::cerr << "error: attempt to divide by zero" << std::endl;
            }

            Vector<T> result(data, size_x);
            for (int i = 0; i < size_x; i++) {
                result[i] = data[i] / num;
            }
            return Vector(result);
        }

    private:
        size_t size_x = 0;
        T *data = nullptr;
    };

    template<numeric_type T>
    Vector<T> operator*(const T &num, const Vector<T> &vec) {
        T *arr = new T[vec.Size()];

        for (int i = 0; i < vec.Size(); i++) {
            arr[i] = vec[i] * num;
        }

        Vector<T> result(arr, vec.Size());
        delete[] arr;

        return Vector<T>(result);
    }

}
