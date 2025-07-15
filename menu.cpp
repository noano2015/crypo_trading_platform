#include <iostream>
#include <map>


/**
 * @brief Prints the main menu of the crypto trading platform
 * 
 */
void printMenu(){
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
int getUserOption(){

    int userOption;
    std::cout << "Type in 1-6:" << std::endl;
    std::cin >> userOption;
    return userOption;
}

void printHelp(){
    std::cout << "Help - your aim is to make money." << std::endl;
    std::cout << "Analyse the market and make bids" << std::endl;
    std::cout << "and offers. " << std::endl;
}

void printMarketBids(){
    std::cout << "Exchange stats. Showing the latest market data..." <<std::endl;
}

void enterAsk(){
    std::cout << "Ask. Ask about a bid..." << std::endl;
}

void enterBid(){
    std::cout << "Bid. Place your Bid..." << std::endl;
}

void printWallet(){
    std::cout << "Wallet. Showing your Wallet..." << std::endl;
}

void gotoNextTimeframe(){
    std::cout << "The operation was successful." <<std::endl;
}


/**
 * @brief Processes the option inserted by the user
 * 
 * @param userOption 
 */
void processUserOption(int userOption){

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

int main(){

    while(true){

        printMenu();
        int userOption = getUserOption();
        processUserOption(userOption);
        
    }
    return 0;
}

