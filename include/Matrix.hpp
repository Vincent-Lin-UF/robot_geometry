#pragma once
#include <vector>
#include <initializer_list>
#include <stdexcept>
#include <cstddef>

namespace lin {

template<class T>
class Matrix {
public:
    Matrix() : r_(0), c_(0) {}
    Matrix(size_t r, size_t c, const T& val = T{}) : r_(r), c_(c), d_(r * c, val) {}
    Matrix(std::initializer_list<std::initializer_list<T>> init);

    std::size_t rows() const noexcept { return r_;}
    std::size_t cols() const noexcept { return c_;}

    T& operator()(std::size_t i, std::size_t j) { return d_[i * c_ + j]; }
    const T& operator()(std::size_t i, std::size_t j) const { return d_[i * c_ + j]; }

    // CPU functions
    Matrix transpose() const;
    Matrix operator+(const Matrix& B) const;
    Matrix operator*(const Matrix& B) const;

    const T* data() const { return d_.data(); }
    T* data() { return d_.data(); }
    
private:
    std::size_t r_, c_;
    std::vector<T> d_;

};

template<class T>
Matrix<T> matmul(const Matrix<T>& A, const Matrix<T>& B, bool prefer_gpu = false);

} //namespace lin

#include "Matrix.tpp"