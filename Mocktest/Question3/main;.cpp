#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define DISCOUNT_RATE 0.05
class Product
{
    string name;
    double price;

public:
    Product(string nameVal = "", double priceVal = 0) : name(nameVal), price(priceVal) {}
     //overload operator == for comparision
    bool operator == (Product another){
        return (this->name == another.name && this->price == another.price);
    }
    void showInfo(){ cout << "\t" << name << ", price = " << price << "\n";}
    friend class Shop;
    friend class CustomerAcc;
};
class Shop
{
    string name;
    vector<Product> sellingList;

public:
    Shop(string nameVal = "", vector<Product> sellingListVal = {}) : name(nameVal), sellingList(sellingListVal) {}
    void showInfo(){
        cout << "\nSHOP: " << name << ", selling items: \n";
        for (Product pd: sellingList){
            pd.showInfo();
        }
    }
};

class Order
{
    int orderId;
    vector<Product> boughtList; // list of bought products
    double expense;
    public:
        Order(int orderID, vector<Product> boughtList = {}, double expense = 0)
        : orderId(orderID), boughtList(boughtList), expense(expense){}
     void showInfo(){
        cout << "OrderID: " << orderId << ". Bought list: \n";
        for (Product pd: boughtList){
            pd.showInfo();
        }
        cout << "\tTotal expense = " << expense << "\n";
    }
    friend class CustomerAcc;
};
class CustomerAcc
{
    string name;
    bool isGoldAcc;
    vector<Order> orderList;
    public:
    CustomerAcc(string nameVal = "", bool isGoldAccVal = false, vector<Order> orderListVal = {}) : name(nameVal), isGoldAcc(isGoldAccVal), orderList(orderListVal) {}

    void buyProducts(vector<Product> pdList) {
        double totalExpense = 0;
        for(Product pd: pdList) {
            if (isGoldAcc){ //Gold acc: discount 5%
                totalExpense += pd.price* (1 - DISCOUNT_RATE);
            } else { //normal acc: no discount
                totalExpense += pd.price;
            }
        }
       
        int orderID = orderList.size() + 1;
        Order newOrder(orderID, pdList, totalExpense);
        orderList.push_back( newOrder );
    }
    void showInfo(){
        cout << "\nCUSTOMER: " << name 
             << ", account type = " << (isGoldAcc ? "Gold": "Normal") 
             << ", discountRate = " << (isGoldAcc ? DISCOUNT_RATE : 0) << "\n";
        for (Order od: orderList){
            od.showInfo();
        }
    }
};
int main() {
    // Create a shop and add products
    Product pd1("Shoe", 20), pd2("Car", 1000), pd3("Book", 10);
    Shop shop1("Shop1", {pd1, pd2, pd3});
    shop1.showInfo();
    
    //Test normal and gold accounts
    CustomerAcc acc1("NormalAcc", 0);
    acc1.buyProducts({pd1}); //first order
    acc1.buyProducts({pd1, pd2, pd3}); //second order
    acc1.showInfo();

    CustomerAcc acc2("GoldAcc", 1); //gold account
    acc2.buyProducts({pd1});
    acc2.buyProducts({pd1, pd2, pd3});
    acc2.showInfo();

    return 0;
}
