#pragma once

#include "Date.h"
#include "Product.h"

class Order {
private:
    Date dueDate_;
    Product p;
    int orderId_;
    int PCId_;
    int quantity_;
    int unitProfitRate_;
    int revenue_;
    double profit_;
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
    double getCancelCost() const;
    double getDiscount() const;
    std::string getCompName(int index) const;
    std::unordered_map<std::string, int> getCPUsUsed() const;

    friend bool operator>(const Order &order1, const Order &order2);
    friend bool operator>=(const Order &order1, const Order &order2);
    friend bool operator<(const Order &order1, const Order &order2);
    friend bool operator<=(const Order &order1, const Order &order2);
    Order &operator+= (double x);
    Order &operator+= (int x);
    Order &operator-= (double x);
    Order &operator-= (int x);

};

Order::Order(int orderId, int PCId, int quantity, int unitProfitRate)
: orderId_(orderId), PCId_(PCId), quantity_(quantity), unitProfitRate_(unitProfitRate), cpuUsed_(0),
    dueDate_(1,1,1), p(PCId), discount_(0)
{
    revenue_ = p.getCost() * quantity_;
    profit_ = (p.getCost() * (static_cast<double>(unitProfitRate_)/100)) * quantity_;
    cycles_ = Const::cycleMap[p.getId()] * quantity_;
    cancelCost_ = (p.getCost() * quantity_) * Const::CANCELLATION_PENALTY;

    // Loop through components used and add to component map
    for (const auto &comp : p.getComponents()) {
        if (comp.getName().find("CPU") != std::string::npos){
            cpuUsed_[comp.getName()] += quantity_;
            discount_ += (comp.getCost() * quantity_) - ((comp.getCost() * quantity_) * Const::CPU_DISCOUNT);
        }
    }
}

std::string Order::getCompName(int index) const {
    return p.getComponents()[index].getName();
}

double Order::getProfitTotal() const { return profit_; }

int Order::getCycles() const {return cycles_;}

int Order::getPCId() const {return PCId_; }

int Order::getQuantity() const { return quantity_; }

int Order::getOrderId() const { return orderId_; }

double Order::getCancelCost() const { return cancelCost_; }

int Order::getRevenue() const { return revenue_; }

double Order::getDiscount() const { return discount_; }

std::unordered_map<std::string, int> Order::getCPUsUsed() const { return cpuUsed_; }

bool operator>(const Order &order1, const Order &order2) {
    return order1.profit_ > order2.profit_;
}

bool operator>=(const Order &order1, const Order &order2) {
    return order1.profit_ >= order2.profit_;
}

bool operator<(const Order &order1, const Order &order2) {
    return order1.profit_ < order2.profit_;
}

bool operator<=(const Order &order1, const Order &order2) {
    return order1.profit_ <= order2.profit_;
}

Order &Order::operator+=(double x) {
    this->profit_ += x;
    return *this;
}

Order &Order::operator+=(int x) {
    this->profit_ += x;
    return *this;
}

Order &Order::operator-=(double x) {
    this->profit_ -= x;
    return *this;
}

Order &Order::operator-=(int x) {
    this->profit_ -= x;
    return *this;
}















