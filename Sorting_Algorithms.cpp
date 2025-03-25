//Christian De La Rosa
// Part 2

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;

// Struct for Delivery Orders
struct DeliveryOrder {
    string id;
    string destination;
    int priority;

    DeliveryOrder(string orderId, string orderDestination, int orderPriority)
        : id(orderId), destination(orderDestination), priority(orderPriority) {}
};

// Helper Function to Display Orders
void displayOrders(const vector<DeliveryOrder>& orders) {
    for (const auto& order : orders) {
        cout << "Order ID: " << order.id << ", Destination: " << order.destination
            << ", Priority: " << order.priority << endl;
    }
    cout << endl;
}

// Selection Sort Implementation
void selectionSort(vector<DeliveryOrder>& orders) {
    for (size_t i = 0; i < orders.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < orders.size(); ++j) {
            if (orders[j].priority < orders[minIndex].priority) {
                minIndex = j;
            }
        }
        swap(orders[i], orders[minIndex]);
    }
}

// Bubble Sort Implementation
void bubbleSort(vector<DeliveryOrder>& orders) {
    for (size_t i = 0; i < orders.size() - 1; ++i) {
        for (size_t j = 0; j < orders.size() - i - 1; ++j) {
            if (orders[j].priority > orders[j + 1].priority) {
                swap(orders[j], orders[j + 1]);
            }
        }
    }
}

// Merge Sort Helper Function
void merge(vector<DeliveryOrder>& orders, int left, int mid, int right) {
    vector<DeliveryOrder> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (orders[i].priority <= orders[j].priority) {
            temp.push_back(orders[i++]);
        }
        else {
            temp.push_back(orders[j++]);
        }
    }
    while (i <= mid) temp.push_back(orders[i++]);
    while (j <= right) temp.push_back(orders[j++]);

    for (int k = left; k <= right; ++k) {
        orders[k] = temp[k - left];
    }
}

// Merge Sort Implementation
void mergeSort(vector<DeliveryOrder>& orders, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(orders, left, mid);
        mergeSort(orders, mid + 1, right);
        merge(orders, left, mid, right);
    }
}

// Quick Sort Partition Function
int partition(vector<DeliveryOrder>& orders, int low, int high) {
    int pivot = orders[high].priority;
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (orders[j].priority < pivot) {
            ++i;
            swap(orders[i], orders[j]);
        }
    }
    swap(orders[i + 1], orders[high]);
    return i + 1;
}

// Quick Sort Implementation
void quickSort(vector<DeliveryOrder>& orders, int low, int high) {
    if (low < high) {
        int pi = partition(orders, low, high);
        quickSort(orders, low, pi - 1);
        quickSort(orders, pi + 1, high);
    }
}

// Generate Random List of Priorities
vector<int> generateRandomPriorities(int length, int minVal, int maxVal) {
    vector<int> priorities(length);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(minVal, maxVal);

    for (int& priority : priorities) {
        priority = dist(gen);
    }
    return priorities;
}

// Measure Execution Time
template <typename Func>
double measureExecutionTime(Func func, vector<DeliveryOrder>& orders) {
    auto start = chrono::high_resolution_clock::now();
    func(orders);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration<double, milli>(end - start).count();
}

// Main Function
int main() {
    vector<DeliveryOrder> orders = {
        {"ORD1", "Location A", 1}, {"ORD2", "Location B", 2}, {"ORD3", "Location C", 3},
        {"ORD4", "Location D", 4}, {"ORD5", "Location E", 5}, {"ORD6", "Location F", 1},
        {"ORD7", "Location G", 2}, {"ORD8", "Location H", 3}, {"ORD9", "Location I", 4},
        {"ORD10", "Location J", 5}, {"ORD11", "Location K", 1}, {"ORD12", "Location L", 2},
        {"ORD13", "Location M", 3}, {"ORD14", "Location N", 4}, {"ORD15", "Location O", 5},
        {"ORD16", "Location P", 1}, {"ORD17", "Location Q", 2}, {"ORD18", "Location R", 3},
        {"ORD19", "Location S", 4}, {"ORD20", "Location T", 5}, {"ORD21", "Location U", 1},
        {"ORD22", "Location V", 2}, {"ORD23", "Location W", 3}, {"ORD24", "Location X", 4},
        {"ORD25", "Location Y", 5}, {"ORD26", "Location Z", 1}, {"ORD27", "Location A", 2},
        {"ORD28", "Location B", 3}, {"ORD29", "Location C", 4}, {"ORD30", "Location D", 5},
        {"ORD31", "Location E", 1}, {"ORD32", "Location F", 2}, {"ORD33", "Location G", 3},
        {"ORD34", "Location H", 4}, {"ORD35", "Location I", 5}, {"ORD36", "Location J", 1},
        {"ORD37", "Location K", 2}, {"ORD38", "Location L", 3}, {"ORD39", "Location M", 4},
        {"ORD40", "Location N", 5}, {"ORD41", "Location O", 1}, {"ORD42", "Location P", 2},
        {"ORD43", "Location Q", 3}, {"ORD44", "Location R", 4}, {"ORD45", "Location S", 5},
        {"ORD46", "Location T", 1}, {"ORD47", "Location U", 2}, {"ORD48", "Location V", 3},
        {"ORD49", "Location W", 4}, {"ORD50", "Location X", 5}
    };

    cout << "Original Orders:\n";
    displayOrders(orders);

    // Sorting and measuring time for selection sort
    vector<DeliveryOrder> selectionSortedOrders = orders;
    double selectionSortTime = measureExecutionTime(selectionSort, selectionSortedOrders);
    cout << "Orders Sorted by Selection Sort (Time: " << selectionSortTime << " ms):\n";
    displayOrders(selectionSortedOrders);

    // Sorting and measuring time for bubble sort
    vector<DeliveryOrder> bubbleSortedOrders = orders;
    double bubbleSortTime = measureExecutionTime(bubbleSort, bubbleSortedOrders);
    cout << "Orders Sorted by Bubble Sort (Time: " << bubbleSortTime << " ms):\n";
    displayOrders(bubbleSortedOrders);

    // Sorting and measuring time for merge sort
    vector<DeliveryOrder> mergeSortedOrders = orders;
    double mergeSortTime = measureExecutionTime([&](vector<DeliveryOrder>& o) { mergeSort(o, 0, o.size() - 1); }, mergeSortedOrders);
    cout << "Orders Sorted by Merge Sort (Time: " << mergeSortTime << " ms):\n";
    displayOrders(mergeSortedOrders);

    // Sorting and measuring time for quick sort
    vector<DeliveryOrder> quickSortedOrders = orders;
    double quickSortTime = measureExecutionTime([&](vector<DeliveryOrder>& o) { quickSort(o, 0, o.size() - 1); }, quickSortedOrders);
    cout << "Orders Sorted by Quick Sort (Time: " << quickSortTime << " ms):\n";
    displayOrders(quickSortedOrders);

    // Generate random priorities
    vector<int> randomPriorities = generateRandomPriorities(10000, 1, 5);

    // First 1000 priorities
    vector<DeliveryOrder> ordersFirst1000;
    for (int i = 0; i < 1000; ++i) {
        ordersFirst1000.push_back({ "RAND" + to_string(i + 1), "RandomLocation", randomPriorities[i] });
    }

    // Sorting and measuring time for the first 1000 numbers
    cout << "\nSorting First 1000 Priorities:\n";

    auto testOrders = ordersFirst1000;
    cout << "Selection Sort: " << measureExecutionTime(selectionSort, testOrders) << " ms\n";

    testOrders = ordersFirst1000;
    cout << "Bubble Sort: " << measureExecutionTime(bubbleSort, testOrders) << " ms\n";

    testOrders = ordersFirst1000;
    cout << "Merge Sort: " << measureExecutionTime([&](vector<DeliveryOrder>& o) { mergeSort(o, 0, o.size() - 1); }, testOrders) << " ms\n";

    testOrders = ordersFirst1000;
    cout << "Quick Sort: " << measureExecutionTime([&](vector<DeliveryOrder>& o) { quickSort(o, 0, o.size() - 1); }, testOrders) << " ms\n";

    // Full 10,000 priorities
    vector<DeliveryOrder> ordersFull;
    for (int i = 0; i < 10000; ++i) {
        ordersFull.push_back({ "RAND" + to_string(i + 1), "RandomLocation", randomPriorities[i] });
    }

    // Sorting and measuring time for the full 10,000 numbers
    cout << "\nSorting Full 10,000 Priorities:\n";

    testOrders = ordersFull;
    cout << "Selection Sort: " << measureExecutionTime(selectionSort, testOrders) << " ms\n";

    testOrders = ordersFull;
    cout << "Bubble Sort: " << measureExecutionTime(bubbleSort, testOrders) << " ms\n";

    testOrders = ordersFull;
    cout << "Merge Sort: " << measureExecutionTime([&](vector<DeliveryOrder>& o) { mergeSort(o, 0, o.size() - 1); }, testOrders) << " ms\n";

    testOrders = ordersFull;
    cout << "Quick Sort: " << measureExecutionTime([&](vector<DeliveryOrder>& o) { quickSort(o, 0, o.size() - 1); }, testOrders) << " ms\n";

    return 0;
}