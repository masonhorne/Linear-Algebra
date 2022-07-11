#include<string>
#include<iostream>
#include<fstream>
#include"../src/matrix.hpp"

//////////////////////////////////////////
// Helper functions for verifying tests
//////////////////////////////////////////

bool compareFiles(const std::string& p1, const std::string& p2) {
    // Open the two files we are comparing
    std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);
    // If files can't open return false
    if (f1.fail() || f2.fail()) return false;
    // If size mismatch return false
    if (f1.tellg() != f2.tellg()) return false; 
    // Move pointers to beginning of file
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    // Check if their values are equal
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()), std::istreambuf_iterator<char>(), std::istreambuf_iterator<char>(f2.rdbuf()));
}

//////////////////////////////////////////
//  Functions testing components
//////////////////////////////////////////

bool testMGreaterThanNMatrixConstruction() {
    Matrix matrix("input/test2.mtx");
        std::string expected = "================================\nDisplaying Matrix: input/test2.mtx\n[ 3 ] rows.\n[ 4 ] columns.\n================================\n    1    2    3    4\n    5    6    7    8\n    9   10   11   12\n================================\n";
    std::string result = matrix.display();
    return result == expected;
}

bool testMLessThanNMatrixConstruction() {
    Matrix matrix("input/test3.mtx");
    std::string expected = "================================\nDisplaying Matrix: input/test3.mtx\n[ 4 ] rows.\n[ 2 ] columns.\n================================\n    1    2\n    3    4\n    5    6\n    7    8\n================================\n";
    std::string result = matrix.display();
    return result == expected;
}

bool testNxNMatrixConstruction() {
    Matrix matrix("input/test1.mtx");
    std::string expected = "================================\nDisplaying Matrix: input/test1.mtx\n[ 2 ] rows.\n[ 2 ] columns.\n================================\n   16    3\n    8    2\n================================\n";
    std::string result = matrix.display();
    return result == expected;
}

bool testOutputMatrix(){
    Matrix matrix("input/test1.mtx");
    matrix.save("output/test1");
    return compareFiles("input/test1.mtx", "output/test1.mtx");
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
    Matrix expected("input/test22.mtx");
    Matrix result = one * two;
    return result == expected;
}

bool testMxNTimesNxMMultiplicationMGreaterThanN() {
    Matrix one("input/test5.mtx");
    Matrix two("input/test6.mtx");
    Matrix expected("input/test7.mtx");
    Matrix result = one * two;
    return result == expected;
}

bool testMxNTimesNxMMultiplicationMLessThanN() {
    Matrix one("input/test8.mtx");
    Matrix two("input/test9.mtx");
    Matrix expected("input/test10.mtx");
    Matrix result = one * two;
    return result == expected;
}

bool testNotEqualDimensions(){
    Matrix one("input/test1.mtx");
    Matrix two("input/test2.mtx");
    return one != two;
}

bool testNotEqualValue() {
    Matrix one("input/test1.mtx");
    Matrix two("input/test4.mtx");
    return one != two;
}

bool testNotEqualFalse() {
    Matrix one("input/test2.mtx");
    Matrix two("input/test15.mtx");
    return !(one.getRow(1) != two);
}

bool testValidAdd() {
    Matrix one("input/test1.mtx");
    Matrix two("input/test4.mtx");
    Matrix expected("input/test23.mtx");
    return one + two == expected;
}

bool testInvalidAdd() {
    Matrix one("input/test1.mtx");
    Matrix two("input/test2.mtx");
    try {
        one + two;
        return false;
    } catch (std::runtime_error error) {
        return true;
    }
}

bool testValidSubtract() {
    Matrix one("input/test1.mtx");
    Matrix two("input/test4.mtx");
    Matrix expected("input/test24.mtx");
    return one - two == expected;
}

bool testInvalidSubtract() {
    Matrix one("input/test1.mtx");
    Matrix two("input/test2.mtx");
    try {
        one + two;
        return false;
    } catch (std::runtime_error error) {
        return true;
    }
}

bool testMultiplyDouble() {
    double value = 4;
    Matrix one("input/test5.mtx");
    Matrix expected("input/test25.mtx");
    return (one * value) == expected;
}

bool testMultiplyInteger() {
    int value = 4;
    Matrix one("input/test5.mtx");
    Matrix expected("input/test25.mtx");
    return (one * value) == expected;
}

bool testMultiplyFloat() {
    float value = 4;
    Matrix one("input/test5.mtx");
    Matrix expected("input/test25.mtx");
    return (one * value) == expected;
}

bool testDivideDouble() {
    double value = 4;
    Matrix one("input/test25.mtx");
    Matrix expected("input/test5.mtx");
    return (one / value) == expected;
}

bool testDivideInteger() {
    int value = 4;
    Matrix one("input/test25.mtx");
    Matrix expected("input/test5.mtx");
    return (one / value) == expected;
}

bool testDivideFloat() {
    float value = 4;
    Matrix one("input/test25.mtx");
    Matrix expected("input/test5.mtx");
    return (one / value) == expected;
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
        std::string expected = "Unable to calculate Determinant of: input/test2.mtx\n================================\nMatrix must be in the form of NxN.\n";
        return expected == error.what();
    }
}

bool testInverseTrivial() {
    Matrix matrix("input/test18.mtx");
    Matrix expected("input/test19.mtx");
    return matrix.inverse() == expected;
} 

bool testInverseComplex() {
    Matrix matrix("input/test20.mtx");
    Matrix expected("input/test21.mtx");
    return matrix.inverse() == expected;
}

bool testInverseInvalid() {
    Matrix matrix("input/test6.mtx");
    try {
        matrix.inverse();
        return false;
    } catch(std::runtime_error error) {
        std::string expected = "Unable to calculate Inverse of: input/test6.mtx\n================================\nRequirements of Inverse calculation: \n\t1) Matrix being operated on is NxN.\n\t2) Matrix must be able to calculate its values via Cramers Rule.\n\t   NOTE: This may prevent the calculation of some inverses.\n";
        return true;
    }
}

//////////////////////////////////////////
//  Test Suites for given functionality
//////////////////////////////////////////

void testFileIO() {
    std::cout << "\nTesting Matrix IO\n";
    std::cout << "=============================\n";
    std::cout << (testNxNMatrixConstruction() ? "PASS\n" : "FAIL\n");
    std::cout << (testMGreaterThanNMatrixConstruction() ? "PASS\n" : "FAIL\n");
    std::cout << (testMLessThanNMatrixConstruction() ? "PASS\n" : "FAIL\n");
    std::cout << (testOutputMatrix() ? "PASS\n" : "FAIL\n");
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
    std::cout << (testInverseComplex() ? "PASS\n" : "FAIL\n");
    std::cout << (testInverseInvalid() ? "PASS\n" : "FAIL\n");
}

void testMatrixOperations() {
    std::cout << "\nTesting Matrix Operator Calculations\n";
    std::cout << "=============================\n";
    std::cout << (testNotEqualDimensions() ? "PASS\n" : "FAIL\n");
    std::cout << (testNotEqualValue() ? "PASS\n" : "FAIL\n");
    std::cout << (testNotEqualFalse() ? "PASS\n" : "FAIL\n");
    std::cout << (testValidAdd() ? "PASS\n" : "FAIL\n");
    std::cout << (testInvalidAdd() ? "PASS\n" : "FAIL\n");
    std::cout << (testValidSubtract() ? "PASS\n" : "FAIL\n");
    std::cout << (testInvalidSubtract() ? "PASS\n" : "FAIL\n");
    std::cout << (testMultiplyDouble() ? "PASS\n" : "FAIL\n");
    std::cout << (testMultiplyInteger() ? "PASS\n" : "FAIL\n");
    std::cout << (testMultiplyFloat() ? "PASS\n" : "FAIL\n");
    std::cout << (testDivideDouble() ? "PASS\n" : "FAIL\n");
    std::cout << (testDivideInteger() ? "PASS\n" : "FAIL\n");
    std::cout << (testDivideFloat() ? "PASS\n" : "FAIL\n");
    std::cout << (testNxNTimesNxNMultiplication() ? "PASS\n" : "FAIL\n");
    std::cout << (testMxNTimesNxMMultiplicationMGreaterThanN() ? "PASS\n" : "FAIL\n");
    std::cout << (testMxNTimesNxMMultiplicationMLessThanN() ? "PASS\n" : "FAIL\n");
}

/**
 * @brief Test driver for Matrix object testing
 * 
 * @return int exit code
 */
int main() {

    testFileIO();
    testAccessors();
    testInvalidAccessors();
    testMatrixOperations();
    testLUDecomposition();
    testDeterminantCalculation();
    testInverseCalculation();

    return 0;
}