#include "CSVReader.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

CSVReader::CSVReader(){}

std::vector<OrderBookEntry> CSVReader::readCSV(const std::string& csvFilename){

    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;

    if(csvFile.is_open()){

        while(std::getline(csvFile, line)){
            try{
                entries.push_back(stringsToOBE(tokenise(line, ',')));
            } catch(const std::exception& e){
                std::cout<< "CSVReader::readCSV bad data" << std::endl;
            }
        }
    }

    std::cout << "CSVReader number of entries read: " << entries.size() <<"." << std::endl;
    return entries;
}



std::vector<std::string> CSVReader::tokenise(std::string& csvLine, char separator){

    std::vector<std::string> tokens;

    int start = 0, end = 0;
    std::string token;

    start = csvLine.find_first_not_of(separator, 0);
    do{
        end = csvLine.find_first_of(separator,start);

        if(start == csvLine.length() || start == end) break;
        if(end >= 0) token = csvLine.substr(start, end - start);
        else token = csvLine.substr(start, csvLine.length() - start);

        tokens.push_back(token);
        start = end + 1;
    } while(end != std::string::npos);

    return tokens;
}

/**
 * @brief Creates an OrderBookEntry based of tokens of a line of the CSV file
 * 
 * @param tokens 
 * @return OrderBookEntry 
 */
OrderBookEntry CSVReader::stringsToOBE(const std::vector<std::string>& tokens){

    if (tokens.size() != 5){
        std::cout << "Bad line!" << std::endl;
        throw std::exception{};
    }
            
    double price = 0;
    double amount = 0;

    try{
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch(const std::exception& e){
        std::cout << "Price- Bad float: " << tokens[3] << std::endl; 
        std::cout << "Amount- Bad float: " << tokens[4] << std::endl; 
        throw;
    }

    return OrderBookEntry{  tokens[0],
                            tokens[1], 
                            OrderBookEntry::stringToOrderBookType(tokens[2]),
                            price,
                            amount};
}

OrderBookEntry CSVReader::stringsToOBE( std::string timestamp,
                                        std::string product,
                                        OrderBookType orderType,
                                        std::string priceString,
                                        std::string amountString,
                                        std::string username){
    double price, amount;
    try {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }catch(const std::exception& e){
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString<< std::endl;
        throw; 
    }
    return OrderBookEntry{timestamp, product, orderType, price, amount, username};
}