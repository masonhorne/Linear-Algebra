#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"matrix.hpp"

//////////////////////////////////////////
//  Importing/Exporting Matrix objects
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
    // Log the creation of the Matrix with its filepath identifier
    Logger::getInstance()->log("Creating a Matrix from the filepath: " + filepath);
    // Store the matrix's filepath
    fp = filepath;
    // Populate the matrix from input file
    readMtx(fp, m, n, matrix);
}

void Matrix::save(std::string filename) {
    // Write the matrix to the provided filepath
    writeMtx(filename, matrix);
}

//////////////////////////////////////////
//  Accessors for Matrix objects
//////////////////////////////////////////

Matrix Matrix::getRow(int row) {
    // Check bounds on the requested row
    if(row < 1 || row > m) Logger::logInvalidRow(row, fp);
    // Return the row matrix
    return Matrix(fp, { matrix[row - 1] });
}

Matrix Matrix::getColumn(int column) {
    // Check bounds on the requested column
    if(column < 1 || column > n) Logger::logInvalidColumn(column, fp);
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
    if(row < 1 || row > m) Logger::logInvalidRow(row, fp);
    if(column < 1 || column > n) Logger::logInvalidColumn(column, fp);
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
    if(n != other.rows()) Logger::logInvalidDimensions(fp, m, n, other.getFilePath(), other.rows(), other.columns());
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
    if(m != other.rows() || n != other.columns()) Logger::logInvalidDimensions(fp, m, n, other.getFilePath(), other.rows(), other.columns());
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
    if(m != other.rows() || n != other.columns()) Logger::logInvalidDimensions(fp, m, n, other.getFilePath(), other.rows(), other.columns());
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
    if(m != n) Logger::logInvalidDeterminant(fp);
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
        Logger::logInvalidInverse(fp);
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
    if(m != n) Logger::logInvalidLUDecomposition(fp);
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
                if(base % edit != 0) Logger::logInvalidLUDecomposition(fp);
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
                    if(row == uCol && U[row][uCol] == 0) Logger::logInvalidLUDecomposition(fp);
                }
            }
        }
    }
    // Once done return the resulting Matrices
    return {Matrix(fp, L), Matrix(fp, U)};
}