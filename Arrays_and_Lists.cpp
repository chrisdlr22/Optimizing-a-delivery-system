//Christian De La Rosa 
//Part 1 
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>
using namespace std;

// Struct to represent delivery orders 
struct myOrders {
    string id, dest; // Order ID i.e., ORD1 and Destinations i.e., Location A
    int prior;       // Priorities (1-5)

    // Constructor with default values 
    myOrders(string orderId = "", string orderDest = "", int orderPrior = 0)
        : id(orderId), dest(orderDest), prior(orderPrior) {}
};

// Class for array-based order management 
class myOrderArray {
private:
    static const int MAX_ORDERS = 50;
    myOrders orders[MAX_ORDERS];
    int size;

public:
    myOrderArray() : size(0) {}

    void addMyOrder(const string& id, const string& dest, int prior) {
        if (size >= MAX_ORDERS) {
            throw overflow_error("The array is full. Cannot add more orders.");
        }
        orders[size++] = myOrders(id, dest, prior);
    }

    void displayMyOrder() const {
        if (size == 0) {
            cout << "There are no orders to display.\n";
            return;
        }
        for (int i = 0; i < size; ++i) {
            cout << "Order ID: " << orders[i].id << ", Destination: " << orders[i].dest
                << ", Priority: " << orders[i].prior << endl;
        }
    }

    void searchMyOrder(const string& id) const {
        for (int i = 0; i < size; ++i) {
            if (orders[i].id == id) {
                cout << "Order found: ID: " << orders[i].id << ", Destination: " << orders[i].dest
                    << ", Priority: " << orders[i].prior << endl;
                return;
            }
        }
        cout << "Order ID " << id << " not found.\n";
    }
};

// Node for a singly linked list
struct Node {
    myOrders data;
    Node* next;

    Node(const myOrders& order) : data(order), next(nullptr) {}
};

// Class for singly linked list management
class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addOrder(const myOrders& order) {
        Node* newNode = new Node(order);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void displayOrders() const {
        if (!head) {
            cout << "Your list is empty.\n";
            return;
        }
        Node* temp = head;
        while (temp) {
            cout << "Order ID: " << temp->data.id << ", Destination: "
                << temp->data.dest << ", Priority: " << temp->data.prior << endl;
            temp = temp->next;
        }
    }

    void searchOrder(const string& id) const {
        Node* temp = head;
        while (temp) {
            if (temp->data.id == id) {
                cout << "Order found: ID: " << temp->data.id << ", Destination: " << temp->data.dest
                    << ", Priority: " << temp->data.prior << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "Order ID " << id << " not found.\n";
    }
};

// Node for a doubly linked list
struct DNode {
    myOrders data;
    DNode* next;
    DNode* prev;

    DNode(const myOrders& order) : data(order), next(nullptr), prev(nullptr) {}
};

// Class for doubly linked list management
class DoublyLinkedList {
private:
    DNode* head;

public:
    DoublyLinkedList() : head(nullptr) {}

    ~DoublyLinkedList() {
        while (head) {
            DNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
    // Order Add
    void addOrder(const myOrders& order) {
        DNode* newNode = new DNode(order);
        if (!head) {
            head = newNode;
            return;
        }
        DNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    //Display order function
    void displayOrders() const {
        if (!head) {
            cout << "Your doubly linked list is empty. :(\n";
            return;
        }
        DNode* temp = head;
        while (temp) {
            cout << "Order ID: " << temp->data.id << ", Destination: "
                << temp->data.dest << ", Priority: " << temp->data.prior << endl;
            temp = temp->next;
        }
    }
    // function removes orders 
    void removeOrder(const string& id) {
        DNode* temp = head;
        while (temp && temp->data.id != id) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Order ID " << id << " not found.\n";
            return;
        }
        if (temp->prev) {
            temp->prev->next = temp->next;
        }
        else {
            head = temp->next;
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        cout << "Removed Order: ID: " << temp->data.id << ", Destination: " << temp->data.dest
            << ", Priority: " << temp->data.prior << endl;
        delete temp;
    }

    void traverseReverse() const {
        if (!head) {
            cout << "Your list is empty. ;(\n";
            return;
        }
        DNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        while (temp) {
            cout << "Order ID: " << temp->data.id << ", Destination: "
                << temp->data.dest << ", Priority: " << temp->data.prior << endl;
            temp = temp->prev;
        }
    }
    // Function to update priority 
    void updatePriority(const string& id, int newPriority) {
        DNode* temp = head;
        while (temp && temp->data.id != id) {
            temp = temp->next;
        }
        if (!temp) {
            cout << "Order ID " << id << " not found.\n";
            return;
        }
        temp->data.prior = newPriority;
        cout << "Updated Priority for Order ID: " << id << " to " << newPriority << endl;
    }
};

// Skip list node
struct SkipNode {
    myOrders data;
    vector<SkipNode*> forward;

    SkipNode(const myOrders& order, int level) : data(order), forward(level + 1, nullptr) {}
};

// Skip list class
class SkipList {
private:
    SkipNode* head;
    int maxLevel;
    int currentLevel;

    int randomLevel() {
        int level = 0;
        while (rand() % 2 && level < maxLevel) {
            level++;
        }
        return level;
    }
    //Create a skip list class
public:
    SkipList(int maxLvl = 5) : maxLevel(maxLvl), currentLevel(0) {
        head = new SkipNode(myOrders(), maxLevel);
    }

    ~SkipList() {
        SkipNode* node = head;
        while (node) {
            SkipNode* temp = node;
            node = node->forward[0];
            delete temp;
        }
    }
    //Add order fuctions
    void addOrder(const myOrders& order) {
        vector<SkipNode*> update(maxLevel + 1, nullptr);
        SkipNode* current = head;

        for (int i = currentLevel; i >= 0; --i) {
            while (current->forward[i] && current->forward[i]->data.id < order.id) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        // Creating random levels for skip lists
        int level = randomLevel();
        if (level > currentLevel) {
            for (int i = currentLevel + 1; i <= level; ++i) {
                update[i] = head;
            }
            currentLevel = level;
        }
        // Updates previous nodes and new nodes 
        SkipNode* newNode = new SkipNode(order, level);
        for (int i = 0; i <= level; ++i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
    // Displays skip list orders
    void displayOrders() const {
        SkipNode* current = head->forward[0];
        while (current) {
            cout << "Order ID: " << current->data.id << ", Destination: " << current->data.dest
                << ", Priority: " << current->data.prior << endl;
            current = current->forward[0];
        }
    }
    //Displays search orders 
    void searchOrder(const string& id) const {
        SkipNode* current = head;
        for (int i = currentLevel; i >= 0; --i) {
            while (current->forward[i] && current->forward[i]->data.id < id) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        if (current && current->data.id == id) {
            cout << "Order found: ID: " << current->data.id << ", Destination: " << current->data.dest
                << ", Priority: " << current->data.prior << endl;
        }
        else {
            cout << "Order ID " << id << " not found.\n";
        }
    }
    // Removes the order 
    void removeOrder(const string& id) {
        vector<SkipNode*> update(maxLevel + 1, nullptr);
        SkipNode* current = head;

        for (int i = currentLevel; i >= 0; --i) {
            while (current->forward[i] && current->forward[i]->data.id < id) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];
        if (current && current->data.id == id) {
            for (int i = 0; i <= currentLevel; ++i) {
                if (update[i]->forward[i] != current) {
                    break;
                }
                update[i]->forward[i] = current->forward[i];
            }
            while (currentLevel > 0 && !head->forward[currentLevel]) {
                currentLevel--;
            }
            cout << "Removed Order: ID: " << current->data.id << ", Destination: " << current->data.dest
                << ", Priority: " << current->data.prior << endl;
            delete current;
        }
        else {
            cout << "Order ID " << id << " not found. :(\n"; // Prints if the order doesn't exist 
        }
    }
};

// Main function
int main() {
    srand(time(0));

    myOrderArray arrayOrders;
    SinglyLinkedList singlyOrders;
    DoublyLinkedList doublyOrders;
    SkipList skipOrders;

    for (int i = 1; i <= 50; ++i) {
        string orderId = "ORD" + to_string(i);
        string destination = "Location " + string(1, 'A' + (i - 1) % 26);
        int priority = (i - 1) % 5 + 1;

        // Add to all data structures
        arrayOrders.addMyOrder(orderId, destination, priority);
        singlyOrders.addOrder(myOrders(orderId, destination, priority));
        doublyOrders.addOrder(myOrders(orderId, destination, priority));
        skipOrders.addOrder(myOrders(orderId, destination, priority));
    }

    // Display all orders
    cout << "Array Orders:\n";
    arrayOrders.displayMyOrder();

    cout << "\nSingly Linked List Orders:\n";
    singlyOrders.displayOrders();

    cout << "\nDoubly Linked List Orders:\n";
    doublyOrders.displayOrders();

    cout << "\nSkip List Orders:\n";
    skipOrders.displayOrders();

    // Test features
    cout << "\nSearching for Order ID 'ORD25' in Array:\n";
    arrayOrders.searchMyOrder("ORD25");

    cout << "\nSearching for Order ID 'ORD25' in Singly Linked List:\n";
    singlyOrders.searchOrder("ORD25");

    cout << "\nRemoving Order ID 'ORD25' from Doubly Linked List:\n";
    doublyOrders.removeOrder("ORD25");

    cout << "\nTraversing Doubly Linked List in Reverse:\n";
    doublyOrders.traverseReverse();

    cout << "\nUpdating Priority for Order ID 'ORD30' in Doubly Linked List:\n";
    doublyOrders.updatePriority("ORD30", 5);

    cout << "\nSearching for Order ID 'ORD25' in Skip List:\n";
    skipOrders.searchOrder("ORD25");

    cout << "\nRemoving Order ID 'ORD25' from Skip List:\n";
    skipOrders.removeOrder("ORD25");

    return 0;
}
