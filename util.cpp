#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    std::set<std::string> result;
    string str = "";
    // rawWords = convToLower(rawWords); //convert to lowercase

    // stringstream ss(rawWords);

    for(size_t i = 0; i < rawWords.length(); i++) {
        if(ispunct(rawWords[i])) { //if not punctuation
            rawWords[i] = ' '; //change the punct to space for ss
        }
    }

    rawWords = convToLower(rawWords); //convert to lowercase
    stringstream ss1(rawWords);

    while(ss1 >> str) {
        if(str.length() > 1) {
            str = convToLower(str);
            result.insert(str);
        }
    }

    // for(size_t i = 0; rawWords.length(); ++i) { //for the entire input string
    //     if(!ispunct(rawWords[i])) { //if char is not punctuation, 
    //         str = rawWords[i]; //add the char to string str
    //     }
    //     if(str.length() >= 2) { //check if at least 2 characters long
    //         result.insert(str); //insert the string str in result set
    //         // str = ""; //empty the str
    //     }
    //     // else {
    //     //     str = ""; //empty the str
    //     // }
    // }

    // if(!str.empty()) { //make sure nothing is left behind
    //     result.insert(str);
    // }

    return result;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
