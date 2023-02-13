#ifndef BOOK_H
#define BOOK_H
#include "product.h"

class Book: public Product {

public:
    //constructor
    Book(const std::string category, const std::string name, double price, 
            int qty, std::string author, std::string isbn);

    //destructor
    ~Book();

     /**
     * Returns the appropriate keywords that this product should be associated with
     */
    std::set<std::string> keywords() const;


    /**
     * Returns a string to display the product info for hits of the search
     */
    std::string displayString() const;


    /**
     * Outputs the product info in the database format
     */
    void dump(std::ostream& os) const;


    //accessors and mutators
    std::string getAuthor() const;
    std::string getIsbn() const;

private:
    std::string author_;
    std::string isbn_;
};
#endif