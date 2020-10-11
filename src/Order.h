#pragma once

#include "Date.h"
#include "Product.h"

class Order {
private:
    Date dueDate_;
    Product product_;
    int orderId_;
    int PCId_;
    int quantity_;
    int unitProfitRate_;
    double revenue_;
    double profit_;
    double profitPerCycle_;
    int cycles_;
    double cancelCost_;
    double discount_;
    std::unordered_map<std::string, int> cpuUsed_;


public:
    Order(int orderId, int PCId, int quantity, int unitProfit);
    double getProfitTotal() const;
    int getCycles() const;
    int getPCId() const;
    int getQuantity() const;
    int getOrderId() const;
    int getRevenue() const;
    int getProductCost() const;
    double getCancelCost() const;
    std::string getComponentName(int index) const;
    std::unordered_map<std::string, int> getCPUsUsed() const;

    friend bool operator>(const Order &order1, const Order &order2);
    friend bool operator>=(const Order &order1, const Order &order2);
    friend bool operator<(const Order &order1, const Order &order2);
    friend bool operator<=(const Order &order1, const Order &order2);

    template<typename Num, typename = typename std::enable_if<std::is_arithmetic<Num>::value, Num>::type>
    Order &operator+= (Num x);
    template<typename Num, typename = typename std::enable_if<std::is_arithmetic<Num>::value, Num>::type>
    Order &operator-= (Num x);

};

Order::Order(int orderId, int PCId, int quantity, int unitProfitRate)
: orderId_(orderId), PCId_(PCId), quantity_(quantity), unitProfitRate_(unitProfitRate), cpuUsed_(0),
  dueDate_(1,1,1), product_(PCId), discount_(0)
{
    profit_ = (product_.getCost() * (static_cast<double>(unitProfitRate_) / 100)) * quantity_;
    revenue_ = (product_.getCost() * quantity_) + profit_;
    cycles_ = Const::cycleMap[product_.getId()] * quantity_;
    cancelCost_ = revenue_ * Const::CANCELLATION_PENALTY;
    profitPerCycle_ = profit_ / cycles_;

    // Loop through components used and add to component map
    for (const auto &comp : product_.getComponents()) {
        if (comp.getName().find("CPU") != std::string::npos){
            cpuUsed_[comp.getName()] += quantity_;
            discount_ += (comp.getCost() * quantity_) - ((comp.getCost() * quantity_) * Const::CPU_DISCOUNT);
        }
    }
}

std::string Order::getComponentName(int index) const {
    return product_.getComponents()[index].getName();
}

double Order::getProfitTotal() const { return profit_; }

int Order::getCycles() const {return cycles_;}

int Order::getPCId() const {return PCId_; }

int Order::getQuantity() const { return quantity_; }

int Order::getOrderId() const { return orderId_; }

double Order::getCancelCost() const { return cancelCost_; }

int Order::getRevenue() const { return revenue_; }

int Order::getProductCost() const {
    return product_.getCost() * quantity_;
}

std::unordered_map<std::string, int> Order::getCPUsUsed() const { return cpuUsed_; }

bool operator>(const Order &order1, const Order &order2) {
    return order1.profitPerCycle_ > order2.profitPerCycle_;
}

bool operator>=(const Order &order1, const Order &order2) {
    return order1.profitPerCycle_ >= order2.profitPerCycle_;
}

bool operator<(const Order &order1, const Order &order2) {
    return order1.profitPerCycle_ < order2.profitPerCycle_;
}

bool operator<=(const Order &order1, const Order &order2) {
    return order1.profitPerCycle_ <= order2.profitPerCycle_;
}

template<typename Num, typename>
Order &Order::operator+=(Num x) {
    this->profit_ += x;
    profitPerCycle_ = profit_ / cycles_;
    return *this;
}

template<typename Num, typename>
Order &Order::operator-=(Num x) {
    this->profit_ -= x;
    profitPerCycle_ = profit_ / cycles_;
    return *this;
}

















