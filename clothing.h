#ifndef CLOTHING_H
#define CLOTHING_H
#include "product.h"

class Clothing: public Product {

public:
    //constructor
    Clothing(const std::string category, const std::string name, double price, 
            int qty, std::string brand, std::string size);
    
    //destructor
    ~Clothing();

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

    //accessor and mutators
    std::string getBrand() const;
    std::string getSize() const;

private:
    std::string brand_;
    std::string size_;

};
#endif