/**
 * @file Wallet.cpp
 * @author Pedro Vicente
 * @brief The container in which all the crypto assets of the user
 * are saved during the simulation.
 * @version 0.1
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "../headers/Wallet.h"
#include <vector>
#include "../headers/CSVReader.h"

Wallet::Wallet(){}

/** insert currency to the wallet */
void Wallet::insertCurrency(std::string type, double amount){
    if(amount < 0) throw std::exception{};
    if(currencies.find(type) != currencies.end()){
        currencies[type] += amount;
    }
    else {currencies[type] = amount;}
}

/** remove currency from the wallet */
bool Wallet::removeCurrency(std::string type, double amount){
    if( amount < 0) throw std::exception{};
    if(containsCurrency(type, amount)){
        currencies[type] -= amount;
        return true;
    }
    else if(currencies.find(type) != currencies.end()) return true;
    return false;
}

/** check if the wallet contains this much currency or more */
bool Wallet::containsCurrency(std::string type, double amount){
    if(amount < 0) return false;
    if(currencies.find(type) == currencies.end()) return false;
    return currencies[type] >= amount;
}

/** generate a string representation of the wallet */
std::string Wallet::toString(){
    std::string wallet_str{""};
    for(std::pair<std::string, double> currency : currencies){
        wallet_str += currency.first + " : " + std::to_string(currency.second) + "\n";
    }
    return wallet_str;
}

bool Wallet::canFulfillOrder(OrderBookEntry order){

    std::string product = order.getProduct();
    std::vector<std::string> currs = CSVReader::tokenise(product, '/');

    if(order.getType() == OrderBookType::ask){
        std::string currency = currs[0];
        return containsCurrency(currency, order.getAmount());
    }
    if(order.getType() == OrderBookType::bid){
        std::string currency = currs[1];
        return containsCurrency(currency, order.getAmount());
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, Wallet& wallet){
    os << wallet.toString();
    return os;
}

void Wallet::processSale(OrderBookEntry& sale){
    std::string product = sale.getProduct();
    std::vector<std::string> currs = CSVReader::tokenise(product, '/');
    // ask
    if (sale.getType() == OrderBookType::asksale){
        double outgoingAmount = sale.getAmount();
        std::string outgoingCurrency = currs[0];
        double incomingAmount = sale.getAmount() * sale.getPrice();
        std::string incomingCurrency = currs[1];
        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
    // bid
    if (sale.getType() == OrderBookType::bidsale){
        double incomingAmount = sale.getAmount();
        std::string incomingCurrency = currs[0];
        double outgoingAmount = sale.getAmount() * sale.getPrice();
        std::string outgoingCurrency = currs[1];
        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}

