/**
 * @file OrderBook.cpp
 * @author Pedro Vicente
 * @brief A Collection that stores and manipulates all the entries 
 * that were introduced since the beigining of the simulation
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "../headers/OrderBook.h"
#include "../headers/OrderBookEntry.h"
#include "../headers/CSVReader.h"
#include <limits>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>

/** construct, reading a csv data file */
OrderBook::OrderBook(std::string filename){
    orders = CSVReader::readCSV(filename);
}


/** return vector of all know products in the dataset*/
std::vector<std::string> OrderBook::getKnownProducts(){
    std::set<std::string> prodSet;
    std::vector<std::string> products;

    for (OrderBookEntry& entry : orders){
        if(prodSet.find(entry.getProduct()) == prodSet.end()){
            prodSet.insert(entry.getProduct());
            products.push_back(entry.getProduct());
        }
    }

    return products;
}

/** return vector of Orders according to the sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(  OrderBookType type,
                                        std::string product,
                                        std::string timestamp){
    
    std::vector<OrderBookEntry> entries;

    for(OrderBookEntry& entry : orders){
        if( entry.getType() == type &&
            entry.getProduct() == product &&
            entry.getTimestamp() == timestamp){
                entries.push_back(entry);
            }
    }

    return entries;
}

std::string OrderBook::getEarliestTime(){
    
    std::string earliest = orders[0].getTimestamp(); 
    for(OrderBookEntry& order : orders){
        if(earliest > order.getTimestamp()) earliest = order.getTimestamp();
    }
    return earliest;
}

std::string OrderBook::getNextTime(const std::string& timestamp){

    std::string next_timestamp = "";
    for (OrderBookEntry& order : orders){
        if (order.getTimestamp() > timestamp){
            next_timestamp = order.getTimestamp();
            break;
        }
    }
    if (next_timestamp == "") next_timestamp = getEarliestTime();

    return next_timestamp;
}

/** return the price of the highest bid in the sent set */
double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders){
    double max = std::numeric_limits<double>::lowest();
    for(OrderBookEntry& entry : orders){
        if(max < entry.getPrice()) max = entry.getPrice(); 
    }
    return max;
}

/** return the price of the lowest bid in the sent set */
double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders){
    double min = std::numeric_limits<double>::max();
    for(OrderBookEntry& entry : orders){
        if(min > entry.getPrice()) min = entry.getPrice(); 
    }
    return min;
}

void OrderBook::insertOrder(OrderBookEntry& order){
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp){
    std::vector<OrderBookEntry> sales;
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);

    if (asks.size() == 0 || bids.size() == 0){
        std::cout << " OrderBook::matchAsksToBids no bids or asks" << std::endl;
        return sales;
    }

    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    // sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    // for ask in asks:
    std::cout << "max ask " << asks[asks.size()-1].getPrice() << std::endl;
    std::cout << "min ask " << asks[0].getPrice() << std::endl;
    std::cout << "max bid " << bids[0].getPrice() << std::endl;
    std::cout << "min bid " << bids[bids.size()-1].getPrice() << std::endl;

    for(OrderBookEntry& ask : asks){
        
        for(OrderBookEntry& bid : bids){
            
        
            if( bid.getPrice() >= ask.getPrice()){

                OrderBookEntry sale{timestamp,
                                product,
                                OrderBookType::asksale,
                                ask.getPrice(),
                                0};

                if (bid.getUsername()== "simuser"){

                    sale.setUsername("simuser");
                    sale.setType(OrderBookType::bidsale);
                }
                if (ask.getUsername() == "simuser"){
                    
                    sale.setUsername("simuser");
                    sale.setType(OrderBookType::asksale);
                }

                if(ask.getAmount() == bid.getAmount()){

                    sale.setAmount(ask.getAmount());
                    sales.push_back(sale);
                    bid.setAmount(0);
                    break;
                }

                if(ask.getAmount() < bid.getAmount()){
                    sale.setAmount(ask.getAmount());
                    sales.push_back(sale);
                    bid.setAmount(bid.getAmount()- ask.getAmount());
                    break;
                }

                if(bid.getAmount() < ask.getAmount() && 
                   bid.getAmount() > 0){
                    sale.setAmount(bid.getAmount());
                    sales.push_back(sale);
                    ask.setAmount(ask.getAmount() - bid.getAmount());
                    bid.setAmount(0);
                    continue;
                }
            }
        }
    }
    return sales;
}