#ifndef __WALLET_H__
#define __WALLET_H__
#include <string>
#include <map>
#include "OrderBookEntry.h"

class Wallet{
public:
    Wallet();
    /** insert currency to the wallet */
    void insertCurrency(std::string type, double amount);
    /** remove currency from the wallet */
    bool removeCurrency(std::string type, double amount);
    /** check if the wallet contains this much currency or more */
    bool containsCurrency(std::string type, double amount);
    /** generate a string representation of the wallet */
    std::string toString();

    friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

    bool canFulfillOrder(OrderBookEntry order);

    void processSale(OrderBookEntry& sale);

private:
    std::map<std::string,double> currencies;
};

#endif