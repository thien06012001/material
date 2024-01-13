#include <iostream>
#include <string>
using namespace std;

class Employee
{
protected:
    string name;
    double salary;

public:
    Employee(string nameVal = "", double salaryVal = 0) : name(nameVal), salary(salaryVal)
    {
    }
    void showInfo()
    {
        cout << "Name: " << name << endl;
        cout << "Salary: " << salary << endl;
    }
};
class Manager : public Employee
{
    double allowance;

public:
    Manager(string nameVal = "", double salaryVal = 0, double allowanceVal = 0) : Employee(nameVal, salaryVal), allowance(allowanceVal)
    {
    }
    void showInfo()
    {
        Employee::showInfo();
        cout << "Allowance: " << allowance << endl;
    }
    double getTotalIncome()
    {
        return salary + allowance;
    }
};
int main()
{
    Manager *arr = new (std::nothrow) Manager[5]{
        Manager("A", 1000, 100),
        Manager("B", 2000, 200),
        Manager("C", 3000, 300),
        Manager("D", 4000, 400),
        Manager("E", 5000, 500)};
    if (arr == nullptr)
    {
        cerr << "Fail to request memory allocation \n";
        return -1;
    }
    double incomeSum = 0;
    for (int i = 0; i < 5; i++)
    {
        incomeSum += (arr[i].getTotalIncome());
    }
    double averageIncome = incomeSum / 5;
    cout << "Average income: " << averageIncome << endl;
    delete[] arr;
    return 0;
}