#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> final;
    typename std::set<T>::iterator it;

    for(it = s1.begin(); it != s1.end(); ++it) {
        //if s1 thing is in s2
        if(s2.find(*it) != s2.end()) { 
            final.insert(*it);
        }
    }

    return final;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    std::set<T> final;

    typename std::set<T>::iterator it1; //iterator for set 1
    typename std::set<T>::iterator it2; //iterator for set 2

    for(it1 = s1.begin(); it1 != s1.end(); ++it1) {
        final.insert(*it1);
        // std::cout << final[*it1]->keywords() << std::endl;
    }
    for(it2 = s2.begin(); it2 != s2.end(); ++it2) {
        //only insert s2 if it wasn't already inserted
        if(final.find(*it2) == final.end()) {
            final.insert(*it2);
        }
        // final.insert(*it2);
        // std::cout << final[*it2]->keywords() << std::endl;
    }

    return final;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
