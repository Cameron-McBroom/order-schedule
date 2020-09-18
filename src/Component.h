#pragma once
#include<iostream>
#include <vector>
#include "Unit.h"
#include "Constant.h"

class Component : public Unit {
private:
	void setCost();

public:
    Component(): Unit() {}
	Component(int cid): Unit(cid) { setCost(); }
	std::string getName() const;
};

void Component::setCost() {
    if (id_ < 0 || id_ > Const::nameMap.size())
        std::cout <<"Component Id is out of range!" << std::endl;
    else
        cost_ = Const::costMap[id_];
}

std::string Component::getName() const {
	if (id_ < 0 || id_ > Const::nameMap.size()) {
		std::cout << "Component Id has not been initialized!" << std::endl;
		return "";
	} else {
		return Const::nameMap[id_];
	}
}

