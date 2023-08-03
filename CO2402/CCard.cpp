#ifndef CCARD_H
#define CCARD_H
#include <iostream>
#include <string>
using namespace std;

class CCard {
private:
	int privateType;
	string privateName;
	int privatePower;

public:
	//Contructor
	CCard(int type, const string name, int power) :privateType(type), privateName(name), privatePower(power) {}


	int getType()const { return privateType; };
	const string& getName() const { return privateName; }
	int getPower() const { return privatePower; }


	virtual int getResilience() const {
		return 0; // Base class does not have resilience, return default value.
	}

	virtual void setResilience(int newResilience) {
	}

};
#endif 