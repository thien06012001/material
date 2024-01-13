#include <iostream>
#include <string>

using namespace std;
class Destination
{
    string name;
    int days;
    Destination *nextDestination = nullptr;

public:
    Destination(string nameVal = "", int daysVal = 0) : name(nameVal), days(daysVal) {}
    void setNextDestination(Destination *dest)
    {
        nextDestination = dest;
    }
    friend void printLinkedList(Destination *head);
    friend void deleteDestination(Destination *&head, Destination *&tail, Destination *delDest);
};
// Qa
void printLinkedList(Destination *head){
    Destination *temp = head;
    while(temp != nullptr) {
        cout<< temp->name << " : " << temp->days << " days" << endl;
        temp = temp->nextDestination;
    }
}
// Qb
void deleteDestination(Destination *&head, Destination *&tail, Destination *delDest) {
    if(delDest == head) {
        head = head->nextDestination;
    }
    else if(delDest == tail){
        Destination *temp = head;
        while(temp->nextDestination != tail) {
            temp = temp->nextDestination;
        }
        temp->nextDestination = nullptr;
        tail = temp;
    }
    else {
        Destination *temp = head;
        while (temp->nextDestination != delDest) {
            temp = temp->nextDestination;
        }
        temp->nextDestination = delDest->nextDestination;
    }
}
int main()
{
    Destination dest1("Dalat", 2), dest2("Nha Trang", 3), dest3("Da Nang", 2), dest4("Hue", 1), dest5("Hanoi", 3);
    Destination *head = &dest1;
    Destination *tail = &dest5;
    dest1.setNextDestination(&dest2);
    dest2.setNextDestination(&dest3);
    dest3.setNextDestination(&dest4);
    dest4.setNextDestination(&dest5);
    dest5.setNextDestination(nullptr);
    printLinkedList(head);
    deleteDestination(head, tail, &dest5);
    cout<< "After delete:" << endl;
    printLinkedList(head);
    return 0;
}