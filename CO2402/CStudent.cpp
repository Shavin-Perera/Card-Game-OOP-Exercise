#include <iostream>
#include <string>
#include "CCard.cpp"
using namespace std;
//derived CCard class
class CStudent : public CCard {
private:
    int privateResilience;

public:
    CStudent(int type, string name, int power, int resilience) : CCard(type, name, power), privateResilience(resilience) {}

    //int getResilience() { return privateResilience; }
    int getResilience() const override {
        return privateResilience;
    }
    void setResilience(int newResilience) override {
        privateResilience = newResilience;
    }
};