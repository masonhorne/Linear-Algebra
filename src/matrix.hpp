#include<string>
#include<vector>
#include"iohandler.hpp"
#ifndef MATRIX_HPP
#define MATRIX_HPP

/**
 * @brief A class representing a matrix object
 * 
 */
class Matrix {
    private:
    /** Number of columns in the matrix */
    int m;
    /** Number of columns in the matrix */
    int n;
    /** Filepointer used as identifier for logging */
    std::string fp;
    /** Underlying data structure for the matrix */
    std::vector<std::vector<double>> matrix;

    /**
     * @brief Special constructor for building a matrix from a given
     * grid of input values
     * 
     * @param filepath filepath identifer for the matrix
     * @param vals grid of values to populate matrix with
     */
    Matrix(std::string filepath, std::vector<std::vector<double>> vals);

    public:
    /**
     * @brief Constructs a matrix from an input file
     * 
     * @param filepath 
     */
    Matrix(std::string filepath);

    /**
     * @brief Exports a matrix to an mtx file with the
     * provided filename
     * 
     * @param filename filename to save matrix as
     */
    void save(std::string filename);

    /**
     * @brief Return the matrix for a given row
     * 
     * @param row index of row you wish to access
     * @return Matrix a matrix of the row
     */
    Matrix getRow(int row);

    /**
     * @brief Return the matrix for a given column
     * 
     * @param column index of column you wish to access
     * @return Matrix a matrix of the column
     */
    Matrix getColumn(int column);

    /**
     * @brief Returns a string to display the matrix information
     * 
     * @return std::string string containing matrix information
     */
    std::string display();

    /**
     * @brief Returns the value at a given row and column in the matrix
     * 
     * @param row row to access value from
     * @param column column to access value from
     * @return double value at the indices in the matrix
     */
    double access(int row, int column);

    /**
     * @brief Returns the number of rows for a given Matrix
     * 
     * @return int number of rows in the matrix
     */
    int rows();

    /**
     * @brief Returns the number of columns for a given Matrix
     * 
     * @return int number of columns in the matrix
     */
    int columns();

    /**
     * @brief Returns the filepath identifer of the Matrix
     * 
     * @return std::string containing the filepath
     */
    std::string getFilePath();

    /**
     * @brief Overload multiplication to multiply Matrix's
     * 
     * @param other matrix being multiplied
     * @return Matrix a matrix that is the result of the multiplication
     */
    Matrix operator*(Matrix &other);

    /**
     * @brief Overload multiplication to multiply Matrix by scalar value
     * 
     * @param double val scalar value to multiply by
     * @return Matrix a matrix that is the result of the multiplication
     */
    Matrix operator*(double val);

    /**
     * @brief Overload multiplication to multiply Matrix by scalar value
     * 
     * @param int val scalar value to multiply by
     * @return Matrix a matrix that is the result of the multiplication
     */
    Matrix operator*(int val);

    /**
     * @brief Overload multiplication to multiply Matrix by scalar value
     * 
     * @param float val scalar value to multiply by
     * @return Matrix a matrix that is the result of the multiplication
     */
    Matrix operator*(float val);

    /**
     * @brief Overload division to divide Matrix by scalar value
     * 
     * @param double val scalar value to multiply by
     * @return Matrix a matrix that is the result of the division
     */
    Matrix operator/(double val);

    /**
     * @brief Overload division to divide Matrix by scalar value
     * 
     * @param int val scalar value to multiply by
     * @return Matrix a matrix that is the result of the division
     */
    Matrix operator/(int val);

    /**
     * @brief Overload division to divide Matrix by scalar value
     * 
     * @param float val scalar value to multiply by
     * @return Matrix a matrix that is the result of the division
     */
    Matrix operator/(float val);

    /**
     * @brief Overload equals operator to compare Matrix contents
     * 
     * @param other matrix being compared with
     * @return true if matrix values are equal
     * @return false if matrix values are not equal
     */
    bool operator==(Matrix &other);

    /**
     * @brief Overload not equals operator to compare Matrix contents
     * 
     * @param other matrix being compared with
     * @return true if matrix values are not equal
     * @return false if matrix values are equal
     */
    bool operator!=(Matrix &other);

    /**
     * @brief Overload addition operator to add Matrices together
     * 
     * @param other matrix being added with
     * @return Matrix containing the result of addition
     */
    Matrix operator+(Matrix &other);

    /**
     * @brief Overload negation operator to get negative of Matrix
     * 
     * @return Matrix containing negative values of original
     */
    Matrix operator-();

    /**
     * @brief Overload subtraction operator to subtract Matrices
     * 
     * @param other matrix being subtracted
     * @return Matrix containing the result of subtraction
     */
    Matrix operator-(Matrix &other);

    /**
     * @brief Computes the determinant of a Matrix using by recursively
     * breaking the matrix into submatrices until they become a 1x1 or
     * a 2x2 matrix
     * 
     * @return int the determinant of the matrix
     */
    int determinant();

    /**
     * @brief Returns the inverse matrix of the current
     * 
     * @return Matrix the inverse matrix of the current
     */
    Matrix inverse();

    /**
     * @brief A function that decomposes the input Matrix into Lower and Upper Matrices
     * using Guass-Jordan Elimination
     * 
     * @param matrix NxN Matrix to decompose
     * @return std::vector<Matrix> Vector containing the Lower(index0) and Upper(index1) output matrices
     */
    std::vector<Matrix> decomposeLU();
};

#endif