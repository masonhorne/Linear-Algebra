#include<string>
#include<vector>
#include"logger.hpp"
#include"util.hpp"
#ifndef IOHANDLER_HPP
#define IOHANDLER_HPP

/**
 * @brief A function to read header info from an mtx file
 * 
 * @param line line of input to parse
 * @return the matrix with the appropriate dimensions from input
 */
void readHeader(std::string line, std::string filepath, int &m, int &n);

/**
 * @brief A function to read a matrix row from an mtx file
 * and adds to the matrix provided
 * 
 * @param line line of matrix values to parse
 * @param matrix matrix that we are adding row to
 */
void readRow(std::string line, std::vector<std::vector<double>> &matrix, std::string filepath);

/**
 * @brief Populates the provided references with information from
 * the provided filepath
 * 
 * @param filepath filepath to mtx file
 * @param m reference to class row count
 * @param n reference to class column count
 * @param matrix reference to class matrix
 */
void readMtx(std::string filepath, int &m, int &n, std::vector<std::vector<double>> &matrix);

/**
 * @brief Writes a provided matrix to the provided filepath
 * 
 * @param filepath filepath to write matrix to
 * @param matrix matrix to write to file
 */
void writeMtx(std::string filepath, std::vector<std::vector<double>> &matrix);

#endif