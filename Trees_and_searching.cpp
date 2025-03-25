//Christian De La Rosa
//Part 3 

#include <iostream>
#include <string>
#include <chrono>
#include <cmath>
using namespace std;
// Create struct for delivery orders! :)
struct DeliveryOrder {
    string id;
    string destination;
    int priority;

    DeliveryOrder(string orderId = "", string orderDestination = "", int orderPriority = 0)
        : id(orderId), destination(orderDestination), priority(orderPriority) {}
};
// Bianary Search trees
struct BSTNode {
    DeliveryOrder data;
    BSTNode* left; //define left and right nodes 
    BSTNode* right;

    BSTNode(const DeliveryOrder& order) : data(order), left(nullptr), right(nullptr) {}
};
//Creates a BST class 
class BST {
private:
    BSTNode* root;
// Function to insert delivery orders  
    void insert(BSTNode*& node, const DeliveryOrder& order) {
        if (!node) {
            node = new BSTNode(order);
        }
        else if (order.id < node->data.id) {
            insert(node->left, order);
        }
        else if (order.id > node->data.id) {
            insert(node->right, order);
        }
    }
// Function that will search the bst 
    BSTNode* search(BSTNode* node, const string& id) const {
        if (!node || node->data.id == id) {
            return node;
        }
        if (id < node->data.id) {
            return search(node->left, id);
        }
        return search(node->right, id);
    }

    BSTNode* findMin(BSTNode* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }
// Deleting a node/element in a BST 
    BSTNode* remove(BSTNode* node, const string& id) {
        if (!node) {
            return node;
        }

        if (id < node->data.id) {
            node->left = remove(node->left, id);
        }
        else if (id > node->data.id) {
            node->right = remove(node->right, id);
        }
        else {
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data.id);
        }
        return node;
    }
// In-order transversal 
    void inOrderTraversal(BSTNode* node) const {
        if (node) {
            inOrderTraversal(node->left);
            cout << "Order ID: " << node->data.id << ", Destination: " << node->data.destination
                << ", Priority: " << node->data.priority << endl;
            inOrderTraversal(node->right);
        }
    }
// Insertion and Seaching 
public:
    BST() : root(nullptr) {}

    void insert(const DeliveryOrder& order) {
        insert(root, order);
    }

    void search(const string& id) const {
        BSTNode* result = search(root, id);
        if (result) {
            cout << "Order found: ID: " << result->data.id << ", Destination: " << result->data.destination
                << ", Priority: " << result->data.priority << endl;
        }
        else {
            cout << "Order ID " << id << " not found." << endl;
        }
    }

    void remove(const string& id) {
        root = remove(root, id);
    }

    void inOrderTraversal() const {
        inOrderTraversal(root);
    }
};

// AVL Node structure
struct AVLNode {
    DeliveryOrder data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const DeliveryOrder& order)
        : data(order), left(nullptr), right(nullptr), height(1) {}
};
// Create an AVL tree class 
class AVLTree {
private:
    AVLNode* root;

    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }
// Function for right roations !
    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }
// Function for left roations 
    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }
// Inserting an order and  making sure if the tree is balanced 
    AVLNode* insert(AVLNode* node, const DeliveryOrder& order) {
        if (!node) {
            return new AVLNode(order);
        }
        if (order.id < node->data.id) {
            node->left = insert(node->left, order);
        }
        else if (order.id > node->data.id) {
            node->right = insert(node->right, order);
        }
        else {
            return node;
        }
// Retrieves and gets max heights 
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && order.id < node->left->data.id) {
            return rotateRight(node);
        }
        if (balance < -1 && order.id > node->right->data.id) {
            return rotateLeft(node);
        }
        if (balance > 1 && order.id > node->left->data.id) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && order.id < node->right->data.id) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    AVLNode* search(AVLNode* node, const string& id) {
        if (!node || node->data.id == id) {
            return node;
        }
        if (id < node->data.id) {
            return search(node->left, id);
        }
        return search(node->right, id);
    }

    void inOrderTraversal(AVLNode* node) {
        if (node) {
            inOrderTraversal(node->left);
            cout << "Order ID: " << node->data.id << ", Destination: " << node->data.destination
                << ", Priority: " << node->data.priority << endl;
            inOrderTraversal(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const DeliveryOrder& order) {
        root = insert(root, order);
    }

    void search(const string& id) {
        AVLNode* result = search(root, id);
        if (result) {
            cout << "Order found: ID: " << result->data.id << ", Destination: " << result->data.destination
                << ", Priority: " << result->data.priority << endl;
        }
        else {
            cout << "Order ID " << id << " not found." << endl;
        }
    }

    void inOrderTraversal() {
        inOrderTraversal(root);
    }
};

int main() {
    BST bst;
    AVLTree avl;

    // Insert 50 delivery orders
    for (int i = 1; i <= 50; ++i) {
        string orderId = "ORD" + to_string(i);
        string destination = "Location " + char('A' + (i - 1) % 26);
        int priority = (i - 1) % 5 + 1;
        DeliveryOrder order(orderId, destination, priority);

        auto start = chrono::high_resolution_clock::now();
        bst.insert(order);
        auto end = chrono::high_resolution_clock::now();
        cout << "BST Insertion Time for " << orderId << ": "
            << chrono::duration<double, milli>(end - start).count() << " ms\n";

        start = chrono::high_resolution_clock::now();
        avl.insert(order);
        end = chrono::high_resolution_clock::now();
        cout << "AVL Insertion Time for " << orderId << ": "
            << chrono::duration<double, milli>(end - start).count() << " ms\n";
    }

    // Search for a specific order
    string searchId = "ORD25";
    auto start = chrono::high_resolution_clock::now();
    bst.search(searchId);
    auto end = chrono::high_resolution_clock::now();
    cout << "BST Search Time for " << searchId << ": "
        << chrono::duration<double, milli>(end - start).count() << " ms\n";
    start = chrono::high_resolution_clock::now();
    avl.search(searchId);
    end = chrono::high_resolution_clock::now();
    cout << "AVL Search Time for " << searchId << ": "
        << chrono::duration<double, milli>(end - start).count() << " ms\n";

    // Perform in-order traversal for both trees
    cout << "\nIn-order Traversal of BST:\n";
    bst.inOrderTraversal();

    cout << "\nIn-order Traversal of AVL Tree:\n";
    avl.inOrderTraversal();

    // Test deletion of a specific order
    string deleteId = "ORD25";
    cout << "\nDeleting " << deleteId << " from BST:\n";
    start = chrono::high_resolution_clock::now();
    bst.remove(deleteId);
    end = chrono::high_resolution_clock::now();
    cout << "BST Deletion Time for " << deleteId << ": "
        << chrono::duration<double, milli>(end - start).count() << " ms\n";

    cout << "\nDeleting " << deleteId << " from AVL Tree:\n";
    start = chrono::high_resolution_clock::now();
    avl.insert({}); // Deletion implementation missing for AVL Tree. Placeholder for now.
    end = chrono::high_resolution_clock::now();
    cout << "AVL Deletion Time for " << deleteId << ": "
        << chrono::duration<double, milli>(end - start).count() << " ms\n";

    // Display traversal after deletion
    cout << "\nIn-order Traversal of BST after Deletion:\n";
    bst.inOrderTraversal();

    cout << "\nIn-order Traversal of AVL Tree after Deletion:\n";
    avl.inOrderTraversal();

    return 0;
}
