/**
 * @file MerkelMain.cpp
 * @author Pedro Vicente
 * @brief The core of all the features of the crypto trading simulation
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "MerkelMain.h"
#include <iostream>
#include "CSVReader.h"
#include "OrderBook.h"

void MerkelMain::init(){

    currentTime = orderBook.getEarliestTime();
    std::cout << "Current Time: " << currentTime << std::endl;
    wallet.insertCurrency("BTC", 10);
    int input = 0;
    while(true){

        printMenu();
        int input = getUserOption();
        if(input == 7) break;
        processUserOption(input);
        
    }
}


void MerkelMain::printMenu(){
    std::cout << "=====Menu=====" << std::endl;
    std::cout << "1: Print help" << std::endl;
    std::cout << "2: Print exchange stats" << std::endl;
    std::cout << "3: Place an ask" << std::endl;
    std::cout << "4: Place a bid" << std::endl;
    std::cout << "5: Print wallet" << std::endl;
    std::cout << "6: Continue" << std::endl;
    std::cout << "7: Exit" << std::endl;
    std::cout << "==============" <<std::endl;
}

int MerkelMain::getUserOption(){
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-6" << std::endl;
    std::getline(std::cin, line);
    try{
        userOption = std::stoi(line);

    } catch(const std::exception& e){}

    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

void MerkelMain::printHelp(){
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;
}

void MerkelMain::printMarketBids(){
   
    for (const std::string& product : orderBook.getKnownProducts()){
        std::cout << "Product: " << product << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, product, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
        
    }
}

void MerkelMain::enterAsk(){
    std::cout << "Make an ask - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    if(tokens.size() != 3){
        std::cout << "MerkelMain::enterAsk: Bad Input! You didn't put enough arguments." << std::endl;
    }else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(   
                                            currentTime,
                                            tokens[0],
                                            OrderBookType::ask, 
                                            tokens[1],
                                            tokens[2],
                                            "simuser"
                                            );

            if (wallet.canFulfillOrder(obe)){
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        
        } catch (std::exception& e){
            std::cout << "MerkelMain::enterAsk: Bad Input! You put invalid arguments." << std::endl;
        }
    }

}

void MerkelMain::enterBid(){
    std::cout << "Make an bid - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');

    if(tokens.size() != 3){
        std::cout << "MerkelMain::enterBid: Bad Input! You didn't put enough arguments." << std::endl;
    }else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(   
                                            currentTime,
                                            tokens[0],
                                            OrderBookType::bid, 
                                            tokens[1],
                                            tokens[2],
                                            "simuser"
                                            );

            if (wallet.canFulfillOrder(obe)){
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        
        } catch (std::exception& e){
            std::cout << "MerkelMain::enterBid: Bad Input! You put invalid arguments." << std::endl;
        }
    }
}

void MerkelMain::printWallet(){
    std::cout << wallet << std::endl;
}

void MerkelMain::gotoNextTimeframe(){
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string& p : orderBook.getKnownProducts()){

        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales){
            std::cout << "Sale price: " << sale.getPrice() << " amount " << sale.getAmount() << std::endl;
            if(sale.getUsername() == "simuser"){
                wallet.processSale(sale);
                std::cout << "VENDIDO!" << std::endl;
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
    std::cout << "Current Time: " << currentTime << std::endl;
}


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