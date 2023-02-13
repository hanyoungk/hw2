#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

//constructor
Clothing::Clothing(const std::string category, const std::string name, double price, 
        int qty, std::string brand, std::string size) : Product(category, name, price, qty)
{
    brand_ = brand;
    size_ = size;
}

//destructor
Clothing::~Clothing()
{

}

/**
 * Returns the appropriate keywords that this product should be associated with
 */
std::set<std::string> Clothing::keywords() const
{
    set<string> s1 = parseStringToWords(name_);
    set<string> s2 = parseStringToWords(brand_);

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
std::string Clothing::displayString() const
{

    stringstream ss1;

    ss1 << fixed << setprecision(2) << price_;

    string str = name_ + "\n";
    str += "Size: " + size_ + " " + "Brand: " + brand_ + "\n";
    str += ss1.str() + " " + to_string(qty_) + " left." + "\n";

    return str;
}


/**
 * Outputs the product info in the database format
 */
void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ 
        << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

//accessor and mutators
std::string Clothing::getBrand() const
{
    return brand_;
}

std::string Clothing::getSize() const
{
    return size_;
}