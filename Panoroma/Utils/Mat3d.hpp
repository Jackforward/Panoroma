//
//  Mat3d.hpp
//  Panoroma
//
//  Created by Neil on 08/11/2016.
//  Copyright © 2016 Neil. All rights reserved.
//

#ifndef Mat3d_hpp
#define Mat3d_hpp

#include <stdio.h>
#include "MatXd.hpp"

template<typename T>
class Mat3d : public MatXd<T> {
    int n_rows_, n_cols_, n_channels_;
    
public:
    Mat3d() {
        n_cols_ = n_rows_ = 0;
    };
    Mat3d(int n_rows, int n_cols, int n_channels) : MatXd<T>(3, n_rows, n_cols, n_channels), n_cols_(n_cols), n_rows_(n_rows), n_channels_(n_channels) {
    };
    ~Mat3d() {
    }
    Mat3d(const Mat3d& mat) : Mat3d(mat.n_rows(), mat.n_cols(), mat.n_channels()){
        memcpy(this->raw_ptr(), mat.raw_ptr(), sizeof(T) * mat.n_elem());
    }

    
    Mat3d<T>& operator=(Mat3d<T>&& mat) {
        if (this->raw_data_ && this->n_elems_ != mat.n_elem()) {
            delete [] this->raw_data_;
            this->raw_data_ = new T[mat.n_elem()];
        }
        n_cols_ = mat.n_cols();
        n_rows_ = mat.n_rows();
        n_channels_ = mat.n_channels();
        memmove(this->raw_data_, mat.raw_ptr(), sizeof(T) * mat.n_elem());
        return *this;
    }
    
    Mat3d<T>& operator=(const Mat3d<T>& mat) {
        if (this->raw_data_ && this->n_elem_ != mat.n_elem()) {
            delete [] this->raw_data_;
            this->raw_data_ = new T[mat.n_elem()];
        }
        n_cols_ = mat.n_cols();
        n_rows_ = mat.n_rows();
        n_channels_ = mat.n_channels();
        memcpy(this->raw_data_, mat.raw_ptr(), sizeof(T) * mat.n_elem());
        return *this;
    }
    
    int n_rows() const {
        return n_rows_;
    }
    
    int n_cols() const {
        return n_cols_;
    }
    
    int n_channels() const {
        return n_channels_;
    }
    
    T& at(int row, int col, int channel) {
        return *(this->raw_data_ + (row * n_cols_ + col) * n_channels_ + channel);
    }
    
    const T& at(int row, int col, int channel) const {
        return *(this->raw_data_ + (row * n_cols_ + col) * n_channels_ + channel);
    }
};

typedef Mat3d<unsigned char> Image;

#endif /* Mat3d_hpp */
