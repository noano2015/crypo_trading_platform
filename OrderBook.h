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

        

        /// @brief Goes to the next timestamp
        /// @param timestamp 
        /// @return the next time timestamp
        std::string getNextTime(const std::string& timestamp);

        static double getHighPrice(std::vector<OrderBookEntry> &orders);

        static double getLowPrice(std::vector<OrderBookEntry> &orders);

        /// @brief Gets the eraliest timestamp in the simultaion
        /// @return the earliest timestamp
        std::string getEarliestTime();

        void insertOrder(OrderBookEntry& order);

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);

    private:
        /// @brief The vector which contain all the entries of the simulation
        std::vector<OrderBookEntry> orders;

};

#endif