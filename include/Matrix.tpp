#pragma once
#include <algorithm>

namespace lin {

// Init
template<class T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> init) {
    r_ = init.size();
    c_ = r_ ? init.begin()->size() : 0;
    d_.reserve(r_ * c_);
    for (auto& row : init){
        if (row.size() != c_) throw std::invalid_argument("Error: All rows must have the same number of columns");
        d_.insert(d_.end(), row.begin(), row.end()); 
    }
}

}