#include <iostream>
#include <string>
using namespace std;
class Broker
{
    string name;
    double buyPrice;
    Broker *nextBuy;

public:
    Broker(string nameVal = "", double buyPriceVal = 0) : name(nameVal), buyPrice(buyPriceVal) {}
    void setNextBuyer(Broker *next) { nextBuy = next; }
    Broker *getNextBuyer() { return nextBuy; };
    string getName() { return this->name; }
    double getBuyPrice() { return this->buyPrice; }
    void showInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Buy price: " << buyPrice << endl;
    }
};
int main()
{
    Broker broker1("David", 800), broker2("John", 1000), broker3("Peter", 1200),
        broker4("Luna", 1800), broker5("Sophia", 3500);
    Broker *head = &broker1;
    broker1.setNextBuyer(&broker2);
    broker2.setNextBuyer(&broker3);
    broker3.setNextBuyer(&broker4);
    broker4.setNextBuyer(&broker5);
    broker5.setNextBuyer(nullptr);
    Broker *temp = head;
    while (temp != nullptr)
    {
        if (temp == head)
        {
            cout << temp->getName() << ": bought the house for $800" << endl;
        }
        else
        {
            cout << temp->getName() << ": " << temp->getBuyPrice() << endl;
        }
        if (temp->getNextBuyer() != nullptr)
        {
            cout << temp->getName() << " --> ";
        }
        temp = temp->getNextBuyer();
    }
    Broker *minTemp = head;
    double minProfit = minTemp->getNextBuyer()->getBuyPrice() - minTemp->getBuyPrice();
    Broker *minBroker = head;
    while (temp != nullptr)
    {
        if (minTemp->getNextBuyer() != nullptr)
        {
            int profit = (minTemp->getNextBuyer()->getBuyPrice()) - minTemp->getBuyPrice();
            if (profit < minProfit)
            {
                minProfit = profit;
                minBroker = minTemp;
            }
        }
        minTemp = minTemp->getNextBuyer();
    }
    if (minBroker != nullptr)
    {
        cout << "\nThe broker with min profit: \n"
             << "> name: ";
        minBroker->showInfo();
    }
}