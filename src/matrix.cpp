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

void logInvalidInverse(std::string fp) {
    // Log error with identifier and column number
    std::string errorMessage = "";
    errorMessage.append("Unable to calculate Inverse of: ");
    errorMessage.append(fp);
    errorMessage.append("\n");
    errorMessage.append("================================\n");
    errorMessage.append("Requirements of Inverse calculation: \n");
    errorMessage.append("\t1) Matrix being operated on is NxN.\n");
    errorMessage.append("\t2) Matrix must be able to calculate its values via Cramers Rule.\n");
    errorMessage.append("\t   NOTE: This may prevent the calculation of some inverses.\n");
    // Throw error with log message
    throw std::runtime_error(errorMessage);
}

void logInvalidDeterminant(std::string fp) {
    // Log error with identifier and column number
    std::string errorMessage = "";
    errorMessage.append("Unable to calculate Determinant of: ");
    errorMessage.append(fp);
    errorMessage.append("\n");
    errorMessage.append("================================\n");
    errorMessage.append("Matrix must be in the form of NxN.\n");
    // Throw error with log message
    throw std::runtime_error(errorMessage);
}

void logInvalidLUDecomposition(std::string fp){
    // Log error with identifier and column number
    std::string errorMessage = "";
    errorMessage.append("Unable to complete LU Decomposition of: ");
    errorMessage.append(fp);
    errorMessage.append("\n");
    errorMessage.append("================================\n");
    errorMessage.append("Requirements of LU Decomposition: \n");
    errorMessage.append("\t1) Matrix being decomposed is NxN.\n");
    errorMessage.append("\t2) Matrix must be able to factorize into components L and U.\n");
    errorMessage.append("\t   NOTE: For the requirements of factorizing look into Gussian Elimination.\n");
    // Throw error with log message
    throw std::runtime_error(errorMessage);
}

void logInvalidColumn(int column, std::string fp){
    // Log error with identifier and column number
    std::string errorMessage = "";
    errorMessage.append("Invalid column requested: ");
    errorMessage.append(fp);
    errorMessage.append("\n");
    errorMessage.append("The request column number was ");
    errorMessage.append(std::to_string(column));
    errorMessage.append(".\n");
    errorMessage.append("Remember that matrices are 1-indexed.\n");
    // Throw error with log message
    throw std::runtime_error(errorMessage);
}

void logInvalidRow(int row, std::string fp){
    // Log error with identifier and row number
    std::string errorMessage = "";
    errorMessage.append("Invalid row requested: ");
    errorMessage.append(fp);
    errorMessage.append("\n");
    errorMessage.append("The request row number was ");
    errorMessage.append(std::to_string(row));
    errorMessage.append(".\n");
    errorMessage.append("Remember that matrices are 1-indexed.\n");
    // Throw error with log message
    throw std::runtime_error(errorMessage);
}

void logInvalidInput(std::string fp){
    // Log error with identifier and formatting hints
    std::string errorMessage = "";
    errorMessage.append("Invalid input was provided in the file: ");
    errorMessage.append(fp);
    errorMessage.append("\n");
    errorMessage.append("================================\n");
    errorMessage.append("Please confirm that the file is in .mtx format.\n");
    errorMessage.append("\t1) First row of file contains the row and column counts for the matrix.\n");
    errorMessage.append("\t   Formatted: <row>:<column>\n");
    errorMessage.append("\t2) A total of <row> lines of input each with <column> integer values.\n");
    errorMessage.append("\t   Formatted: <value>:<value:...:<value\n");
    errorMessage.append("\t3) The file name ends with .mtx\n");
    errorMessage.append("\t4) The file exists in the working directory.\n");
    // Throw error with log message
    throw std::runtime_error(errorMessage);
}

void logInvalidDimensions(Matrix &other, std::string fp, int m, int n) {
    // Log error with dimensions and identifiers
    std::string errorMessage = "";
    errorMessage.append("Invalid dimensions were provided for operation on Matrices: ");
    errorMessage.append(fp);
    errorMessage.append(" and ");
    errorMessage.append(other.getFilePath());
    errorMessage.append("\n");
    errorMessage.append(fp);
    errorMessage.append(": ");
    errorMessage.append(std::to_string(m));
    errorMessage.append("x");
    errorMessage.append(std::to_string(n));
    errorMessage.append("\n");
    errorMessage.append(other.getFilePath());
    errorMessage.append(": ");
    errorMessage.append(std::to_string(other.rows()));
    errorMessage.append("x");
    errorMessage.append(std::to_string(other.columns()));
    errorMessage.append("\n");
    errorMessage.append("A reminder for multiplying Matrices:\n");
    errorMessage.append("The columns of the first matrix must equal the rows of the second.\n");
    errorMessage.append("Their result will be another matrix with the row count of the first and the column count of the second.\n");
    // Throw error with log message
    throw std::runtime_error(errorMessage);
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
        if(line[i] < '0' || line[i] > ':') logInvalidInput(fp);
        // Otherwise if not the delimiter build up value
        if(line[i] != ':'){
            int *val = first ? &m : &n;
            *val = *val * 10 + line[i] - '0';
        // Otherwise confirm swapping to column
        } else if(!first) logInvalidInput(fp);
        // Swap to read in column count
         else first = false;
    }
}

void Matrix::readRow(std::string line){
    // Row to add to the matrix
    std::vector<double> row;
    // Build value and keep up with its sign and floating point values
    float val = 0;
    int negative = 1;
    float dec = 1;
    // Parse the line character by character
    for(int i = 0; i < line.size(); i++){
        // If character is invalid exit
        if((line[i] < '0' || line[i] > ':') && line[i] != '-' && line[i] != '.') logInvalidInput(fp);
        // If end of an input, add to row
        if(line[i] == ':') {
            row.push_back(val * negative);
            val = 0;
            negative = 1;
            dec = 1;
        // If start of an input and negative, mark negative
        } else if(val == 0 && line[i] == '-') {
            // If already marked negative input is invalid
            if(negative < 0) logInvalidInput(fp);
            // Otherwise swap to negative
            negative = -negative;
        // If the spot marks a decimal point
        } else if(line[i] == '.') {
            if(dec != 1) logInvalidInput(fp);
            dec = 0.1;
        // Otherwise add value to total
        } else {
            // If decimal just add to correct place
            if(dec != 1){
                val += (line[i] - '0') * dec;
                dec /= 10;
            // Otherwise add like normal
            } else val = val * 10 + (line[i] - '0') * dec;
        }
    }
    // Add the final value to the row
    row.push_back(val * negative);
    // Log an error if not enough columns were given
    if(row.size() != n) logInvalidInput(fp);
    // Add the row to the matrix
    matrix.push_back(row);
}

void Matrix::readInput() {
    // Check for the proper file type
    if(!endsWith(fp, ".mtx")) logInvalidInput(fp);
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
    if(idx - 1 != m) logInvalidInput(fp);
}

//////////////////////////////////////////
//  Constructors for Matrix objects
//////////////////////////////////////////

Matrix::Matrix(std::string filepath, std::vector<std::vector<double>> vals) {
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
    if(row < 1 || row > m) logInvalidRow(row, fp);
    // Return the row matrix
    return Matrix(fp, { matrix[row - 1] });
}

Matrix Matrix::getColumn(int column) {
    // Check bounds on the requested column
    if(column < 1 || column > n) logInvalidColumn(column, fp);
    // Initialize value vector to pass in
    std::vector<std::vector<double>> vals(m, std::vector<double>(0));
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
    int valueWidth = 5;
    for(int i = 0; i < m; i++) {
        result += formatDouble(matrix[i][0], valueWidth);
        for(int j = 1; j < n; j++) result += formatDouble(matrix[i][j], valueWidth);
        result += "\n";
    }
    result += std::string("================================\n");
    return result;
}

double Matrix::access(int row, int column){
    // Check the bounds of the row and column
    if(row < 1 || row > m) logInvalidRow(row, fp);
    if(column < 1 || column > n) logInvalidColumn(column, fp);
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
    if(n != other.rows()) logInvalidDimensions(other, fp, m, n);
    // Initialize values grid for new matrix
    std::vector<std::vector<double>> vals(m, std::vector<double>(other.columns()));
    // Loop through all indices in output grid
    for(int i = 0; i < m; i++)
        for(int j = 0; j < other.columns(); j++)
            // For each index total the row x column values
            for(int ii = 0; ii < n; ii++)
                    vals[i][j] += matrix[i][ii] * other.access(ii + 1, j + 1);
    // Return the new resulting Matrix
    return Matrix(fp, vals);
}

Matrix Matrix::operator*(double val) {
    // Initialize array to hold resulting values
    std::vector<std::vector<double>> vals(m, std::vector<double>(n));
    // Loop through scaling values
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            vals[i][j] = matrix[i][j] * val;
    // Return the resulting matrix
    return Matrix(fp, vals);
}

Matrix Matrix::operator*(int val) {
    // Return the result of the multiplication
    return *this * ((double) val);
}

Matrix Matrix::operator*(float val) {
    // Return the result of the multiplication
    return *this * ((double) val);
}

Matrix Matrix::operator/(double val) {
    // Initialize array to hold resulting values
    std::vector<std::vector<double>> vals(m, std::vector<double>(n));
    // Loop through scaling values
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            vals[i][j] = matrix[i][j] / val;
    // Return the resulting matrix
    return Matrix(fp, vals);
}

Matrix Matrix::operator/(int val) {
    // Return the result of the division
    return *this / ((double) val);
}


Matrix Matrix::operator/(float val){
    // Return the result of the division
    return *this / ((double) val);
}

bool Matrix::operator==(Matrix &other){
    // If the dimensions don't match return false
    if(m != other.rows() || n != other.columns()) return false;
    // Otherwise iterate through and if mismatch occurs return false
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            if(matrix[i][j] != other.access(i + 1, j + 1)) return false;
    // If all were equal return true
    return true;
}

bool Matrix::operator!=(Matrix &other){
    // Return the opposite of equal
    return !(*this == other);
}

Matrix Matrix::operator+(Matrix &other) {
    // If dimensions don't match display error message
    if(m != other.rows() || n != other.columns()) logInvalidDimensions(other, fp, m, n);
    // Initialize values grid for new matrix
    std::vector<std::vector<double>> vals(m, std::vector<double>(n));
    // Loop through all indices in output grid
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            // Each index is the sum of the two in the input
            vals[i][j] = matrix[i][j] + other.access(i + 1, j + 1);
    // Return the resulting matrix
    return Matrix(fp, vals);
}

Matrix Matrix::operator-() {
    // Initialize values grid for new matrix
    std::vector<std::vector<double>> vals(m, std::vector<double>(n));
    // Loop through all indices in output grid
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            // Each index is the negative of its value in matrix
            vals[i][j] = -matrix[i][j];
    // Return the resulting matrix
    return Matrix(fp, vals);
}

Matrix Matrix::operator-(Matrix &other) {
    // If dimensions don't match display error message
    if(m != other.rows() || n != other.columns()) logInvalidDimensions(other, fp, m, n);
    // Initialize values grid for new matrix
    std::vector<std::vector<double>> vals(m, std::vector<double>(n));
    // Loop through all indices in output grid
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            // Each index is the subtraction of the two in the input
            vals[i][j] = matrix[i][j] - other.access(i + 1, j + 1);
    // Return the resulting matrix
    return Matrix(fp, vals);
}

//////////////////////////////////////////
//  Functions for Matrix objects
//////////////////////////////////////////

double determinantHelper(std::vector<std::vector<double>> matrix, int n){
    // Initialize result to 0 and subMatrix of NxN dimensions
    int result = 0;
    std::vector<std::vector<double>> subMat(n, std::vector<double>(n));
    // Handle the trivial cases of N = 1 or 2
    if(n == 1) return matrix[0][0];
    if(n == 2) return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    // Loop through each index in list
    for(int idx = 0; idx < n; idx++){
        // Use x to keep up with pointer into sub matrix
        int x = 0;
        // Loop through rows in matrix
        for(int i = 1; i < n; i++){
            // Use y to keep pointer into sub matrix
            int y = 0;
            // Loop through columns in matrix
            for(int j = 0; j < n; j++){
                // If this is the submatrix being calculated, skip it
                if(j == idx) continue;
                // Store value in submatrix
                subMat[x][y] = matrix[i][j];
                // Progress y pointer
                y++;
            }
            // Progress x pointer
            x++;
        }
        // The sign for the component is based on whether x pointer is odd or even
        int sign = idx % 2 == 0 ? 1 : -1;
        // Add component to result, recursing to solve for the submatrix's determinant
        result = result + (sign * matrix[0][idx] * determinantHelper(subMat, n - 1));
    }
    // Return the resulting determinant
    return result;
}

int Matrix::determinant(){
    // Check if dimensions are invalid and log if so
    if(m != n) logInvalidDeterminant(fp);
    // Otherwise use recursive helper to calculate determinant
    return determinantHelper(matrix, m);
}

Matrix Matrix::inverse() {
    // Calculate the denominator for the resulting matrix
    float denominator;
    try {
        // The denominator is the total matrix determinant
        denominator = this->determinant();
    } catch (std::runtime_error error) {
        // If error occurs log issue
        logInvalidInverse(fp);
    }
    // Create a workspace matrix to calculate values from
    std::vector<std::vector<double>> vals(this->rows(), std::vector<double>(this->columns(), 0));
    for(int i = 0; i < m; i++)
        for(int j = 0; j < n; j++)
            vals[i][j] = matrix[i][j];
    // Create an output matrix to store values in
    std::vector<std::vector<double>> result(this->rows(), std::vector<double>(this->columns(), 0));
    // Loop through computing each columns values
    for(int col = 0; col < this->columns(); col++){
        // Set this columns values to 0
        for(int row = 0; row < this->rows(); row++) vals[row][col] = 0;
        // Loop through finding numerator
        for(int row = 0; row < this->rows(); row++){
            // Mark position we are calculating
            vals[row][col] = 1;
            // Calculate numerator and store result
            int numerator = Matrix(fp, vals).determinant();
            result[col][row] = numerator / denominator;
            // Unmark our position to move on
            vals[row][col] = 0;
        }
        // Once done bring back original matrix values
        for(int row = 0; row < this->rows(); row++) vals[row][col] = matrix[row][col];
    }
    // Return the resulting matrix
    return Matrix(fp, result);
}

//////////////////////////////////////////
//  Decompositions for Matrix Objects
//////////////////////////////////////////

std::vector<Matrix> Matrix::decomposeLU(){
    if(m != n) logInvalidLUDecomposition(fp);
    // Initialize the result vector L and U for decomposing the Matrix into
    std::vector<std::vector<double>> L(m, std::vector<double>(n));
    std::vector<std::vector<double>> U(m, std::vector<double>(n));
    // Initialize L's diagonal and U's first row
    for(int i = 0; i < m; i++) {
        L[i][i] = 1;
        U[0][i] = matrix[0][i];
    }
    // Loop through each column solving for its coefficients
    for(int col = 0; col < n; col++){
        // Process one row at a time for this column
        for(int row = 1; row < m; row++) {
            // Only solve for coefficients below the diagonal
            if(row > col){
                // The base value is from matrix if first iteration
                // otherwise it is from updated previous coefficients
                int base = col == 0 ? matrix[row][col] : U[row][col];
                // The value to modify by is row == col
                int edit = U[col][col];
                // If not evenly divisible no LU Decomposition exists
                if(base % edit != 0) logInvalidLUDecomposition(fp);
                // The value to update by is the base divided by edit
                int change = base / edit;
                // This value is a coefficient is Lower Matrix
                L[row][col] = change;
                // Loop through this row of Upper updating the other values
                for(int uCol = col; uCol < n; uCol++){
                    // The value in Upper is the current value minus the change and the updating value
                    // NOTE: The current value is dependent upon whether it is the first column
                    U[row][uCol] = (col == 0 ? matrix[row][uCol] : U[row][uCol]) - (change * U[col][uCol]);
                    // If a diagonal in Upper becomes 0, their isn't a valid factorization of the matrix
                    if(row == uCol && U[row][uCol] == 0) logInvalidLUDecomposition(fp);
                }
            }
        }
    }
    // Once done return the resulting Matrices
    return {Matrix(fp, L), Matrix(fp, U)};
}