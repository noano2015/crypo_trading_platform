#ifndef __CSV_READER_H__
#define __CSV_READER_H__
#include "OrderBookEntry.h"
#include <vector>

class CSVReader{
    
    public:
        CSVReader();

        static std::vector<OrderBookEntry> readCSV(const std::string& CSVfile);
        static std::vector<std::string> tokenise(std::string& csvLine, char separator);
        static OrderBookEntry stringsToOBE(std::string timestamp, 
                                            std::string product,
                                            OrderBookType orderType,
                                            std::string priceString,
                                            std::string amountString);
        
    private:

        static OrderBookEntry stringsToOBE(const std::vector<std::string>& strings);
        
};

#endif