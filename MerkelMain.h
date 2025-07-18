#ifndef __MERKEL_MAIN_H__
#define __MERKEL_MAIN_H__
#include <vector>
#include "OrderBook.h"
#include "Wallet.h"

class MerkelMain{

    public:
        MerkelMain() = default;
        void init();
        
    private:
        void printMenu();
        int getUserOption();
        void printHelp();
        void printMarketBids();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        void processUserOption(int userOption);


        OrderBook orderBook{"20200317.csv"};
        std::string currentTime{""};
        Wallet wallet;
};



#endif