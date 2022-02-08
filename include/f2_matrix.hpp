#pragma once
#include <cstddef>
#include <vector>
#include <utility>
#include <iostream>
#include "f2_vector.hpp"

/**
template over data type T
assumed to be uint64_t or similar


*/
template <typename T=uint64_t>
class F2Matrix {
private:
    std::vector<T> _data;
    size_t m;
    size_t n;

    size_t colblocks; // number of blocks in each column

    static const size_t Tbits = sizeof(T) * 8; // number of bits for type

    inline T* data() {
        return _data.data();
    }

public:

    inline size_t nrow() const { return m; }
    inline size_t ncol() const { return n; }

    /**
    get i,j entry
    */
    bool get(size_t i, size_t j) {
        size_t offset_i = i / Tbits;
        size_t ind_i = i % Tbits;
        size_t offset = j * colblocks  + offset_i;
        return (*(data() + offset) >> ind_i) & 0x1;
    }

    /**
    set i,j entry
    */
    // template <typename TI>
    void set(size_t i, size_t j, bool val) {
        size_t offset_i = i / Tbits;
        size_t ind_i = i % Tbits;
        size_t offset = j * colblocks  + offset_i;
        if (val) {
            *(data() + offset) = *(data() + offset) | (0x1 << ind_i);
        } else {
            *(data() + offset) = *(data() + offset) & (0xFFFFFFFF - (0x1 << ind_i));
        }
    }

    F2Matrix(size_t m, size_t n) : m(m), n(n) {
        colblocks = m / Tbits; // number of column blocks
        colblocks = colblocks + ((m % Tbits) > 0); // add 1 if necessary
        _data = std::vector<T>(n * colblocks, 0x0);
    }

    /**
    initialize matrix with non-zero indices specified by
    row and column vectors
    */
    F2Matrix(size_t m, size_t n,
        const std::vector<size_t>& row,
        const std::vector<size_t>& col
    ) : m(m), n(n) {
        colblocks = m / Tbits; // number of column blocks
        colblocks = colblocks + ((m % Tbits) > 0); // add 1 if necessary
        _data = std::vector<T>(n * colblocks, 0x0);

        auto rit = row.begin();
        auto cit = col.begin();
        while (rit != row.end()) {
            set(*rit++, *cit++, 1);
        }
    }


    inline F2Vector<T> col(size_t j) {
        return F2Vector(data() + colblocks*j, data() + colblocks*(j+1));
    }




    void print() {
        for (size_t i = 0; i < m; ++i) {
            for (size_t j = 0; j < n; ++j) {
                std::cout << get(i,j) << " ";
            }
            std::cout << std::endl;
        }
    }

};

template <typename T>
std::vector<int> reduce(F2Matrix<T>& A) {
    std::vector<int> p2c(A.nrow(), -1);
    for (size_t j = 0; j < A.ncol(); ++j) {
        auto colj = A.col(j);
        auto pivj = colj.pivot();
        while (pivj > -1) {

            int j2 = p2c[pivj];
            // std::cout << "piv(" << j << ") = " << pivj << "p2c[pivj] = " << j2 << std::endl;
            if (j2 > -1) {
                colj.axpy(A.col(j2));
            } else {
                // new pivot
                p2c[pivj] = j;
                break;
            }
            pivj = colj.pivot();
        }
    }

    return p2c;
}
