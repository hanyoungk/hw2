#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;


//constructor
Movie::Movie(const std::string category, const std::string name, double price, 
        int qty, std::string genre, std::string rating) : Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}

//destructor
Movie::~Movie()
{

}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Movie::keywords() const
{
    set<string> s1 = parseStringToWords(name_);
    set<string> s2 = parseStringToWords(genre_);

    set<string>::iterator it1;
    for(it1 = s2.begin(); it1 != s2.end(); ++it1)
    {
        s1.insert(*it1);
    }

    return s1;
}


/**
 * Returns a string to display the product info for hits of the search
 */
std::string Movie::displayString() const
{

    stringstream ss1;

    ss1 << fixed << setprecision(2) << price_;

    string str = name_ + "\n";
    str += "Genre: " + genre_ + " " + "Rating: " + rating_ + "\n";
    str += ss1.str() + " " + to_string(qty_) + " left." + "\n";
    
    return str;
}


/**
 * Outputs the product info in the database format
 */
void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ 
        << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}


//accessors and mutators
std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}