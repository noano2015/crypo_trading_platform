/**
 * @file MerkelMain.h
 * @author Pedro Vicente
 * @brief The core of all the features of the crypto trading simulation
 * @date 2025-07-19
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef __MERKEL_MAIN_H__
#define __MERKEL_MAIN_H__
#include <vector>
#include "OrderBook.h"
#include "Wallet.h"


/// @brief The core of the crypto trading simulation
class MerkelMain{

    public:
        /// @brief The default constructor of the program's core.(Not Inicialize)
        MerkelMain() = default;

        /// @brief Inicializes the program's core.
        void init();
        
    private:

        /// @brief Prints the main menu of the simulation into the console.
        void printMenu();

        /// @brief Gets the input of the user.
        /// @return Integer that represents the option of the user input.
        int getUserOption();

        /// @brief Prints the help menu.
        void printHelp();

        /// @brief Prints the market statistics for each product.
        void printMarketBids();

        /// @brief Allows, computes and saves the ask request from the user.
        void enterAsk();

        /// @brief Allows, computes and saves the bid request from the user.
        void enterBid();

        /// @brief Prints the contentes of the user's wallet.
        void printWallet();

        /// @brief Goes to the next timestamp of the simulation.
        void gotoNextTimeframe();

        /// @brief Computes the user's option.
        /// @param userOption the user's option/action.
        void processUserOption(int userOption);

        /// @brief The book that contains all the crypto trading actions of the simulation.
        OrderBook orderBook{"data/20200317.csv"};

        /// @brief Saves the current simulation timestamp.
        std::string currentTime{""};

        /// @brief The user's wallet with all of his/her crypto assets.
        Wallet wallet;
};
#endif