#pragma once
#include <algorithm>

namespace lin {

// Init
template<class T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init) {
    r_ = init.size();
    c_ = r_ ? init.begin()->size() : 0;
    d_.reserve(r_ * c_);
    for (const auto& row : init){
        if (row.size() != c_) throw std::invalid_argument("Error: All rows must have the same number of columns");
        d_.insert(d_.end(), row.begin(), row.end()); 
    }
}

template<class T>
Matrix<T> Matrix<T>::transpose() const {
    Matrix<T> R(c_, r_, T{});
    for(size_t i = 0; i < r_; ++i){
        for(size_t j = 0; j < c_; ++j){
            R(j, i) = (*this)(i, j);
        }
    }
    return R;
}

template<class T>
Matrix<T> Matrix<T>::operator+(const Matrix<T>& B) const {
    if (r_ != B.r_ || c_ != B.c_) throw std::invalid_argument("Error: Matrix dimensions must agree for addition");
    Matrix<T> R(r_, c_, T{});
    for(size_t i = 0; i < r_ * c_; ++i){
        R.d_[i] = d_[i] + B.d_[i];
    }
    return R;
}

template<class T>
Matrix<T> Matrix<T>::operator-(const Matrix<T> & B) const {
    if (r_ != B.r_ || c_ != B.c_) throw std::invalid_argument("Error: Matrix dimensions must agree for subtraction");
    Matrix<T> R(r_, c_, T{});
    for(size_t i = 0; i < r_ * c_; ++i){
        R.d_[i] = d_[i] - B.d_[i];
    }
    return R;    
}

template<class T>
Matrix<T> Matrix<T>::operator*(const Matrix<T>& B) const {
    if (c_ != B.r_) throw std::invalid_argument("Error: Matrix dimensions must agree for multiplication");
    Matrix<T> R(r_, B.c_, T{});
    for(size_t i = 0; i < r_; ++i){
        for(size_t j = 0; j < B.c_; ++j){
            for(size_t k = 0; k < c_; ++k){
                R(i, j) += (*this)(i, k) * B(k, j);
            }
        }
    }
    return R;
}

}