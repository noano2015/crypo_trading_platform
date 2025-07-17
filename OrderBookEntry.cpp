#include "OrderBookEntry.h"
#include <string>

/**
 * @brief Construct a new Order Book Entry:: Order Book Entry object
 * 
 * @param _timestamp 
 * @param _product 
 * @param _type 
 * @param _price 
 * @param _amount 
 */
OrderBookEntry::OrderBookEntry(
    std::string _timestamp,
    std::string _product,
    OrderBookType _type,
    double _price,
    double _amount)
: 
timestamp(_timestamp),
product(_product),
type(_type),
price(_price),
amount(_amount) {}


OrderBookType OrderBookEntry::stringToOrderBookType(std::string s){
    if(s == "ask") return OrderBookType::ask;
    if(s == "bid") return OrderBookType::bid;
    return OrderBookType::unknown;
}

/**
 * @brief Gets the price of the entry
 * 
 * @return double 
 */
double OrderBookEntry::getPrice(){ return price; }


/**
 * @brief 
 * 
 * @return double 
 */
double OrderBookEntry::getAmount(){ return amount; }

/**
 * @brief 
 * 
 * @return OrderBookType 
 */
OrderBookType OrderBookEntry::getType(){return type;}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string OrderBookEntry::getTimestamp(){return timestamp;}

/**
 * @brief 
 * 
 * @return std::string 
 */
std::string OrderBookEntry::getProduct(){ return product;}
