#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <iomanip>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::endl;
class Product
{
private:
    string name;
    double price;

public:
    Product(string name = "", double price = 0)
    {
        this->name = name;
        this->price = price;
    }

    // Getters and Setters
    string getName() const
    {
        return name;
    }

    void setName(string Name)
    {
        name = Name;
    }

    double getPrice() const
    {
        return price;
    }

    void setPrice(double Price)
    {
        price = Price;
    }

    void showInfo()
    {
        cout << name << ", $" << price << "\n";
    }

    friend class CoffeeShop;
};

class Receipt
{
private:
    int id;
    std::unordered_map<int, Product> boughtProducts;
    std::vector<double> subtotalTracker;
    double totalPrice;

public:
    Receipt(int id) : id(id), totalPrice(0.0) {}
    void addItem(Product &product, int quantity)
    {
        boughtProducts.insert(std::make_pair(quantity, product));
        subtotalTracker.push_back(product.getPrice() * quantity);
        this->totalPrice += product.getPrice() * quantity;
    }

    double findSmallestSubtotal()
    {
        double smallestSubtotal = subtotalTracker[0];
        for (int i = 0; i < subtotalTracker.size(); i++)
        {
            if (subtotalTracker[i] < smallestSubtotal)
            {
                smallestSubtotal = subtotalTracker[i];
            }
        }
        return smallestSubtotal;
    }

    int getTotalQuantity()
    {
        int totalQuantity = 0;
        for (auto item = boughtProducts.begin(); item != boughtProducts.end(); item++)
        {
            totalQuantity += item->first;
        }
        return totalQuantity;
    }

    void showInfo()
    {
        cout << endl;
        cout << "Receipt ID: " << id << "\n";
        cout << "Bought items: \n";
        int count = 1;
        for (auto item = boughtProducts.begin(); item != boughtProducts.end(); item++)
        {
            cout << count << ". Item: " << item->second.getName() << "\n";
            cout << "Quantity: " << item->first << "\n";
            cout << "Subtotal: $" << std::fixed << std::setprecision(2) << item->second.getPrice() * item->first << "\n";
            count++;
            cout << "\n";
        }

        cout << "========================\n";
        cout << "      GRAND TOTAL       \n";
        cout << "========================\n";
        cout << "Total items purchased: " << getTotalQuantity() << "\n";
        cout << "Lowest subtotal: $" << std::fixed << std::setprecision(2) << findSmallestSubtotal() << "\n";
        cout << "Total amount to be paid: $" << std::fixed << std::setprecision(2) << totalPrice << "\n";
    }

    friend class CoffeeShop;
};

class CoffeeShop
{
private:
    string name;
    vector<Product> sellingProducts;
    vector<Receipt> receipts;

public:
    // Constructor
    CoffeeShop(string name) : name(name) {}
    void addProduct(Product &product)
    {
        // Check if the product is already in the system
        for (int i = 0; i < sellingProducts.size(); i++)
        {
            if (sellingProducts[i].getName() == product.getName())
            {
                cout << "Product is already in the system\n";
                return;
            }
        }
        sellingProducts.push_back(product);
    }

    void showInfo()
    {
        cout << "Welcome to " << name << "\n\n";
        cout << "List of Coffee available\n";
        cout << "========================\n";
        for (int i = 0; i < sellingProducts.size(); i++)
        {
            cout << i + 1 << ". ";
            sellingProducts[i].showInfo();
        }
        cout << "========================\n";
    }

    void addReceipt(Receipt &receipt)
    {
        receipts.push_back(receipt);
    }

    void createOrder()
    {
        Receipt receipt = Receipt(receipts.size() + 1);
        while (true)
        {
            string item = getValidItem();
            if (item == "Q")
            {
                break;
            }
            else
            {
                int quantity = 0;
                cout << "Enter quantity: ";
                cin >> quantity;
                cin.ignore();
                Product myProduct = findProduct(item);
                receipt.addItem(myProduct, quantity);
            }
        }
        addReceipt(receipt);

        // Print bill info
        receipt.showInfo();
    }

    bool isItemExist(string item)
    {
        for (int i = 0; i < sellingProducts.size(); i++)
        {
            if (sellingProducts[i].getName() == item)
            {
                return true;
            }
        }
        return false;
    }

    string getValidItem()
    {
        // Get the item, loop until the item is found in the system
        string item;
        do
        {
            cout << "Enter item ('Q' to quit): ";
            getline(cin, item);
            if (item == "Q")
            {
                return item;
            }
            else if (isItemExist(item))
            {
                return item;
            }
            else
            {
                cout << "Item not found. Try again!!!\n";
            }
        } while (true);
    }

    Product &findProduct(string name)
    {
        // Loop through the sellingProducts vector to find the product
        for (Product &p : sellingProducts)
        {
            if (p.getName() == name)
            {
                return p;
            }
        }
    }
};

int main()
{
    // Create a coffee shop
    CoffeeShop coffeeShop("Coffee Shop 1");
    Product p1("Latte", 4.50), p2("Americano", 3.00), p3("Flat White", 4.80);

    // Add products to the coffee shop
    coffeeShop.addProduct(p1);
    coffeeShop.addProduct(p2);
    coffeeShop.addProduct(p3);

    // Show the coffee shop's information
    coffeeShop.showInfo();
    coffeeShop.createOrder();

    return 0;
}