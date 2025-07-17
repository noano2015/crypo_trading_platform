#ifndef __ORDER_BOOK_ENTRY_H__
#define __ORDER_BOOK_ENTRY_H__

#include <string>

enum class OrderBookType{bid, ask, unknown};

class OrderBookEntry{

    public:

        OrderBookEntry(
            std::string _timestamp,
            std::string _product,
            OrderBookType _type,
            double _price,
            double _amount
        );
        
        static OrderBookType stringToOrderBookType(std::string s);
        double getPrice();
        double getAmount();
        OrderBookType getType();
        std::string getTimestamp();
        std::string getProduct();
    
    private:
        std::string timestamp;
        std::string product;
        OrderBookType type;
        double price; 
        double amount;

};




#endif