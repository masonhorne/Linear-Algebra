#include<string>
#include<vector>
#include"util.hpp"
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
    std::vector<std::vector<int>> matrix;

    /**
     * @brief A function for logging errors with input
     * 
     */
    void exitInvalidInput();

    /**
     * @brief A function for logging errors with dimensions
     * 
     * @param other other matrix being used in operation
     */
    void exitInvalidDimensions(Matrix &other);

    /**
     * @brief A function for logging errors with requested columns
     * 
     * @param column column that was requested
     */
    void exitInvalidColumn(int column);

    /**
     * @brief A function for logging errors with requested rows
     * 
     * @param row row that was requested
     */
    void exitInvalidRow(int row);

    /**
     * @brief A function to read header info from an mtx file
     * 
     * @param line line of input to parse
     */
    void readHeader(std::string line);

    /**
     * @brief A function to read a matrix row from an mtx file
     * 
     * @param line line of matrix values to parse
     */
    void readRow(std::string line);

    /**
     * @brief Populates the array from its input file
     * 
     */
    void readInput();

    /**
     * @brief Special constructor for building a matrix from a given
     * grid of input values
     * 
     * @param filepath filepath identifer for the matrix
     * @param vals grid of values to populate matrix with
     */
    Matrix(std::string filepath, std::vector<std::vector<int>> vals);

    public:
    /**
     * @brief Constructs a matrix from an input file
     * 
     * @param filepath 
     */
    Matrix(std::string filepath);


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
     * @return int value at indices in matrix
     */
    int access(int row, int column);

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
     * NOTE: Result will inherit the initial Matrix's filepath
     * 
     * @param other 
     * @return Matrix 
     */
    Matrix operator*(Matrix &other);
};

#endif