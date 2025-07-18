
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <limits>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

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

    for(OrderBookEntry& ask : asks){
        
        for(OrderBookEntry& bid : bids){
            
            OrderBookEntry sale{timestamp,
                                product,
                                OrderBookType::sale,
                                ask.getPrice(),
                                0};
            
            if( bid.getPrice() >= ask.getPrice()){
                if(ask.getAmount() == bid.getAmount()){

                    sale.setAmount(ask.getAmount());
                    sales.push_back(sale);
                    bid.setAmount(0);
                    break;
                }

                else if(ask.getAmount() < bid.getAmount()){
                    sale.setAmount(ask.getAmount());
                    sales.push_back(sale);
                    bid.setAmount(bid.getAmount()- ask.getAmount());
                    break;
                }

                else{
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