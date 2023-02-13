#include <string>
#include <iostream>
#include <iomanip>
#include <queue>
#include "product.h"
#include "user.h"
#include "datastore.h"
#include "util.h"
#include "mydatastore.h"

using namespace std;

//destructor
MyDataStore::~MyDataStore()
{
    //deallocate productsList
    vector<Product*>::iterator it1;
    for(it1 = productsList_.begin(); it1 != productsList_.end(); ++it1) {
        delete *it1;
    }

    //deallocate usersList
    vector<User*>::iterator it2;
    for(it2 = usersList_.begin(); it2 != usersList_.end(); ++it2) {
        delete *it2;
    }  


}

/**
 * Adds a product to the data store (is virtual)
 */
void MyDataStore::addProduct(Product* p)
{
    //insert the passed Product to the Products List set
    productsList_.push_back(p);

    //add the keywords for the product and the corresponding product with it
    set<string>::iterator it1;
    map<string, set<Product*>>::iterator it2;

    //create a new set that is a copy of keywords set of the current product
    set<string> newSet = p->keywords();

    //iterate through the keywords set to add it to map
    for(it1 = newSet.begin(); it1 != newSet.end(); ++it1)
    {
        //see if the current keyword is in the data_ map
        it2 = data_.find(*it1);

        if(it2 != data_.end()) { //if keyword already exist
            data_[*it1].insert(p);
        }
        else { //if the keyword doesn't exist in the map
            set<Product*> temp; //create a temp set 
            temp.insert(p); //insert the product into the temp set

            data_.insert({convToLower(*it1), temp}); //insert the pair(keyword, set with product) into map
        }
    }


}

/**
 * Adds a user to the data store (is virtual)
 */
void MyDataStore::addUser(User* u)
{

    //if user doesn't already exist
    if (find(usersList_.begin(), usersList_.end(), u) == usersList_.end()) {
        usersList_.push_back(u);

        string username = u->getName();

        //insert the corresponding username and the user object
        user_.insert({username, u});

        //insert the username and the vector of products
        vector<Product*> cartItems;
        cart_.insert({username, cartItems});
    }
}

/**
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 * (is virtual)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    vector<Product*> hits;
    /*
    case 1: the user doesn't search anything
    */
    if(terms.size() < 1) { //user searches nothing or only (AND, OR) w/o real keywords
        return hits;
    }

    /*
    case 2: the user searches multiple terms
    */
    if(type == 0) { //case 2.1: AND search
        set<Product*> tempSearch = data_[terms[0]];
        vector<string>::iterator it1 = terms.begin();

        for(it1 = terms.begin(); it1 != terms.end(); ++it1) {
            if(data_.find(convToLower(*it1)) != data_.end()) {

                if(!tempSearch.empty()) { //if set is not empty
                    tempSearch = setIntersection(tempSearch, data_[*it1]);
                }
                else {
                    tempSearch = data_[*it1]; //initialize the tempSearch
                }
            }
        }

        set<Product*>::iterator it2; //set iterator for the tempSearch set
        for(it2 = tempSearch.begin(); it2 != tempSearch.end(); ++it2) {
            hits.push_back(*it2); //add the Product* to the returning vector
        }
    }
    else if(type == 1) { //case 2.2: OR search
        set<Product*> tempSearch = data_[terms[0]];
        vector<string>::iterator it1;

        for(it1 = terms.begin(); it1 != terms.end(); ++it1) {
            if(data_.find(convToLower(*it1)) != data_.end()) {

                if(!tempSearch.empty()) { //if set is not empty
                    tempSearch = setUnion(tempSearch, data_[*it1]);
                }
                else {
                    tempSearch = data_[*it1]; //initialize the tempSearch
                }
            }
        }
        for(set<Product*>::iterator it3 = tempSearch.begin(); it3 != tempSearch.end(); ++it3) {
            hits.push_back(*it3);
        }
    }

    return hits;
}

/**
 * Reproduce the database file from the current Products and User values
 * is virtual
 */
void MyDataStore::dump(std::ostream& ofile)
{
    vector<Product*>::iterator it1;
    map<string, User*>:: iterator it2;

    ofile << "<products>" << endl;
    for(it1 = productsList_.begin(); it1 != productsList_.end(); ++it1) {
        //specific child class's dump()
        (*it1)->dump(ofile);
    }
    ofile << "</products>" << endl;

    ofile << "<users>" << endl;
    for(it2 = user_.begin(); it2 != user_.end(); ++it2) {
        (it2->second)->dump(ofile);
    }
    ofile << "</users>" << endl;

}

//adding product to user's cart
void MyDataStore::addToCart(string uname, Product* p) 
{
    uname = convToLower(uname);
    //iterator for the user's cart
    map<string, vector<Product*>>::iterator it1 = cart_.find(uname);
    
    if(it1 != cart_.end()) { //if the username was found
        (it1->second).push_back(p); //add the product to the cart's product vector
    }
    else {
        cout << "Invalid request" << endl;
    }
    

}

//view user's cart
void MyDataStore::viewCart(string uname)
{
    vector<Product*>::iterator it1;

    uname = convToLower(uname);
    int numItems = 1;
    if(cart_.find(convToLower(uname)) != cart_.end()) { //if the username is valid
        for(it1 = cart_[uname].begin(); it1 != cart_[uname].end(); ++it1) {
            cout << "Item " << numItems << endl;
            cout << (*it1)->displayString() << endl;
            numItems++;
        }
    }
    else {
        cout << "Invalid username" << endl;
    }

}

//buying user's cart
void MyDataStore::buyCart(string uname)
{
    uname = convToLower(uname);
    map<string, vector<Product*>>::iterator it1 = cart_.find(convToLower(uname));
    vector<Product*>::iterator it2;

    if(it1 != cart_.end()) { //if valid username

        for(it2 = cart_[uname].begin(); it2 != cart_[uname].end();) { //iterate thru user's cart
            double balance = user_[uname]->getBalance();

            if((*it2)->getQty() > 0) {
                if(balance >= (*it2)->getPrice()) {
                    (*it2)->subtractQty(1); //subtract in stock quantity by 1

                    user_[uname]->deductAmount((*it2)->getPrice()); //price debited from user's available credit
        
                    cart_[uname].erase(it2); //removed from the cart
                }
                else { //go to the next item without any action
                    ++it2;
                }
            }
            else { //go to the next item without any action
                ++it2;
            }
        }
    }
    else {
        cout << "Invalid username" << endl;
    }

}