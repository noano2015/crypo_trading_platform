#include "MerkelMain.h"
#include <iostream>
#include "CSVReader.h"



void MerkelMain::init(){

    currentTime = orderBook.getEarliestTime();
    int input = 0;
    while(true){

        printMenu();
        int input = getUserOption();
        processUserOption(input);
        
    }
}



/**
 * @brief Prints the main menu of the crypto trading platform
 * 
 */
void MerkelMain::printMenu(){
    std::cout << "=====Menu=====" << std::endl;
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "==============" <<std::endl;
}

/**
 * @brief Gets the option from the user
 * 
 * @return int 
 */
int MerkelMain::getUserOption(){

    int userOption;
    std::cout << "Type in 1-6:" << std::endl;
    std::cin >> userOption;
    return userOption;
}

void MerkelMain::printHelp(){
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;
}

void MerkelMain::printMarketBids(){
   
    for (const std::string& product : orderBook.getKnownProducts()){
        std::vector<OrderBookEntry> allEntries = orderBook.getAllOrders();
        std::cout << "Product: " << product << std::endl;
        std::cout << "24h Change: " << orderBook.change24Hours(allEntries, currentTime, product) << std::endl;
        std::cout << "24h High: " << orderBook.high24Hours(allEntries, currentTime, product) << std::endl;
        std::cout << "24h Low: " << orderBook.low24Hours(allEntries, currentTime, product) << std::endl;
        std::cout << "7 Week Average: " << orderBook.averageWeeks(allEntries, 7, currentTime, product) << std::endl;
        std::cout << "25 Week Average: " << orderBook.averageWeeks(allEntries, 25, currentTime, product) << std::endl;
        std::cout << "99 Week Average: " << orderBook.averageWeeks(allEntries, 99, currentTime, product) << std::endl;
    }
}

void MerkelMain::enterAsk(){
    std::cout << "Ask. Ask about a bid..." << std::endl;
}

void MerkelMain::enterBid(){
    std::cout << "Bid. Place your Bid..." << std::endl;
}

void MerkelMain::printWallet(){
    std::cout << "Wallet. Showing your Wallet..." << std::endl;
}

void MerkelMain::gotoNextTimeframe(){
    std::cout << "Going to next time frame. "  << "." << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "Current time: " << currentTime << "." << std::endl;
}


/**
 * @brief Processes the option inserted by the user
 * 
 * @param userOption 
 */
void MerkelMain::processUserOption(int userOption){

    switch (userOption){
            
        case 1:
            printHelp();
            break;
            
        case 2:
            printMarketBids();
            break;

        case 3:
            enterAsk();
            break;

        case 4:
            enterBid();
            break;

        case 5:
            printWallet();
            break;

        case 6:
            gotoNextTimeframe();
            break;

        default:
            std::cout<< "Invalid operation." <<std::endl;
            break;
    }
    
}