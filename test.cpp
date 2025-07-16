#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "CSVReader.h"


/** function implementation */
std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator){

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

enum class OrderBookType{bid, ask};

int main(){
    std::string csvFilename{"20200317.csv"};
    std::ifstream csvFile{csvFilename};
    std::string line;
    int count = 0;

    if (csvFile.is_open()){
        std::cout << "Opened file " << csvFilename << std::endl;
        std::string line;
        while(getline(csvFile, line)){
            std::vector<std::string> tokens = tokenise(line, ',');
            std::cout << "Read " << tokens.size() << " tokens " << std::endl;
            if (tokens.size() != 5) continue;
            
            std::string timestamp = tokens[0];
            std::string product = tokens[1];
            OrderBookType type = (tokens[2] == "ask")? OrderBookType::ask:OrderBookType::bid;

            try{
                double price = std::stod(tokens[3]);
                double amount = std::stod(tokens[4]);
            }
            catch(const std::exception& e){
                continue;
            }
            ++count;

        }   
    }
    else{
        std::cout << "Problem opening file " << csvFilename << std::endl;
    }

    std::cout << count << " lines were read." << std::endl;
    // don't forget to close it!
    csvFile.close();
    return 0;
}
