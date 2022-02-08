#pragma once

#include <cstddef>

template <typename T>
class F2Vector {
private:
    T* begin;
    T* end;

public:
    F2Vector(T* begin, T* end) : begin(begin), end(end) {}

    /**
    add data in other vector to this vector
    */
    void axpy(F2Vector other) {
        T* it1 = begin;
        T* it2 = other.begin;
        while (it1 != end) {
            *it1 = *it1 ^ *it2;
            ++it1; ++it2;
        }
    }

	/**

	returns last non-zero index
	-1 if vector is zero.

	assumes uint64_t

	__builtin_clzll(); is number of leading zeros
	*/
    int pivot() {
		T* it = end - 1;
		while (it >= begin) {
			if (*it != 0) {
				return (int) (64 * (1 + it - begin) - __builtin_clzll(*it)) - 1;
			}
			--it;
		}
		return -1; // no pivot

    }

	/**

	return number of non-zeros

	assumes T is unit64_t
	*/
    size_t nnz() const {
		size_t s = 0; // sum
		T* it = begin;
		while (it != end) {
			s += __builtin_popcountll(*it);
		}
		return s;
	}
};
