#pragma once

#include <vector>
#include <iostream>
#include <type_traits>
#include <typeinfo>

struct util {
    template<typename numT>
    static std::string numWCommas(const numT &value, int precision = 2) {
        // Takes in any numerical value, and returns comma separated string
        static_assert(std::is_arithmetic<numT>::value, "Type must be numerical");
        std::string numWithComms = std::to_string(value);
        std::size_t strSize = numWithComms.size();

        int insertPos = strSize - 3;

        //Check for any dot, keep 2 decimals
        int found = numWithComms.find('.');
        if (found != std::string::npos) {
            if (precision > 0) precision++;
            numWithComms.erase(numWithComms.begin() + (found + precision), numWithComms.end());
            insertPos = numWithComms.size() - (3 + precision);
        }

        while (insertPos > 0) {
            numWithComms.insert(insertPos, ",");
            if (insertPos > 3) insertPos -= 3;
            else break;
        }
        return numWithComms;
    }

    static bool fileExists(const std::string &path) {
        std::ifstream f(path.c_str());
        return f.good();
    }


};
