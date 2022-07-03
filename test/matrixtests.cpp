#include<string>
#include<iostream>
#include"../src/matrix.hpp"


bool testMGreaterThanNMatrixConstruction() {
    Matrix matrix("input/test2.mtx");
    std::string result = matrix.display();
    return result == "================================\nDisplaying Matrix: input/test2.mtx\n[ 3 ] rows.\n[ 4 ] columns.\n================================\n  1  2  3  4\n  5  6  7  8\n  9 10 11 12\n================================\n";
}

bool testMLessThanNMatrixConstruction() {
    Matrix matrix("input/test3.mtx");
    std::string result = matrix.display();
    return result == "================================\nDisplaying Matrix: input/test3.mtx\n[ 4 ] rows.\n[ 2 ] columns.\n================================\n  1  2\n  3  4\n  5  6\n  7  8\n================================\n";
}

bool testNxNMatrixConstruction() {
    Matrix matrix("input/test1.mtx");
    std::string result = matrix.display();
    return result == "================================\nDisplaying Matrix: input/test1.mtx\n[ 2 ] rows.\n[ 2 ] columns.\n================================\n 16  3\n  8  2\n================================\n";
}

bool testNxNTimesNxNMultiplication() {
    Matrix one("input/test1.mtx");
    Matrix two("input/test4.mtx");
    Matrix result = one * two;
    return result.display() == "================================\nDisplaying Matrix: input/test1.mtx\n[ 2 ] rows.\n[ 2 ] columns.\n================================\n 22 63\n 12 34\n================================\n";
}

/**
 * @brief Test driver for Matrix object testing
 * 
 * @return int exit code
 */
int main() {
    
    std::cout << "\nTesting Matrix Construction\n";
    std::cout << "=============================\n";
    std::cout << (testNxNMatrixConstruction() ? "PASS\n" : "FAIL\n");
    std::cout << (testMGreaterThanNMatrixConstruction() ? "PASS\n" : "FAIL\n");
    std::cout << (testMLessThanNMatrixConstruction() ? "PASS\n" : "FAIL\n");

    std::cout << "\nTesting Matrix Multiplication\n";
    std::cout << "=============================\n";
    std::cout << (testNxNTimesNxNMultiplication() ? "PASS\n" : "FAIL\n");
    return 0;
}