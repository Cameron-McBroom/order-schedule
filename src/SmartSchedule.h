#pragma once

#include "Schedule.h"

class SmartSchedule : public Schedule {
private:
    std::unordered_map<std::string, int> allComponents_;
    std::unordered_map<std::string, int> CPUExtraVal_;
    void weightCPUValue() {
        for (const auto &comp: allComponents_) {
            // give larger values based on number of components > 500 AND price of CPU
            if (comp.first.find("CPU") != std::string::npos && comp.second > Const::CPU_DISC_REQ+100)
                CPUExtraVal_[comp.first] =(
                        (comp.second - Const::CPU_DISC_REQ) *
                        (Const().compPrice(comp.first) * Const::CPU_DISCOUNT)* 1.3);
        }
    }

public:
    SmartSchedule(std::istream &orderBundle) : Schedule(orderBundle)
    {
        // map out all the components that can possible be made if every order was fulfilled
        for (auto &order: ordersReceived_) {
            for (int i = 0; i < 4; i++)
                allComponents_[order.getComponentName(i)] += order.getQuantity();
        }

        // weight how much each CPU is worth
        weightCPUValue();

        // Loop through each order and add the extra profit based on CPU extra val
        for (auto &order: ordersReceived_) {
            const auto CPUUsedMap = order.getCPUsUsed();
            double extraVal = 0;
            for (const auto &CPU: CPUUsedMap){
                extraVal += CPUExtraVal_[CPU.first];
            }
            order += extraVal;
       }

        // Sort orders by total profitability
        ordersReceived_ = QuickSort<Order>(std::move(ordersReceived_))();

        // Remove the extra profit to ensure results are not skewed
        for (auto &order: ordersReceived_) {
            const auto CPUUsedMap = order.getCPUsUsed();
            double extraVal = 0;
            for (const auto &CPU: CPUUsedMap){
                extraVal += CPUExtraVal_[CPU.first];
            }
            order -= extraVal;
        }
    }

    void createSchedule() {
        for (const auto &order: ordersReceived_) {
            if (totalCyclesUsed_ < Const::MAX_CYCLES && totalCyclesUsed_ + order.getCycles() <= Const::MAX_CYCLES) {
                ordersSatisfied_.push_back(order);
                totalCyclesUsed_ += order.getCycles();
                PCsProduced_[order.getPCId()] += order.getQuantity();

                // Loop through components used and add to component map
                for (int i = 0; i < 4; i++)
                    componentsProduced_[order.getComponentName(i)] += order.getQuantity();

                // Add profit & rev for each order
                totalRevenue_ += order.getRevenue();
                grossProfit_ += order.getProfitTotal();
                totalPCCost_ += order.getProductCost();

            } else {
                ordersCancelled_.push_back(order);
                totalCancelCost_ += order.getCancelCost();
            }
        }
        addDiscountToNetProfit();
    }
};
