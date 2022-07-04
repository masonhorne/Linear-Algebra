#include<string>
#include<iostream>
#include"../src/matrix.hpp"

//////////////////////////////////////////
//  Functions testing components
//////////////////////////////////////////

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

bool testMatrixRowAccess() {
    Matrix matrix("input/test2.mtx");
    Matrix expected("input/test15.mtx");
    Matrix row = matrix.getRow(1);
    return expected == row;
}

bool testMatrixColumnAccess() {
    Matrix matrix("input/test3.mtx");
    Matrix expected("input/test16.mtx");
    Matrix column = matrix.getColumn(2);
    return expected == column;
}

bool testMatrixAccess() {
    Matrix matrix("input/test6.mtx");
    int expected = 0;
    int value = matrix.access(2, 3);
    return expected == value;
}

bool testMatrixInvalidRowAccess() {
    Matrix matrix("input/test1.mtx");
    try {
        matrix.getRow(3);
        return false;
    } catch (std::runtime_error error) {
        std::string expected = "Invalid row requested: input/test1.mtx\nThe request row number was 3.\nRemember that matrices are 1-indexed.\n";
        return expected == error.what();
    }
}

bool testMatrixInvalidColumnAccess() {
    Matrix matrix("input/test9.mtx");
    try {
        matrix.getColumn(2);
        return false;
    } catch (std::runtime_error error) {
        std::string expected = "Invalid column requested: input/test9.mtx\nThe request column number was 2.\nRemember that matrices are 1-indexed.\n";
        return expected == error.what();
    }
}

bool testMatrixInvalidAccess() {
    Matrix matrix("input/test8.mtx");
    try {
        matrix.access(2, 2);
        return false;
    } catch(std::runtime_error error) {
        std::string expected = "Invalid row requested: input/test8.mtx\nThe request row number was 2.\nRemember that matrices are 1-indexed.\n";
        if(expected != error.what()) return false;
    }
    try {
        matrix.access(1, 3);
        return false;
    } catch (std::runtime_error error) {
        std::string expected = "Invalid column requested: input/test8.mtx\nThe request column number was 3.\nRemember that matrices are 1-indexed.\n";
        return expected == error.what();
    }
}

bool testNxNTimesNxNMultiplication() {
    Matrix one("input/test1.mtx");
    Matrix two("input/test4.mtx");
    Matrix result = one * two;
    return result.display() == "================================\nDisplaying Matrix: input/test1.mtx\n[ 2 ] rows.\n[ 2 ] columns.\n================================\n 22 63\n 12 34\n================================\n";
}

bool testMxNTimesNxMMultiplicationMGreaterThanN() {
    Matrix one("input/test5.mtx");
    Matrix two("input/test6.mtx");
    Matrix result = one * two;
    Matrix expected("input/test7.mtx");
    return result == expected;
}

bool testMxNTimesNxMMultiplicationMLessThanN() {
    Matrix one("input/test8.mtx");
    Matrix two("input/test9.mtx");
    Matrix result = one * two;
    Matrix expected("input/test10.mtx");
    return result == expected;
}

bool testValidLUDecomposition() {
    Matrix A("input/test11.mtx");
    Matrix expectedL("input/test12.mtx");
    Matrix expectedU("input/test13.mtx");
    std::vector<Matrix> result = A.decomposeLU();
    return result[0] == expectedL && result[1] == expectedU && result[0] * result[1] == A;
}

bool testInvalidLUDecompositionDimensions() {
    Matrix A("input/test2.mtx");
    try {
        A.decomposeLU();
        return false;
    } catch(std::runtime_error error) {
        std::string expected = "Unable to complete LU Decomposition of: input/test2.mtx\n================================\nRequirements of LU Decomposition: \n\t1) Matrix being decomposed is NxN.\n\t2) Matrix must be able to factorize into components L and U.\n\t   NOTE: For the requirements of factorizing look into Gussian Elimination.\n";
        return expected == error.what();
    }
}

bool testInvalidLUDecompositionFactorization() {
    Matrix A("input/test14.mtx");
    try {
        A.decomposeLU();
        return false;
    } catch(std::runtime_error error) {
        std::string expected = "Unable to complete LU Decomposition of: input/test14.mtx\n================================\nRequirements of LU Decomposition: \n\t1) Matrix being decomposed is NxN.\n\t2) Matrix must be able to factorize into components L and U.\n\t   NOTE: For the requirements of factorizing look into Gussian Elimination.\n";
        return expected == error.what();
    }
}

bool testDeterminantTrivial() {
    Matrix one("input/test4.mtx");
    int expected1 = -1;
    Matrix two("input/test11.mtx");
    int expected2 = 12;
    return expected1 == one.determinant() && expected2 == two.determinant();
}

bool testDeterminantComplex() {
    Matrix matrix("input/test17.mtx");
    int expected = -6;
    return expected == matrix.determinant();
}

bool testDeterminantInvalid() {
    Matrix matrix("input/test2.mtx");
    try {
        matrix.determinant();
        return false;
    } catch(std::runtime_error error) {
        std::string expected = "Unable to calculate Determinant of: input/test2.mtx\n================================\nRequirements of Determinant calculation: \n\t1) Matrix being decomposed is NxN.\n\t2) Matrix must be able to factorize into components L and U via Guassian Elimination.\n\t   NOTE: This may prevent the calculation of some determinants.\n";
        return expected == error.what();
    }
}

bool testInverseTrivial() {
    Matrix one("input/test18.mtx");
    Matrix two("input/test19.mtx");
    return one.inverse() == two;
}

//////////////////////////////////////////
//  Test Suites for given functionality
//////////////////////////////////////////

void testConstruction() {
    std::cout << "\nTesting Matrix Construction\n";
    std::cout << "=============================\n";
    std::cout << (testNxNMatrixConstruction() ? "PASS\n" : "FAIL\n");
    std::cout << (testMGreaterThanNMatrixConstruction() ? "PASS\n" : "FAIL\n");
    std::cout << (testMLessThanNMatrixConstruction() ? "PASS\n" : "FAIL\n");
}

void testAccessors() {
    std::cout << "\nTesting Matrix Accessors\n";
    std::cout << "=============================\n";
    std::cout << (testMatrixRowAccess() ? "PASS\n" : "FAIL\n");
    std::cout << (testMatrixColumnAccess() ? "PASS\n" : "FAIL\n");
    std::cout << (testMatrixAccess() ? "PASS\n" : "FAIL\n");
}

void testInvalidAccessors() {
    std::cout << "\nTesting Matrix Invalid Accessors\n";
    std::cout << "=============================\n";
    std::cout << (testMatrixInvalidRowAccess() ? "PASS\n" : "FAIL\n");
    std::cout << (testMatrixInvalidColumnAccess() ? "PASS\n" : "FAIL\n");
    std::cout << (testMatrixInvalidAccess() ? "PASS\n" : "FAIL\n");
}

void testMatrixMultiplication() {
    std::cout << "\nTesting Matrix Multiplication\n";
    std::cout << "=============================\n";
    std::cout << (testNxNTimesNxNMultiplication() ? "PASS\n" : "FAIL\n");
    std::cout << (testMxNTimesNxMMultiplicationMGreaterThanN() ? "PASS\n" : "FAIL\n");
    std::cout << (testMxNTimesNxMMultiplicationMLessThanN() ? "PASS\n" : "FAIL\n");
}

void testLUDecomposition() {
    std::cout << "\nTesting Matrix LU Decomposition\n";
    std::cout << "=============================\n";
    std::cout << (testValidLUDecomposition() ? "PASS\n" : "FAIL\n");
    std::cout << (testInvalidLUDecompositionDimensions() ? "PASS\n" : "FAIL\n");
    std::cout << (testInvalidLUDecompositionFactorization() ? "PASS\n" : "FAIL\n");
}

void testDeterminantCalculation() {
    std::cout << "\nTesting Matrix Determinant Calculation\n";
    std::cout << "=============================\n";
    std::cout << (testDeterminantTrivial() ? "PASS\n" : "FAIL\n");
    std::cout << (testDeterminantComplex() ? "PASS\n" : "FAIL\n");
    std::cout << (testDeterminantInvalid() ? "PASS\n" : "FAIL\n");
}

void testInverseCalculation() {
    std::cout << "\nTesting Matrix Inverse Calculation\n";
    std::cout << "=============================\n";
    std::cout << (testInverseTrivial() ? "PASS\n" : "FAIL\n");
}

/**
 * @brief Test driver for Matrix object testing
 * 
 * @return int exit code
 */
int main() {

    testConstruction();
    testAccessors();
    testInvalidAccessors();
    testMatrixMultiplication();
    testLUDecomposition();
    testDeterminantCalculation();
    testInverseCalculation();

    return 0;
}