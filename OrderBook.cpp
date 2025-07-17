
#include "OrderBook.h"
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <limits>
#include <string>
#include <vector>
#include <set>

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

std::vector<OrderBookEntry> OrderBook::getAllOrders(){
    return orders;
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

std::string OrderBook::obtainPastTimestamp(std::string timestamp, int days){
    // Obtain the past timestamp
    int year = std::stoi(timestamp.substr(0, 4));
    int month = std::stoi(timestamp.substr(5, 2));
    int day = std::stoi(timestamp.substr(8, 2));

    while (days > 0) {
        day--;
        if (day == 0) {
            month--;
            if (month == 0) {
                month = 12;
                year--;
            }
            // Days in month
            static const int daysInMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
            bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
            day = daysInMonth[month];
            if (month == 2 && leap) day = 29;
        }
        days--;
    }

    return  std::to_string(year)+"/"
            +std::to_string(month) +"/"
            +std::to_string(day) + 
            timestamp.substr(10, timestamp.size()-10);
}


/// @brief Computes the avrege of the past n weeks
/// @param orders vector of Entries
/// @param n_weeks number of weeks of the average
/// @param currentTimestamp current time stamp of the simulation
/// @param product string that corresponds to a specific type of product
/// @return the average of the price of all entries based on the number of weeks
double OrderBook::averageWeeks( std::vector<OrderBookEntry>& orders, 
                                int n_weeks, 
                                std::string currentTimestamp,
                                std::string product){

    std::string pastTimestamp{obtainPastTimestamp(currentTimestamp, n_weeks*7)};
    
    // Calculate the average of the price of all entries
    double sum = 0;
    double n_entries = 0;

    for(OrderBookEntry& order : orders){
        if( order.getTimestamp() >= pastTimestamp && 
            order.getTimestamp() <=currentTimestamp && 
            order.getProduct() == product){
            sum+=order.getPrice();
            ++n_entries;
        }
    }
    return sum/n_entries;
}

double OrderBook::change24Hours(    std::vector<OrderBookEntry>& orders,
                                    std::string current,
                                    std::string product){

    std::string pastTimestamp = obtainPastTimestamp(current, 1);
    double yesterdayPrice = 0, todaysPrice = 0;
    bool fisrtSeen = true;
    for(OrderBookEntry& entry : orders){
        if( entry.getTimestamp() >= pastTimestamp &&
            entry.getProduct()==product &&
            fisrtSeen){
            yesterdayPrice = entry.getPrice();
            fisrtSeen = !fisrtSeen;
        }
        if(entry.getTimestamp() <= current)
            todaysPrice = entry.getPrice();
        else
            break;
    }

    return todaysPrice - yesterdayPrice;
}

double OrderBook::high24Hours(  std::vector<OrderBookEntry>& orders,
                                std::string current,
                                std::string product){

    std::string pastTimespam{obtainPastTimestamp(current, 1)};

    double max = std::numeric_limits<double>::lowest();
    for(OrderBookEntry& entry : orders){
        if( entry.getTimestamp() >= pastTimespam &&
            entry.getTimestamp() <= current &&
            entry.getProduct() == product){
            if(max < entry.getPrice()) max = entry.getPrice();
        }
        if(entry.getTimestamp() > current) break; 
    }
    return max;
}

double OrderBook::low24Hours(   std::vector<OrderBookEntry>& orders,
                                std::string current,
                                std::string product){
    std::string pastTimespam{obtainPastTimestamp(current, 1)};
    double min = std::numeric_limits<double>::max();
    for(OrderBookEntry& entry : orders){
        if( entry.getTimestamp() >= pastTimespam &&
            entry.getTimestamp() <= current &&
            entry.getProduct() == product){
            if(min > entry.getPrice()) min = entry.getPrice(); 
        }
        if(entry.getTimestamp() > current) break; 
    }
    return min;

}
