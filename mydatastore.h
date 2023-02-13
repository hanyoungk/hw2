#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include <map>
#include <vector>
#include <set>


class MyDataStore: public DataStore {

public:
    //constructor 
    // MyDataStore();

    //destructor
    ~MyDataStore();

    /**
     * Adds a product to the data store (is virtual)
     */
    void addProduct(Product* p);

    /**
     * Adds a user to the data store (is virtual)
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     * (is virtual)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     * is virtual
     */
    void dump(std::ostream& ofile);


    //adding product to user's cart
    void addToCart(std::string uname, Product* p);

    //view user's cart
    void viewCart(std::string uname);

    //buying user's cart
    void buyCart(std::string uname);

    // virtual void getUser(std::string uname);






protected:

private:
    std::vector<Product*> productsList_;
    std::vector<User*> usersList_;

    //map to store the all possible products according to the keywords
    std::map<std::string, std::set<Product*>> data_;

    //map to store all of usernames and User?
    std::map<std::string, User*> user_;
    
    //set for cart that holds username and the list of products
    std::map<std::string, std::vector<Product*>> cart_;

    // std::vector<Product*> hits;
};
#endif