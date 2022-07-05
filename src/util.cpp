#include"util.hpp"
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;


bool endsWith(string word, string suffix) {
    // Check that the word is long enough for the suffix
    if(word.size() < suffix.size()) return false;
    // Get the offset for suffix in the word
    int idx = word.size() - suffix.size();
    // Iterate through looking for mismatches
    for(int i = idx; i < word.size(); i++)
        if(word[i] != suffix[i - idx]) return false;
    // If all matched return true
    return true;
}

std::string formatDouble(double value, int width) {
    std::ostringstream oss;
    oss << std::setfill(' ') << std::setw(width) << value;
    return oss.str();
}