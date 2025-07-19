/**
 * @file CSVReader.cpp
 * @author Pedro Vicente
 * @brief The class that allows to parse csv files
 * @date 2025-07-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef __CSV_READER_H__
#define __CSV_READER_H__
#include "OrderBookEntry.h"
#include <vector>

/// @brief Allows to read csv files and tokenise input
class CSVReader{
    
    public:

        /// @brief The default constructor of the CSVReader class.
        /// Not that useful.
        CSVReader();

        /// @brief Reads a csv file and returns the entries in that csv file
        /// @param CSVfile path of the csv file
        /// @return a std::vector of OrderBookEntry
        static std::vector<OrderBookEntry> readCSV(const std::string& CSVfile);

        /// @brief Basic tokenise function parses the line which was passed as input
        /// @param csvLine line of text
        /// @param separator a char which is the deliminator of the fields
        /// @return a std::vector of strings that were separated by the separator
        static std::vector<std::string> tokenise(std::string& csvLine, char separator);

        /// @brief Converts the strings into a OrderBookEntry
        /// @param timestamp 
        /// @param product 
        /// @param orderType 
        /// @param priceString 
        /// @param amountString 
        /// @param username 
        /// @return an OrderBookEntry with the specified values
        static OrderBookEntry stringsToOBE(std::string timestamp, 
                                            std::string product,
                                            OrderBookType orderType,
                                            std::string priceString,
                                            std::string amountString,
                                            std::string username = "dataset");
        
    private:
        /// @brief Converts the vector of strings into a OrderBookEntry
        /// @param strings 
        /// @return an OrderBookEntry with specified values
        static OrderBookEntry stringsToOBE(const std::vector<std::string>& strings);
        
};

#endif