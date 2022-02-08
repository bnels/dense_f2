#include "f2_matrix.hpp"
#include "f2_vector.hpp"
#include <iostream>
#include <vector>

int main() {

    F2Matrix A(3,3);
    A.print();

    std::cout << "\n";
    A.set(0,0, 1);
    A.set(1,1,1);
    A.print();

    std::cout << "\n";
    std::vector<size_t> row{0,0,1,1,2,3,3,2,1};
    std::vector<size_t> col{0,1,0,1,2,2,3,3,3};
    F2Matrix B(4,4,row, col);
    B.print();
    // std::cout << B.col(0).pivot() << std::endl;

    std::cout << "\n";
    auto p2c = reduce(B);
    B.print();


    return EXIT_SUCCESS;
}
