#pragma once

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "Constant.h"
#include "ParseOrders.h"
#include "Utility.h"

class BundleGenerator {
private:
    std::ofstream outFile_;
    int numOrders_;
    int nextOrderId_;
    int lastOrderNum() {
        std::ifstream lastBundle (getLastBundlePath());
        return ParseOrders().lastOrderNum(lastBundle);
    }

public:
    BundleGenerator() {
        numOrders_ = std::rand() % (Const::MAX_ORDER_BUNDLE - Const::MIN_ORDER_BUNDLE) + Const::MIN_ORDER_BUNDLE;
        nextOrderId_ = (isPreviousBundle() ? lastOrderNum() + 1 : 1);
        outFile_.open(getNextBundlePath());
        if (outFile_.fail()) {
            std::cout << "input failed to open file.\n";
            exit(1);
        }
    }

    ~BundleGenerator() { }

    void operator()() {
        for (int i = 0; i < numOrders_; ++i) {
            outFile_ << "["
            << nextOrderId_
            << "," << (rand() % 15)
            << "," << (rand() % Const::MAX_ORDER_QUANTITY + 1)
            << "," << (rand() % (Const::MAX_PROFIT_RATE - Const::MIN_PROFIT_RATE) + Const::MIN_PROFIT_RATE)
            << "]\n";
            nextOrderId_++;
        }
    }

    static std::string getLastBundlePath() {
        std::size_t bunIdx = 1;
        std::string path = Const::ORDERS_PATH + Const::BUNDLE_NAME + ".txt";
        while (!util::fileExists(path)) {
            path = Const::ORDERS_PATH + Const::BUNDLE_NAME + std::to_string(bunIdx) + ".txt";
            bunIdx ++;
        }
        return path;
    }

    static int getLastBundleIdx() {
        std::size_t bunIdx = 0;
        std::string path = Const::ORDERS_PATH + Const::BUNDLE_NAME + ".txt";
        while (util::fileExists(path)) {
            bunIdx ++;
            path = Const::ORDERS_PATH + Const::BUNDLE_NAME + std::to_string(bunIdx) + ".txt";
        }
        return bunIdx;
    }

    std::string getNextBundlePath() {
        std::size_t bunIdx = 1;
        std::string path = Const::ORDERS_PATH + Const::BUNDLE_NAME + ".txt";
        while (util::fileExists(path)) {
            path = Const::ORDERS_PATH + Const::BUNDLE_NAME + std::to_string(bunIdx) + ".txt";
            bunIdx ++;
        }
        return path;
    }

    bool isPreviousBundle () {
        std::string path = Const::ORDERS_PATH + Const::BUNDLE_NAME + ".txt";
        return util::fileExists(path);
    }

};