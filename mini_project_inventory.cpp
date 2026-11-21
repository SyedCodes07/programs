#include <iostream>
#include <string>
#include <cstring>
using namespace std;
 
// Weeks 1-6 integrated task: inventory item management
class Item {
    char *name;            // heap-allocated name (Week 4)
    int qty;
    double price;
    static int created;    // static counter of objects created (Week 5)
public:
    // default arguments (Week 2) and parameterized constructor (Week 3/4)
    Item(const char *n = "unnamed", int q = 0, double p = 0.0) : qty(q), price(p) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        ++created;
    }
    // deep copy constructor (Week 4)
    Item(const Item &o) : qty(o.qty), price(o.price) {
        name = new char[strlen(o.name) + 1];
        strcpy(name, o.name);
        ++created;
    }
    // deep-copy assignment operator with self-assignment guard (Week 6)
    Item& operator=(const Item &o) {
        if (this != &o) {
            delete[] name;
            name = new char[strlen(o.name) + 1];
            strcpy(name, o.name);
            qty = o.qty;
            price = o.price;
        }
        return *this;
    }
    ~Item() { delete[] name; }
 
    // member operator + combines quantities of two items (Week 6)
    Item operator+(const Item &o) const {
        return Item(name, qty + o.qty, price);
    }
    bool operator==(const Item &o) const { return strcmp(name, o.name) == 0; }
 
    int getQty() const { return qty; }
    double value() const { return qty * price; }
    void setQty(int q) { if (q >= 0) qty = q; }   // validated setter (Week 3)
 
    static int totalCreated() { return created; } // static function (Week 5)
 
    // friend operator<< so an item prints itself (Week 5/6)
    friend ostream& operator<<(ostream &os, const Item &it) {
        os << it.name << " | qty " << it.qty << " | price " << it.price;
        return os;
    }
};
int Item::created = 0;   // definition of the static member (Week 5)
 
// inline helper with default argument (Week 2)
inline double gstAmount(double amount, double rate = 0.18) { return amount * rate; }
 
// overloaded functions (Week 2)
void show(const string &label) { cout << "[" << label << "]\n"; }
void show(int value)           { cout << "value: " << value << "\n"; }
 
// pass by reference modifies the caller's object (Week 1/3)
void restock(Item &it, int n) { it.setQty(it.getQty() + n); }
 
int main() {
    Item pen("Pen", 10, 5.0);
    Item book("Notebook", 4, 40.0);
 
    show(string("Initial stock"));
    cout << pen << "\n" << book << "\n";
 
    restock(pen, 15);                       // by reference: pen changes
    show(string("After restock"));
    cout << pen << "\n";
 
    Item combined = pen + book;             // operator+ (name taken from pen)
    show(string("Combined item (pen + notebook quantities)"));
    cout << combined << "\n";
 
    Item copy = pen;                        // deep copy constructor
    Item other;
    other = book;                           // deep-copy assignment
    show(string("Copy and assignment"));
    cout << copy << "\n" << other << "\n";
    cout << "Pen == copy? " << (pen == copy ? "yes" : "no") << "\n";
 
    show(string("Value with GST (default 18%)"));
    cout << "Pen value = " << pen.value()
         << ", GST = " << gstAmount(pen.value()) << "\n";
    cout << "Pen value GST at 5% = " << gstAmount(pen.value(), 0.05) << "\n";
 
    show(42);                               // overload selected by argument type
    show(string("Objects created so far"));
    show(Item::totalCreated());
    return 0;
}
