#pragma once
#include<iostream>
#include <list>

#include "Unit.h"
#include "Constant.h"
#include "Component.h"

class Product : public Unit {
private:
    std::array<Component,4> components_;
    void setCost();

public:
    Product(): Unit() {}
    Product(int pcId): Unit(pcId) { setCost(); }
    std::array<Component,4> getComponents() const;
};

void Product::setCost() {
    if (id_ < 0 || id_ > Const::cycleMap.size()) {
        std::cout <<"Product id is out of range!" << std::endl;
    } else {
        // Price of components
        for (int i = 0; i < 4; i++) {
            Component c(Const::compMap[id_][i]);
            cost_ += c.getCost();
            components_[i] = c;
        }

        // Price of cycles
        cost_ += Const::cycleMap[id_] * Const::CYCLE_COST;
    }
}

std::array<Component,4> Product::getComponents() const {
    return components_;
}
