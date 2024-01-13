#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class Node
{
    int value;
    Node *next = nullptr;
    Node *prev = nullptr;

public:
    Node(int value = 0)
        : value(value) {}

    void setNext(Node *next)
    {
        this->next = next;
    }
    void setPrev(Node *prev)
    {
        this->prev = prev;
    }
    void linkNextNode(Node *nextNode)
    {
        next = nextNode;
        if (nextNode != nullptr)
        {
            nextNode->prev = this; // link backward from nextNode
        }
    }
     //function to link to the previous node  
    void linkPrevNode(Node *prevNode){
        prev = prevNode;
        if (prevNode != nullptr) {
            prevNode->next = this; //link forward from nextNode
        }
    }
    friend void forward(Node *head);
    friend void backward(Node *tail);
    friend void insertNode(Node *&head, Node *&tail, Node *priorNode, Node *newNode);
    friend void deleteNode(Node *&head, Node *&tail, Node *delNote);
    friend void deleteNodeDouble(Node *&head, Node *&tail, Node *delNode);
     friend void swapNodes(Node *&headNode, Node *&tailNode, Node *nodeA, Node *nodeB);
};
// Qa
void forward(Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->value << " --> ";
        temp = temp->next;
    }
    cout << endl;
}
void backward(Node *tail)
{
    Node *temp = tail;
    while (temp != nullptr)
    {
        cout << temp->value << " --> ";
        temp = temp->prev;
    }
    cout << endl;
}
// Qb
void insertNode(Node *&head, Node *&tail, Node *priorNode, Node *newNode)
{
    if (priorNode == nullptr)
    { // Inserting at the beginning
        // Connect newNode to the current head
        newNode->linkNextNode(head);

        // the newNode become the new head
        head = newNode;
    }
    else if (priorNode == tail)
    { // Inserting at the end
        // Connect tailNode to the newNode
        tail->linkNextNode(newNode);

        // the newNode become the new tail
        tail = newNode;
    }
    else
    { // Inserting at the middle
        // Connect newNode to the node after the priorNode
        newNode->linkNextNode(priorNode->next);

        // Connect priorNode to the newNode
        priorNode->linkNextNode(newNode);
    }
}
// Single linked list delete
void deleteNode(Node *&head, Node *&tail, Node *delNote)
{
    if (delNote == head)
    {
        head = head->next;
        // delete delNote;
    }
    else if (delNote == tail)
    {
        Node *temp = head;
        while (temp->next != tail)
        {
            temp = temp->next;
        }
        temp->next = nullptr;
        // delete tail;
        tail = temp;
    }
    else
    {
        Node *temp = head;
        while (temp->next != delNote)
        {
            temp = temp->next;
        }
        temp->next = delNote->next;
        // delete delNote;
    }
}
// double linked list delete
void deleteNodeDouble(Node *&head, Node *&tail, Node *delNode)
{
    if (delNode == nullptr)
    {
        std::cerr << "Cannot delete a null node.\n";
        return;
    }

    if (delNode == head)
    {
        head = head->next;
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
        // delete delNode;

        // If the list becomes empty after deletion, update the tail to null
        if (head == nullptr)
        {
            tail = nullptr;
        }
    }
    else if (delNode == tail)
    {
        tail = tail->prev;
        if (tail != nullptr)
        {
            tail->next = nullptr;
        }
        // delete delNode;
    }
    else
    {
        delNode->prev->next = delNode->next;
        delNode->next->prev = delNode->prev;
        // delete delNode;
    }
}
void swapNodes(Node *&headNode, Node *&tailNode, Node *nodeA, Node *nodeB){
    //store all values of NodeB first (since its values will be changed)
    Node temp = *nodeB;

    //A stands before B --> after swapping, B will stand before A
    if (nodeB->prev == nodeA) { 
        nodeB->linkPrevNode(nodeA->prev);  //second way:  (nodeA->prev)->linkNextNode(nodeB); 
        nodeB->linkNextNode(nodeA);
        nodeA->linkNextNode(temp.next);

    //B stands before A --> after swapping, A will stand before B
    } else if (nodeB->next == nodeA) {
        nodeB->linkNextNode(nodeA->next);
        nodeB->linkPrevNode(nodeA);
        nodeA->linkPrevNode(temp.prev);

    } else { //Normal case
        //Connect B with next node of A
        nodeB->linkNextNode(nodeA->next);
        //Connect B with previous node of A
        nodeB->linkPrevNode(nodeA->prev);

        //Connect A with next node of B
        nodeA->linkNextNode(temp.next);
        //Connect A with previous node of B
        nodeA->linkPrevNode(temp.prev);
    }

    //Update the head and the tail if A or B is head/ tail
    headNode =  (headNode == nodeA) ? nodeB :  
                (headNode == nodeB) ? nodeA : headNode;

    tailNode =  (tailNode == nodeA) ? nodeB :
                (tailNode == nodeB) ? nodeA : tailNode;
}
int main()
{
    Node node1(8), node2(5), node3(3), node4(6), node5(100), node6(200);
    Node *head = &node1;
    Node *tail = &node4;
    node1.setNext(&node2);
    node2.setPrev(&node1);
    node2.setNext(&node3);
    node3.setPrev(&node2);
    node3.setNext(&node4);
    node4.setPrev(&node3);
    forward(head);
    backward(tail);
    insertNode(head, tail, nullptr, &node5);
    insertNode(head, tail, &node3, &node6);
    forward(head);
    backward(tail);
    deleteNodeDouble(head, tail, &node4);
    forward(head);
    backward(tail);
}