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
    double _amount,
    std::string _username)
: 
timestamp(_timestamp),
product(_product),
type(_type),
price(_price),
amount(_amount),
username(_username)
{}


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

std::string OrderBookEntry::getUsername(){ return username;}

void OrderBookEntry::setPrice(double _price){ price = _price; }

void OrderBookEntry::setAmount(double _amount){ amount = _amount; }

void OrderBookEntry::setType(OrderBookType _orderType){ type = _orderType;}

void OrderBookEntry::setUsername(std::string _username){ username = _username;}
