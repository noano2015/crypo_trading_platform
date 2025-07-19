/**
 * @file OrderBookEntry.h
 * @author Pedro Vicente
 * @brief An entry of the OrderBook that stores the information of a bid, a ask or a sale
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __ORDER_BOOK_ENTRY_H__
#define __ORDER_BOOK_ENTRY_H__

#include <string>

/// @brief An enum that restricts the possibilities of the type of the OrderBookEntry.
enum class OrderBookType{bid, ask, unknown, asksale, bidsale};


/// @brief An entry of the OrderBook that stores the information of a bid, a ask or a sale.
class OrderBookEntry{

    public:

        /// @brief 
        /// @param _timestamp The timestamp when the entry was created.
        /// @param _product The product which the entry is about.
        /// @param _type If the entry is a bid, a ask or a sale.
        /// @param _price The price that the user put for the transaction.
        /// @param _amount The amount of the product that the user decided to trade.
        /// @param _username The user's name responsabile for the creation of the entry.
        OrderBookEntry(
            std::string _timestamp,
            std::string _product,
            OrderBookType _type,
            double _price,
            double _amount,
            std::string _username = "dataset"
        );
        
        /// @brief Converts a string to the specified OrderBookType
        /// @param s 
        /// @return An OrderBookType in the enum of OrderBookType.
        static OrderBookType stringToOrderBookType(std::string s);

        /// @brief Gets the price of the entry.
        /// @return The price of the entry.
        double getPrice();

        /// @brief Gets the amount of the entry.
        /// @return The amount of the entry.
        double getAmount();

        /// @brief Gets the OrderBookType of the entry.
        /// @return The OrderBookType of the entry.
        OrderBookType getType();

        /// @brief Gets the timestamp of creation of the entry.
        /// @return The timestamp of creation of the entry.
        std::string getTimestamp();

        /// @brief Gets the product of the entry.
        /// @return The product of the entry.
        std::string getProduct();

        /// @brief Gets the username of the creator of the entry.
        /// @return The username of the creator of the entry.
        std::string getUsername();

        /// @brief Sets a new price for the Entry.
        /// @param _price The new price.
        void setPrice(double _price);

        /// @brief Sets a new amount for the Entry.
        /// @param _amount The new amount.
        void setAmount(double _amount );

        /// @brief Sets a new OrderBookType for the Entry.
        /// @param _orderType The new OrderBookType.
        void setType(OrderBookType _orderType);

        /// @brief Sets a new username for the Entry.
        /// @param _username The new username.
        void setUsername(std::string _username);

        /// @brief Compares if the entry e2 comes before the entry e1.
        /// @param e1 timestamp of the simulation.
        /// @param e2 timestamp of the simulation.
        /// @return True if e2 comes after e1, False otherwise.
        static bool compareByTimestamp(const OrderBookEntry& e1, const OrderBookEntry& e2){
            return e1.timestamp < e2.timestamp;
        }

        /// @brief Comapres the price of two entries
        /// @param e1 price of one of the entries.
        /// @param e2 The price of the other entry.
        /// @return True if the e2's price is higher than the e1's price, False otherwise. 
        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2){
            return e1.price < e2.price;
        }

        /// @brief Comapres the price of two entries
        /// @param e1 price of one of the entries.
        /// @param e2 The price of the other entry.
        /// @return True if the e2's price is lower than the e1's price, False otherwise. 
        static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2){
            return e1.price > e2.price;
        }
    
    private:

        /// @brief The timestamp when the entry was created.
        std::string timestamp;

        /// @brief The product which the entry is about.
        std::string product;

        /// @brief If the entry is a bid, a ask or a sale.
        OrderBookType type;

        /// @brief The price that the user put for the transaction.
        double price; 

        /// @brief The amount of the product that the user decided to trade.
        double amount;

        /// @brief The user's name responsabile for the creation of the entry.
        std::string username;

};




#endif