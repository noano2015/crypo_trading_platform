/**
 * @file menu.cpp
 * @author Pedro Vicente
 * @brief The main program for the crypo_trading_platform
 * @date 2025-07-16
 *
 * @copyright Copyright (c) 2025
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "OrderBookEntry.h"
#include "MerkelMain.h"


double computeAveragePrice(std::vector<OrderBookEntry> &entries)
{

    double sum = 0;
    for (OrderBookEntry &entry : entries)
        sum += entry.price;
    return sum / entries.size();
}

double computeLowPrice(std::vector<OrderBookEntry> &entries)
{
    double min = std::numeric_limits<double>::max();
    for (OrderBookEntry &entry : entries)
        min = (min > entry.price) ? entry.price : min;
    return min;
}

double computeHighPrice(std::vector<OrderBookEntry> &entries)
{
    double max = std::numeric_limits<double>::lowest();
    for (OrderBookEntry &entry : entries)
        max = (max < entry.price) ? entry.price : max;
    return max;
}

double computePriceSpread(std::vector<OrderBookEntry> &entries)
{
    double highestBid = std::numeric_limits<double>::lowest();
    double lowestAsk = std::numeric_limits<double>::max();

    for (OrderBookEntry &entry : entries)
    {

        if (entry.type == OrderBookType::ask)
            lowestAsk = (lowestAsk > entry.price) ? entry.price : lowestAsk;

        if (entry.type == OrderBookType::bid)
            highestBid = highestBid = (highestBid < entry.price) ? entry.price : highestBid;
    }

    return lowestAsk - highestBid;
}

int main()
{

    MerkelMain app{};
    app.init();

    return 0;
}
