#include <iostream>
#include <string>
#define ARRAY_SIZE 3
using namespace std;
class Vehicle
{
protected:
    string name;
    int year;

public:
    Vehicle(string nameVal = "", int yearVal = 0) : name(nameVal), year(yearVal) {}
    void showInfo()
    {
        cout << "Name: " << name << ", year = " << year << "\n";
    }
    int getYear() { return this->year; }
};
class Car : public Vehicle
{
    int plateNumber;

public:
    Car(string nameVal = "", int yearVal = 0, int plateNumberVal = 0) : Vehicle(nameVal, yearVal), plateNumber(plateNumberVal) {}
    void showInfo()
    {
        Vehicle::showInfo();
        cout << "Plate number: " << plateNumber << "\n";
    }
};
int main()
{
    Car *carArr = new (std::nothrow) Car[ARRAY_SIZE]{
        Car("A", 2000, 100),
        Car("B", 2001, 200),
        Car("C", 2002, 300)};
    if (carArr == nullptr)
    {
        cerr << "Fail to request memory allocation \n";
        return -1;
    }
    
    Car *oldestCar = carArr;
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (carArr[i].getYear() < oldestCar->getYear())
        {
            oldestCar = &carArr[i];
        }
    }
    
    cout << "Oldest car: \n";
    oldestCar->showInfo();
    delete[] carArr;
    return 0;
}