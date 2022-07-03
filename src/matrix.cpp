#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<format>
#include"util.h"
#include"matrix.hpp"

//////////////////////////////////////////
//  Functions for logging errors
//////////////////////////////////////////

void Matrix::exitInvalidColumn(int column){
    // Log error with identifier and column number
    std::cout << "Invalid column requested: " + fp + "\n";
    std::cout << "The request column number was " + std::to_string(column) + ",\n";
    std::cout << "Remember that matrices are 1-indexed.\n";
    // Exit program
    exit(1);
}

void Matrix::exitInvalidRow(int row){
    // Log error with identifier and row number
    std::cout << "Invalid row requested: " + fp + "\n";
    std::cout << "The request row number was " + std::to_string(row) + ",\n";
    std::cout << "Remember that matrices are 1-indexed.\n";
    // Exit program
    exit(1);
}

void Matrix::exitInvalidInput(){
    // Log error with identifier and formatting hints
    std::cout << "Invalid input was provided in the file: " + fp + "\n";
    std::cout << "================================\n";
    std::cout << "Please confirm that the file is in .mtx format.\n";
    std::cout << "\t1) First row of file contains the row and column counts for the matrix.\n";
    std::cout << "\t   Formatted: <row>:<column>\n";
    std::cout << "\t2) A total of <row> lines of input each with <column> integer values.\n";
    std::cout << "\t   Formatted: <value>:<value:...:<value\n";
    std::cout << "\t3) The file name ends with .mtx\n";
    std::cout << "\t4) The file exists in the working directory.\n";
    // Exit program
    exit(1);
}

void Matrix::exitInvalidDimensions(Matrix &other) {
    // Log error with dimensions and identifiers
    std::cout << "Invalid dimensions were provided for operation on Matrices: " + fp + " and " + other.getFilePath() + "\n";
    std::cout << fp + ": " + std::to_string(m) + "x" + std::to_string(n) + "\n";
    std::cout << other.getFilePath() + ": " + std::to_string(other.rows()) + "x" + std::to_string(other.columns()) + "]\n";
    std::cout << "A reminder for multiplying Matrices:\n";
    std::cout << "The columns of the first matrix must equal the rows of the second.\n";
    std::cout << "Their result will be another matrix with the row count of the first and the column count of the second.\n";
    // Exit program
    exit(1);
}


//////////////////////////////////////////
//  Functions for reading input files
//////////////////////////////////////////

void Matrix::readHeader(std::string line) {
    // Set to initially read m
    bool first = true;
    // Initialize m and n to 0
    m = 0;
    n = 0;
    // Loop through input string
    for(int i = 0; i < line.size(); i++){
        // If character is invalid exit
        if(line[i] < '0' || line[i] > ':') exitInvalidInput();
        // Otherwise if not the delimiter build up value
        if(line[i] != ':'){
            int *val = first ? &m : &n;
            *val = *val * 10 + line[i] - '0';
        // Otherwise confirm swapping to column
        } else if(!first) exitInvalidInput();
        // Swap to read in column count
         else first = false;
    }
}

void Matrix::readRow(std::string line){
    // Row to add to the matrix
    std::vector<int> row;
    int val = 0;
    for(int i = 0; i < line.size(); i++){
        // If character is invalid exit
        if(line[i] < '0' || line[i] > ':') exitInvalidInput();
        if(line[i] == ':') {
            row.push_back(val);
            val = 0;
        } else val = val * 10 + line[i] - '0';
    }
    // Add the final value to the row
    row.push_back(val);
    if(row.size() != n) exitInvalidInput();
    matrix.push_back(row);
}

void Matrix::readInput() {
    // Check for the proper file type
    if(!endsWith(fp, ".mtx")) exitInvalidInput();
    // Open file and create string and index values
    std::ifstream file(fp);
    std::string line;
    int idx = 0;
    // Read input until the end
    while(std::getline(file, line)){
        if(idx == 0) readHeader(line);
        else readRow(line);
        idx++;
    }
    // If m row didn't exist invalid input
    if(idx - 1 != m) exitInvalidInput();
}

//////////////////////////////////////////
//  Constructors for Matrix objects
//////////////////////////////////////////

Matrix::Matrix(std::string filepath, std::vector<std::vector<int>> vals) {
    // Store the matrix's filepath
    fp = filepath;
    // Store the dimensions of the matrix
    m = vals.size();
    n = vals[0].size();
    // Read in the values for the matrix
    for(int i = 0; i < m; i++) matrix.push_back(vals[i]);
}

Matrix::Matrix(std::string filepath){
    // Store the matrix's filepath
    fp = filepath;
    // Populate the matrix from input file
    readInput();
}

//////////////////////////////////////////
//  Accessors for Matrix objects
//////////////////////////////////////////

Matrix Matrix::getRow(int row) {
    // Check bounds on the requested row
    if(row < 1 || row > m) exitInvalidRow(row);
    // Return the row matrix
    return Matrix(fp, { matrix[row - 1] });
}

Matrix Matrix::getColumn(int column) {
    // Check bounds on the requested column
    if(column < 1 || column > n) exitInvalidColumn(column);
    // Initialize value vector to pass in
    std::vector<std::vector<int>> vals(m, std::vector<int>(0));
    // Read through columns pushing to rows
    for(int i = 0; i < m; i++) vals[i].push_back(matrix[i][column - 1]);
    // Return the column matrix
    return Matrix(fp, vals);
}

std::string Matrix::display() {
    // Display matrix identifier and dimensions
    std::string result;
    result += std::string("================================\n");
    result += std::string("Displaying Matrix: ") + fp + std::string("\n");
    result += std::string("[ ") + std::to_string(m) + std::string(" ] rows.\n");
    result += std::string("[ ") + std::to_string(n) + std::string(" ] columns.\n");
    result += std::string("================================\n");
    // Loop through values and output
    int valueWidth = 3;
    for(int i = 0; i < m; i++) {
        result += formatInteger(matrix[i][0], valueWidth);
        for(int j = 1; j < n; j++) result += formatInteger(matrix[i][j], valueWidth);
        result += "\n";
    }
    result += std::string("================================\n");
    return result;
}

int Matrix::access(int row, int column){
    // Check the bounds of the row and column
    if(row < 1 || row > m) exitInvalidRow(row);
    if(column < 1 || column > n) exitInvalidColumn(column);
    // Return the value at the provided indices
    return matrix[row - 1][column - 1];
}

int Matrix::rows() {
    // Return the number of rows for the matrix
    return m;
}

int Matrix::columns() {
    // Return the number of columns for the matrix
    return n;
}

std::string Matrix::getFilePath() {
    // Returns the file path for the matrix
    return fp;
}

//////////////////////////////////////////
//  Operators for Matrix objects
//////////////////////////////////////////

Matrix Matrix::operator*(Matrix &other){
    // If dimensions don't match display error message
    if(n != other.columns()) exitInvalidDimensions(other);
    // Initialize values grid for new matrix
    std::vector<std::vector<int>> vals(m, std::vector<int>(other.columns()));
    // Loop through all indices in output grid
    for(int i = 0; i < m; i++)
        for(int j = 0; j < other.columns(); j++)
            // For each index total the row x column values
            for(int ii = 0; ii < n; ii++)
                    vals[i][j] += matrix[i][ii] * other.access(ii + 1, j + 1);
    // Return the new resulting Matrix
    return Matrix(fp, vals);
}