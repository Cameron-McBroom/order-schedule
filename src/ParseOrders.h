#pragma once

#include <vector>
#include <fstream>
#include <functional>
#include <string>

#include "Order.h"

class ParseOrders {
private:
    std::vector<Order> parsedOrders_;
    std::vector<int> strToVec(const std::string &line);

public:
    ParseOrders();
    std::vector<Order>& operator()(std::istream &orderBundle);
    int lastOrderNum(std::istream &orderBundle);
};

ParseOrders::ParseOrders() = default;

std::vector<int> ParseOrders::strToVec(const std::string &line) {
    std::vector<int> order;
    std::string num;
    for (const char &c: line){
        if (!isdigit(c) && !num.empty()){
            order.push_back(stoi(num));
            num = "";
        }
        else if (isdigit(c)) num += c;
    }
    return order;
}

int ParseOrders::lastOrderNum(std::istream &orderBundle) {
    std::string str;
    std::vector<int> orderNums;
    while (std::getline(orderBundle, str)) {
        if(!str.empty()) {
            std::vector<int> order = strToVec(str);
            orderNums.push_back(order[0]);
        }
    }
    return orderNums.back();
}

std::vector<Order> &ParseOrders::operator()(std::istream &orderBundle) {
    std::string str;
    while (std::getline(orderBundle, str)) {
        if(!str.empty()) {
            std::vector<int> order = strToVec(str);
            parsedOrders_.emplace_back(Order(order[0], order[1], order[2], order[3]));
        }
    }
    return parsedOrders_;
}
