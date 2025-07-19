/**
 * @file Wallet.h
 * @author Pedro Vicente
 * @brief The container in which all the crypto assets of the user
 * are saved during the simulation.
 * @version 0.1
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __WALLET_H__
#define __WALLET_H__
#include <string>
#include <map>
#include "OrderBookEntry.h"

/// @brief The container in which all the crypto assets of the user
/// are saved during the simulation.
class Wallet{
public:

    /// @brief Default constructor of the wallet.
    /// Does not contain any crypto assets.
    Wallet();

    /// @brief Inserts an amount of a crypto product into the wallet.
    /// @param type The type of the crypto product.
    /// @param amount The amount of the crypto product.
    void insertCurrency(std::string type, double amount);

    /// @brief Removes an amount of a crypto product into the wallet.
    /// @param type The type of the crypto product.
    /// @param amount The amount of the crypto product.
    bool removeCurrency(std::string type, double amount);

    /// @brief Verifies if the wallet contains the amount of a crypto
    /// product necessary for a crypto transaction. 
    /// @param type The type of crypto product.
    /// @param amount The amount of the crypto product.
    /// @return True if the wallet contains. False otherwise.
    bool containsCurrency(std::string type, double amount);

    /// @brief Converts the wallet into string format.
    /// @return The string that represents the string.
    std::string toString();

    /// @brief Allows to use the object wallet into the std::cout.
    /// @param os 
    /// @param wallet 
    /// @return The std::osstream to output the wallet.
    friend std::ostream& operator<<(std::ostream& os, Wallet& wallet);

    /// @brief Verifies if the wallet can fulfill and OrderBookEntry.
    /// @param order The OrderBookEntry in question.
    /// @return True if It can, False otherwise.
    bool canFulfillOrder(OrderBookEntry order);

    /// @brief Computes a sale.
    /// @param sale 
    void processSale(OrderBookEntry& sale);

private:
    /// @brief A map that keeps track of all the currencies that the user has.
    std::map<std::string,double> currencies;
};

#endif