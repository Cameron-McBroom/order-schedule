#ifndef CONSTANT_H_
#define CONSTANT_H_

#include <string>
#include <unordered_map>
#include <vector>

class Const {
private:
    std::unordered_map<std::string, int> COMP_PRICE_MAP;

public:
    Const();
    static const int MAX_CYCLES;
    static const int CYCLE_COST;
    static const int CPU_DISC_REQ;
    static const double CPU_DISCOUNT;
    static const double CANCELLATION_PENALTY;
    static const int MAX_ORDER_QUANTITY;
    static const int MIN_PROFIT_RATE;
    static const int MAX_PROFIT_RATE;
    static const int MIN_ORDER_BUNDLE;
    static const int MAX_ORDER_BUNDLE;
    static const std::string REPORTS_PATH;
    static const std::string ORDERS_PATH;
    static const std::string BUNDLE_NAME;
    static const std::string REPORT_NAME;
    static const std::string SCHEDULE_NAME;
    static const std::vector<std::vector<int>> compMap;
    static const std::vector<std::string> nameMap;
    static const std::vector<int> costMap;
    static const std::vector<int> cycleMap;
    int compPrice(std::string name);
};

const std::string Const::REPORTS_PATH =  "../reports/";
const std::string Const::ORDERS_PATH = "../orders/";
const std::string Const::BUNDLE_NAME = "orderbundle";
const std::string Const::REPORT_NAME = "report";
const std::string Const::SCHEDULE_NAME = "schedule";

Const::Const() {
    for (int i = 0; i < nameMap.size(); i++)
        COMP_PRICE_MAP.insert({nameMap[i], costMap[i]});
}

int Const::compPrice(std::string name) {
    return COMP_PRICE_MAP[name];
}
const std::vector<int> Const::cycleMap = {4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7 };

const std::vector<int> Const::costMap = {1000, 1500, 1000, 1500, 250, 250, 100, 200, 300, 400};

const std::vector<std::vector<int>> Const::compMap = {
        { 0, 4, 6, 8 },
        { 0, 4, 6, 9 },
        { 0, 4, 7, 8 },
        { 0, 4, 7, 9 },
        { 1, 4, 6, 8 },
        { 1, 4, 6, 9 },
        { 1, 4, 7, 8 },
        { 1, 4, 7, 9 },
        { 2, 5, 6, 8 },
        { 2, 5, 6, 9 },
        { 2, 5, 7, 9 },
        { 2, 5, 7, 8 },
        { 3, 5, 6, 8 },
        { 3, 5, 6, 9 },
        { 3, 5, 7, 8 },
        { 3, 5, 7, 9 }
};

const std::vector<std::string> Const::nameMap = {
        "Pintel CPU 3 GHz",
        "Pintel CPU 5 GHz",
        "IMD CPU 3GHz",
        "IMD CPU 5GHz",
        "Pintel motherboard",
        "IMD motherboard",
        "Memory 8 GB",
        "Memory 16 GB",
        "Hard disk 1TB",
        "Hard disk 2TB"
};

const int Const::MAX_CYCLES = 10000;

const int Const::CYCLE_COST = 100;

const int Const::CPU_DISC_REQ = 500;

const double Const::CPU_DISCOUNT = 0.18;

const double Const::CANCELLATION_PENALTY = 0.03;

const int Const::MAX_ORDER_QUANTITY = 30;

const int Const::MIN_PROFIT_RATE = 25;

const int Const::MAX_PROFIT_RATE = 75;

const int Const::MIN_ORDER_BUNDLE = 120;

const int Const::MAX_ORDER_BUNDLE = 200;


#endif /* CONSTANT_H_ */
