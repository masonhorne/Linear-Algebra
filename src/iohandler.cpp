#include"iohandler.hpp"

void readHeader(std::string line, std::string fp, int &m, int &n) {
    // Set to initially read m
    bool first = true;
    // Initialize m and n to 0
    m = 0;
    n = 0;
    // Loop through input string
    for(int i = 0; i < line.size(); i++){
        // If character is invalid exit
        if(line[i] < '0' || line[i] > ':') Logger::logInvalidInput(fp);
        // Otherwise if not the delimiter build up value
        if(line[i] != ':'){
            int *val = first ? &m : &n;
            *val = *val * 10 + line[i] - '0';
        // Otherwise confirm swapping to column
        } else if(!first) Logger::logInvalidInput(fp);
        // Swap to read in column count
         else first = false;
    }
}

void readRow(std::string line, std::vector<std::vector<double>> &matrix, std::string fp, int n){
    // Row to add to the matrix
    std::vector<double> row;
    // Build value and keep up with its sign and floating point values
    float val = 0;
    int negative = 1;
    float dec = 1;
    // Parse the line character by character
    for(int i = 0; i < line.size(); i++){
        // If character is invalid exit
        if((line[i] < '0' || line[i] > ':') && line[i] != '-' && line[i] != '.') Logger::logInvalidInput(fp);
        // If end of an input, add to row
        if(line[i] == ':') {
            row.push_back(val * negative);
            val = 0;
            negative = 1;
            dec = 1;
        // If start of an input and negative, mark negative
        } else if(val == 0 && line[i] == '-') {
            // If already marked negative input is invalid
            if(negative < 0) Logger::logInvalidInput(fp);
            // Otherwise swap to negative
            negative = -negative;
        // If the spot marks a decimal point
        } else if(line[i] == '.') {
            if(dec != 1) Logger::logInvalidInput(fp);
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
    if(row.size() != n) Logger::logInvalidInput(fp);
    // Add the row to the matrix
    matrix.push_back(row);
}

void readMtx(std::string filepath, int &m, int &n, std::vector<std::vector<double>> &matrix) {
    // Check for the proper file type
    if(!endsWith(filepath, ".mtx")) Logger::logInvalidInput(filepath);
    // Open file and create string and index values
    std::ifstream file(filepath);
    std::string line;
    int idx = 0;
    // Read input until the end
    while(std::getline(file, line)){
        if(idx == 0) readHeader(line, filepath, m, n);
        else readRow(line, matrix, filepath, n);
        idx++;
    }
    // If m row didn't exist invalid input
    if(idx - 1 != m) Logger::logInvalidInput(filepath);
}

void writeMtx(std::string filepath, std::vector<std::vector<double>> &matrix){
    // Get the dimensions of the matrix provided
    int m = matrix.size();
    int n = matrix[0].size();
    // Open the file to write to
    std::ofstream file(filepath + ".mtx");
    // Output the row and column dimensions
    file << m << ":" << n;
    // Loop through and output values
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++)
            // If first in row, newline previous row and output first value
            if(j == 0) file << "\n" << matrix[i][j];
            // Otherwise just output the separator and the value
            else file << ":" << matrix[i][j];
    }
    // Close the file pointer
    file.close();
}