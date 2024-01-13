#include <iostream>
#include <string>
#include <vector>
#define ARRAY_SIZE 3
using namespace std;
class Product
{
    string name;
    int id;
    double price;

public:
    Product(string nameVal = "", int idVal = 0, double priceVal = 0) : name(nameVal), id(idVal), price(priceVal) {}
    void showInfo()
    {
        cout << "Name: " << name << ", id = " << id << ", price = " << price << "\n";
    }
    friend class Shop;
    friend class Customer;
};
class Bill
{
    int billId;
    vector<Product> boughtList;
    double expense;

public:
    Bill(int billIdVal = 0, vector<Product> boughtListVal = {}, double expenseVal = 0) : billId(billIdVal), boughtList(boughtListVal), expense(expenseVal) {}
    friend class Customer;
    friend class Shop;
};
class Customer
{
    string name;
    int id;
    vector<Bill> billList;

public:
    Customer(string nameVal = "", int idVal = 0, vector<Bill> billListVal = {}) : name(nameVal), id(idVal), billList(billListVal) {}
    void buyProducts(vector<Product> pdList)
    {
        double totalExpense = 0;
        // Calculating total expense
        for (Product &pd : pdList)
        {
            totalExpense += pd.price;
        }

        // Create a bill object and add it to the billList of the customer
        Bill bill(billList.size() + 1, pdList, totalExpense);
        billList.push_back(bill);
        // Update shop's total revenue
    }

    void printBills()
    {
        for (Bill &bill : billList)
        {
            cout << "Bill id: " << bill.billId << endl;
            cout << "Bill expense: " << bill.expense << endl;
            cout << "Bill bought list: " << endl;
            for (Product pd : bill.boughtList)
            {
                pd.showInfo();
            }
        }
    }
    friend class Shop;
};
class Shop
{
    string name;
    double totalRevenue;
    vector<Product> sellingList;
    vector<Customer *> customerList;
    vector<Bill> billList;

public:
    Shop(string nameVal = "", vector<Product> sellingListVal = {}) : name(nameVal), sellingList(sellingListVal) {}
    void addProduct(Product &pd)
    {
        for (Product &shopPd : sellingList)
        {
            if (pd.name == shopPd.name && pd.id == shopPd.id)
            {
                cout << "Product already exists in the shop\n";
                return;
            }
        }
        sellingList.push_back(pd);
    }
    void addUser(Customer &customer)
    {
        for (Customer *&shopCustomer : customerList)
        {
            if (customer.id == shopCustomer->id && customer.name == shopCustomer->name)
            {
                cout << "Customer already exists in the shop\n";
                return;
            }
        }
        customerList.push_back(&customer);
    }
    void displayRevenue()
    {
        double Revenue = 0;
        for (Customer *&customer : customerList)
        {
            // for (Bill &bill : customer.billList)
            // {
            //     Revenue += bill.expense;
            // }
            customer->printBills();
        }
        cout << "Total revenue: " << Revenue << endl;
    }

    void showInfo()
    {
        cout << "Shop name: " << name << endl;
        displayRevenue();
        cout << "Selling list: " << endl;
        for (Product &pd : sellingList)
        {
            pd.showInfo();
        }
        cout << "Customer list: " << endl;
        for (Customer *&customer : customerList)
        {
            cout << "Customer name: " << customer->name << endl;
            cout << "Customer id: " << customer->id << endl;
            cout << "Customer bill list: " << endl;
            for (Bill &bill : customer->billList)
            {
                cout << "Bill id: " << bill.billId << endl;
                cout << "Bill expense: " << bill.expense << endl;
                cout << "Bill bought list: " << endl;
                for (Product &pd : bill.boughtList)
                {
                    pd.showInfo();
                }
            }
        }
    }
};

int main()
{
    Shop shop("ABC");
    Product pd1("A", 1, 100), pd2("B", 2, 200), pd3("C", 3, 300);
    shop.addProduct(pd1);
    shop.addProduct(pd2);
    shop.addProduct(pd3);
    Customer cus1("D", 4), cus2("E", 5);

    shop.addUser(cus1);
    cus1.buyProducts({pd1, pd2});

    shop.showInfo();
}