#ifndef __ORDER_BOOK_ENTRY_H__
#define __ORDER_BOOK_ENTRY_H__

#include <string>

enum class OrderBookType{bid, ask, sale, unknown};

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
        void setAmount(double amount );

        static bool compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2){
            return e1.timestamp < e2.timestamp;
        }

        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2){
            return e1.price < e2.price;
        }

        static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2){
            return e1.price > e2.price;
        }
    
    private:
        std::string timestamp;
        std::string product;
        OrderBookType type;
        double price; 
        double amount;

};




#endif