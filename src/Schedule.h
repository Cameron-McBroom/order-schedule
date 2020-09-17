#pragma once

#include <unordered_map>
#include <vector>
#include <fstream>
#include <ostream>
#include <iomanip>

#include "ParseOrders.h"
#include "Constant.h"
#include "Order.h"
#include "QuickSort.h"
#include "Utility.h"

class Schedule {
protected:
    std::vector<Order> ordersReceived_;
    std::vector<Order> ordersSatisfied_;
    std::vector<Order> ordersCancelled_;
    std::unordered_map<int, int> PCsProduce_;
    std::unordered_map<std::string, int> componentProduce_;
    std::unordered_map<std::string, int> COMP_COST_MAP;
    int totalCyclesUsed_;
    int totalRevenue_;
    double totalCancelCost_;
    double discount_;
    double grossProfit_;
    double netProfit_;
    void calculateDiscount();
    double salesExpenses();

public:
    Schedule(std::istream &orderBundle);
    virtual void createSchedule();
    void makeReport(std::ostream &out);
};

Schedule::Schedule(std::istream &orderBundle)
    : ordersReceived_(ParseOrders()(orderBundle)),
      totalCyclesUsed_(0), grossProfit_(0), netProfit_(0), totalRevenue_(0), discount_(0), totalCancelCost_(0)
{}

void Schedule::calculateDiscount() {
    for (auto const &pair: componentProduce_)
        if (pair.first.find("CPU") != std::string::npos)
            if (pair.second >= Const::CPU_DISC_REQ) {
                double priceBefore = Const().compPrice(pair.first) * pair.second;
                double discPrice = (Const().compPrice(pair.first) * pair.second) * Const::CPU_DISCOUNT;
                discount_ += (priceBefore - discPrice);
            }
    netProfit_ = grossProfit_ + discount_;
}

void Schedule::makeReport(std::ostream &out) {
    out << "TOP LEVEL METRICS" << std::endl;
    out << "Total orders: " << ordersReceived_.size() << std::endl;
    out << "Orders Satisfied: " << ordersSatisfied_.size() << std::endl;
    out << "Orders Cancelled: " << ordersCancelled_.size() << std::endl;
    out << "Total Cycles Used: " << totalCyclesUsed_ << std::endl;

    out << "===========================================================" << std::endl;
    out << "PROFIT AND REVENUE" << std::endl;
    out << std::setw(46) << std::left << "Total Revenue: " << "$"
        << std::setw(11) << std::right << util::numWCommas(totalRevenue_) << std::endl;

    out << std::setw(46) << std::left << "Operational / Selling Expenses:" << "$"
        << std::setw(11) << std::right << "-" + util::numWCommas(salesExpenses(),0) << std::endl;

    out << std::setw(46) << std::left << "Total Cycle Cost: " << "$"
        << std::setw(11) << std::right << "-" + util::numWCommas(totalCyclesUsed_ * Const::CYCLE_COST) << std::endl;

    out << std::setw(46) << std::left << "Total Cancellation Cost:" << "$"
        << std::setw(11) << std::right << "-" + util::numWCommas(totalCancelCost_,0) << std::endl << std::endl;

    out << std::setw(46) << std::left <<"Gross Profit (after cancellations):" << "$"
        << std::setw(11) << std::right << util::numWCommas(grossProfit_, 0) << std::endl;

    out << std::setw(46) << std::left << "Net Profit (including discounts):" << "$"
        << std::setw(11) << std::right << util::numWCommas(netProfit_, 0) << std::endl;

    out << "===========================================================" << std::endl;
    out << "NO. PC PRODUCED" << std::endl;
    for (int i = 0; i < PCsProduce_.size(); i++)
        out << std::setw(30) << std::left << std::setfill('_') << ("PC" + std::to_string(i)) << PCsProduce_[i] << std::endl;

    out << "===========================================================" << std::endl;
    out << "NO. COMPONENTS USED" << std::endl;
    for (auto const &pair: componentProduce_)
        out << std::setw(30) << std::left << pair.first << std::right << pair.second << std::endl;

    out << std::setfill(' ') << std::endl;
}

double Schedule::salesExpenses() {
    return grossProfit_ - (totalCyclesUsed_* Const::CYCLE_COST) - totalCancelCost_;
}

void Schedule::createSchedule() {
    for (const auto &order: ordersReceived_) {
        if (totalCyclesUsed_ < Const::MAX_CYCLES && totalCyclesUsed_ + order.getCycles() <= Const::MAX_CYCLES) {
            ordersSatisfied_.push_back(order);
            totalCyclesUsed_ += order.getCycles();
            PCsProduce_[order.getPCId()] += order.getQuantity();

            // Loop through components used and add to component map
            for (int i = 0; i < 4; i++)
                componentProduce_[order.getCompName(i)] += order.getQuantity();

            // Add profit & rev for each order
            totalRevenue_ += order.getRevenue();
            grossProfit_ += order.getProfitTotal();

        } else {
            ordersCancelled_.push_back(order);
            totalCancelCost_ += order.getCancelCost();
        }
    }
    calculateDiscount();
}
