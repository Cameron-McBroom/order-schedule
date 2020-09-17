#pragma once

class Unit {
protected:
	int id_;
	int cost_;
public:
	Unit() : id_(-1), cost_(0) {} // Id for un-init product is -1

	Unit(int id): id_(id), cost_(0) {}

	Unit(int id, int cost) : id_(id), cost_(cost) {}

	int getId() {
		return id_;
	}

	int getCost() const {
		return cost_;
	}
};

