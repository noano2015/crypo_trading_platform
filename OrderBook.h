#ifndef __ORDER_BOOK_H__
#define __ORDER_BOOK_H__

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>


class OrderBook{

    public:
        /// @brief Constructor of the OrderBook based on a filename;
        /// @param filename 
        OrderBook(std::string filename);
        
        /// @brief Gets all the known products of the simulation 
        /// @return the vector of OrderBookEntries of the simulation
        std::vector<std::string> getKnownProducts();

        /// @brief Gets all the orders of the OrderBook with that type, product 
        /// and timestamp specified
        /// @param type the type of entry
        /// @param product the product in the entry 
        /// @param timestamp the timestamp of the entry
        /// @return a vector of entrys around that timestamp
        std::vector<OrderBookEntry> getOrders(  OrderBookType type,
                                                std::string product,
                                                std::string timestamp);

        /// @brief Gets all the entries of the book
        /// @return all entries of the book
        std::vector<OrderBookEntry> getAllOrders();
        
        /// @brief Computes the avrege of the past n weeks
        /// @param orders vector of Entries
        /// @param n_weeks number of weeks of the average
        /// @param currentTimestamp current time stamp of the simulation
        /// @param product string that corresponds to a specific type of product
        /// @return the average of the price of all entries based on the number of weeks
        static double averageWeeks( std::vector<OrderBookEntry>& orders,
                                    int n_weeks, 
                                    std::string currentTimestamp,
                                    std::string product);
        
        /// @brief computes the absolute difference of the prices in the last 24h
        /// @param orders vector of entries
        /// @param current the current timestamp
        /// @param product the type of product in question
        /// @return the absolute difference
        static double change24Hours(std::vector<OrderBookEntry>& orders,
                                    std::string current,
                                    std::string product);
        
        /// @brief computes the highest price in the entries
        /// @param orders vector of entries
        /// @param current the current timestamp
        /// @param product the type of product in question
        /// @return the highest value of an entry in the past 24 hours
        static double high24Hours(  std::vector<OrderBookEntry>& orders,
                                    std::string current,
                                    std::string product);
        
        /// @brief computes the lowest price of the entries
        /// @param orders vector of entries
        /// @param current  the current timestamp
        /// @param product the type of product in question
        /// @return the lowest value of an entry in the past 24 hours
        static double low24Hours(   std::vector<OrderBookEntry>& orders,
                                    std::string current,
                                    std::string product);

        /// @brief Goes to the next timestamp
        /// @param timestamp 
        /// @return the next time timestamp
        std::string getNextTime(const std::string& timestamp);
        
        /// @brief Gets the eraliest timestamp in the simultaion
        /// @return the earliest timestamp
        std::string getEarliestTime();

    private:
        /// @brief The vector which contain all the entries of the simulation
        std::vector<OrderBookEntry> orders;

        /// @brief Obatins the past timestamp by a number of days
        /// @param timestamp - the specified current timestamp
        /// @param days - the number of days to the past timestamp
        /// @return the date before the number of days specified
        static std::string obtainPastTimestamp(std::string timestamp, int days);
};

#endif