#include<string>
#include<fstream>
#include<iostream>
#include"logger.hpp"

// Reference to logger flag
bool Logger::flag;

// Reference to logger pointer
Logger* Logger::logger;

// Reference to file to write log to
std::ofstream Logger::file;

Logger::Logger(){
    // Open the log file
    file.open("log/debug.log", std::ofstream::app);
    // Output a line to show a new log has been initialized
    file << "===================================\n";
}

Logger* Logger::getInstance() {
    // If the logger has been initialized return it
    if(flag) return logger;
    // Otherwise initialize and return its pointer
    else {
        logger = new Logger();
        flag = true;
        return logger;
    }
}

Logger::~Logger(){
    flag = false;
}

void Logger::log(std::string message) {
    // Output the error message to the log file
    file << message << std::endl;
}

void Logger::logInvalidInverse(std::string fp) {
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

void Logger::logInvalidDeterminant(std::string fp) {
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

void Logger::logInvalidLUDecomposition(std::string fp){
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

void Logger::logInvalidColumn(int column, std::string fp){
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

void Logger::logInvalidRow(int row, std::string fp){
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

void Logger::logInvalidInput(std::string fp){
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

void Logger::logInvalidDimensions(std::string fp1, int m1, int n1, std::string fp2, int m2, int n2) {
    // Log error with dimensions and identifiers
    std::string errorMessage = "";
    errorMessage.append("Invalid dimensions were provided for operation on Matrices: ");
    errorMessage.append(fp1);
    errorMessage.append(" and ");
    errorMessage.append(fp2);
    errorMessage.append("\n");
    errorMessage.append(fp1);
    errorMessage.append(": ");
    errorMessage.append(std::to_string(m1));
    errorMessage.append("x");
    errorMessage.append(std::to_string(n1));
    errorMessage.append("\n");
    errorMessage.append(fp2);
    errorMessage.append(": ");
    errorMessage.append(std::to_string(m2));
    errorMessage.append("x");
    errorMessage.append(std::to_string(n2));
    errorMessage.append("\n");
    errorMessage.append("A reminder for multiplying Matrices:\n");
    errorMessage.append("The columns of the first matrix must equal the rows of the second.\n");
    errorMessage.append("Their result will be another matrix with the row count of the first and the column count of the second.\n");
    // Throw error with log message
    throw std::runtime_error(errorMessage);
}