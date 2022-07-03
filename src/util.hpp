#include<string>

#ifndef UTIL_HPP
#define UTIL_HPP

/**
 * @breif Returns if the word ends with the given suffix
 * 
 * @param word word being inspected for the suffix
 * @param suffix suffix being looked for
 * @return true if the word contained the suffix
 * @return false if the word didn't contain the suffix
 */
bool endsWith(std::string word, std::string suffix);

/**
 * @brief Formats an integer value into a string of given width
 * 
 * @param value value to format
 * @param width width to format value to
 * @return std::string 
 */
std::string formatInteger(int value, int width);

#endif