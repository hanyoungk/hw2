#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

//constructor
Book::Book(const std::string category, const std::string name, double price, 
        int qty, std::string author, std::string isbn) : Product(category, name, price, qty)
{
    //need to make name, author, and isbn into keywords
    author_ = author;
    isbn_ = isbn;
}

//destructor
Book::~Book() 
{

}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Book::keywords() const 
{
    set<string> s1 = parseStringToWords(name_);
    set<string> s2 = parseStringToWords(author_);

    set<string>::iterator it1;
    for(it1 = s2.begin(); it1 != s2.end(); ++it1)
    {
        s1.insert(*it1);
    }
    s1.insert(isbn_);

    return s1;
}


/**
 * Returns a string to display the product info for hits of the search
 */
std::string Book::displayString() const
{
    stringstream ss;
    stringstream ss1;

    ss1 << fixed << setprecision(2) << price_;

    ss << name_ << "\n";
    ss << "Author: " << author_ << " " << "ISBN: " << isbn_ << "\n";
    ss << ss1.str() << " " << to_string(qty_) << " left." << "\n";

    return ss.str();
}


/**
 * Outputs the product info in the database format
 */
void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << 
        "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}


//accessors and mutators
std::string Book::getAuthor() const
{
    return author_;
}

std::string Book::getIsbn() const
{
    return isbn_;
}