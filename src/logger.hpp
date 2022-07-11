#include<string>
#include<fstream>
#ifndef LOGGER_HPP
#define LOGGER_HPP

/**
 * @brief Small class implementing the singleton pattern to streamline
 * writing log messages to files and stdout throughout application
 * 
 */
class Logger {
    private:
    /** Flag for whether logger has been initialized */
    static bool flag;

    /** Pointer to the logger */
    static Logger* logger;

    /** File to write log messages to */
    static std::ofstream file;

    /**
     * @brief Construct the logger
     * 
     */
    Logger();

    public:
    /**
     * @brief Get the instance of the logger for writing to files
     * 
     * @return Logger* pointer to the logger
     */
    static Logger* getInstance();
    
    /**
     * @brief Destroy the Logger object and sets
     * the initialized flag to flase
     * 
     */
    ~Logger();

    /**
     * @brief log a message to the log file
     * 
     * @param message message to write to the log
     */
    void log(std::string message);

    /**
     * @brief Throws an exception about invalid inverse being requested
     * 
     * @param fp filepath to the root matrix being inversed
     */
    static void logInvalidInverse(std::string fp);

    /**
     * @brief Throws an exception about an invalid determinant being requested
     * 
     * @param fp filepath to the root matrix determinant is being taken from
     */
    static void logInvalidDeterminant(std::string fp);

    /**
     * @brief Throws an exception about invalid matrix for LU decomposition
     * 
     * @param fp file path to the root matrix being decomposed
     */
    static void logInvalidLUDecomposition(std::string fp);

    /**
     * @brief Throws an exception about invalid column access
     * 
     * @param column column number that was accessed
     * @param fp filepath to the root matrix being accessed
     */
    static void logInvalidColumn(int column, std::string fp);

    /**
     * @brief Throws an exception information about an invalid row
     * 
     * @param row row number that was invalid
     * @param fp filepath to the root matrix
     */
    static void logInvalidRow(int row, std::string fp);

    /**
     * @brief Throw an error for invalid input file
     * 
     * @param fp filepath of the invalid input
     */
    static void logInvalidInput(std::string fp);

    /**
     * @brief Throw an error about invalid matrix dimensions for an operation
     * 
     * @param fp1 filepath to root of main matrix
     * @param m1 main matrix row count
     * @param n1 main matrix column count
     * @param fp2 filepath to root of secondary matrix
     * @param m2 secondary matrix row count
     * @param n2 secondary matrix column count
     */
    static void logInvalidDimensions(std::string fp1, int m1, int n1, std::string fp2, int m2, int n2);

};

#endif