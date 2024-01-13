#include <iostream>
#include <string>
#define ARRAY_SIZE 3
using namespace std;
class Customer
{
    string name;
    double expense;
    double bonus;
    Customer *next;

public:
    Customer(string nameVal = "", double expenseVal = 0) : name(nameVal), expense(expenseVal) {}
    void setNext(Customer *nextVal)
    {
        next = nextVal;
    }
    friend void printLinkedList(Customer *head);
    friend void largestExpense(Customer *head);
    friend void updateBonus(Customer *head);
};
// Qa
void printLinkedList(Customer *head)
{
    Customer *temp = head;
    while (temp != nullptr)
    {
        cout << temp->name << " (" << temp->expense << ")";
        if(temp->next != nullptr){
            cout << " -> " ;
        }
        temp = temp->next;
    }
     cout << endl;
};
// Qb
void largestExpense(Customer *head) {
    Customer *temp = head;
    Customer *largestExp = head;

    while(temp != nullptr) {
        if(largestExp->expense < temp->expense) {
            largestExp = temp;
        }
        temp = temp->next;
    }
    cout << "Customer with largest expense: " << largestExp->name<< endl;
}
// Qc
void updateBonus(Customer *head) {
    Customer *temp = head;
    Customer *temp1 = nullptr;
    cout << "All bonus: ";
    while(temp != nullptr) {
        temp1 = temp->next;
        if(temp->next == nullptr){
            break;
        }
        temp->bonus += temp1->expense * 0.05;
        while(temp1->next != nullptr) {
            temp->bonus += temp1->next->expense * 0.02;
            temp1 = temp1->next;
        }
        cout << temp->name << ": " << temp->bonus << " ";
        temp = temp->next;
    } 
}
int main()
{
    Customer customer1("Peter", 1000), customer2("John", 200), customer3("Harry", 1200), customer4("Luna", 400);
    Customer *head = &customer1;
    customer1.setNext(&customer2);
    customer2.setNext(&customer3);
    customer3.setNext(&customer4);
    customer4.setNext(nullptr);
    printLinkedList(head);
    largestExpense(head);
    updateBonus(head);
}