/**
 * @file OrderBook.h
 * @author Pedro Vicente
 * @brief A Collection that stores and manipulates all the entries 
 * that were introduced since the beigining of the simulation
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef __ORDER_BOOK_H__
#define __ORDER_BOOK_H__

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

/// @brief A Collection that stores and manipulates all the entries 
/// that were introduced since the beigining of the simulation.
class OrderBook{

    public:
        /// @brief Constructor of the OrderBook based on a csv file.
        /// @param filename A csv file.
        OrderBook(std::string filename);
        
        /// @brief Gets all the known products of the simulation .
        /// @return the vector of OrderBookEntries of the simulation.
        std::vector<std::string> getKnownProducts();

        /// @brief Gets all the orders of the OrderBook with that type, product 
        /// and timestamp specified.
        /// @param type the type of entry.
        /// @param product the product in the entry.
        /// @param timestamp the timestamp of the entry.
        /// @return a vector of entrys around that timestamp.
        std::vector<OrderBookEntry> getOrders(  OrderBookType type,
                                                std::string product,
                                                std::string timestamp);

        

        /// @brief Goes to the next timestamp.
        /// @param timestamp 
        /// @return the next time timestamp.
        std::string getNextTime(const std::string& timestamp);

        /// @brief Gets the highest price of all the orders that were received
        /// @param orders std::vector of orders
        /// @return The highest price of the entries in the vector orders.
        static double getHighPrice(std::vector<OrderBookEntry> &orders);
        
        /// @brief Gets the lowest price of all the orders that were received
        /// @param orders std::vector of orders
        /// @return The lowest price of the entries in the vector orders.
        static double getLowPrice(std::vector<OrderBookEntry> &orders);

        /// @brief Gets the eraliest timestamp in the simultaion
        /// @return the earliest timestamp
        std::string getEarliestTime();
        
        /// @brief Inserts an entry into th OrderBook
        /// @param order An entry of the book
        void insertOrder(OrderBookEntry& order);
        
        /// @brief Computes all the possible matches between bids and aks in order to exectue the trade.
        /// @param product The product specified that all the bids and asks will have to contain.
        /// @param timestamp The timestamp at which the matching is being excuted.
        /// @return A std::vector with all the sales that were successful.
        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    private:
    
        /// @brief The vector which contain all the entries of the simulation
        std::vector<OrderBookEntry> orders;

};

#endif