// Christian De La Rosa
// Part 4 

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// Graph Representation using Adjacency List and Adjacency Matrix
class Graph {
    vector<vector<pair<int, int>>> adjList; // pair(destination, weight)
    vector<vector<int>> adjMatrix;         // Adjacency matrix

public:
    Graph(int vertices) {
        adjList.resize(vertices);
        adjMatrix.resize(vertices, vector<int>(vertices, INT_MAX));
        for (int i = 0; i < vertices; ++i) {
            adjMatrix[i][i] = 0; // Distance to self is 0
        }
    }

    void addEdge(int src, int dest, int weight) {
        adjList[src].emplace_back(dest, weight);
        adjMatrix[src][dest] = weight;
    }

    void printAdjacencyList() const {
        cout << "Adjacency List:\n";
        for (int i = 0; i < adjList.size(); ++i) {
            cout << "Node " << char('A' + i) << ": ";
            for (const auto& neighbor : adjList[i]) {
                cout << "(" << char('A' + neighbor.first) << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    void printAdjacencyMatrix() const {
        cout << "Adjacency Matrix:\n";
        for (const auto& row : adjMatrix) {
            for (int val : row) {
                if (val == INT_MAX) {
                    cout << "\tINF";
                }
                else {
                    cout << "\t" << val;
                }
            }
            cout << endl;
        }
    }

    void BFS(int start, int destination) {
        vector<bool> visited(adjList.size(), false);
        vector<int> parent(adjList.size(), -1);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            if (node == destination) break;

            for (const auto& neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    parent[neighbor.first] = node;
                    q.push(neighbor.first);
                }
            }
        }

        vector<int> path;
        for (int at = destination; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());

        cout << "BFS Path: ";
        if (path[0] == start) {
            for (int node : path) {
                cout << char('A' + node) << " ";
            }
        }
        else {
            cout << "No path found.";
        }
        cout << endl;
    }

    void DFSUtil(int node, int destination, vector<bool>& visited, vector<int>& path, vector<int>& result) {
        visited[node] = true;
        path.push_back(node);

        if (node == destination) {
            result = path;
            return;
        }

        for (const auto& neighbor : adjList[node]) {
            if (!visited[neighbor.first]) {
                DFSUtil(neighbor.first, destination, visited, path, result);
                if (!result.empty()) return;
            }
        }

        path.pop_back();
    }

    void DFS(int start, int destination) {
        vector<bool> visited(adjList.size(), false);
        vector<int> path, result;

        DFSUtil(start, destination, visited, path, result);

        cout << "DFS Path: ";
        if (!result.empty()) {
            for (int node : result) {
                cout << char('A' + node) << " ";
            }
        }
        else {
            cout << "No path found.";
        }
        cout << endl;
    }

    int dijkstraShortestPath(int start, int destination) {
        int n = adjList.size();
        vector<int> dist(n, INT_MAX);
        dist[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int currDist = pq.top().first;
            int currNode = pq.top().second;
            pq.pop();

            if (currNode == destination) return currDist;

            if (currDist > dist[currNode]) continue;

            for (const auto& neighbor : adjList[currNode]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;

                if (dist[currNode] + weight < dist[nextNode]) {
                    dist[nextNode] = dist[currNode] + weight;
                    pq.emplace(dist[nextNode], nextNode);
                }
            }
        }

        return INT_MAX;
    }
};

// Main Function
int main() {
    int vertices = 10; // Locations A-J
    Graph g(vertices);

    // Adding edges based on the provided graph
    g.addEdge(0, 1, 10); // A -> B
    g.addEdge(0, 2, 15); // A -> C
    g.addEdge(1, 3, 12); // B -> D
    g.addEdge(1, 8, 11); // B -> I
    g.addEdge(2, 4, 10); // C -> E
    g.addEdge(3, 5, 2);  // D -> F
    g.addEdge(3, 7, 14); // D -> H
    g.addEdge(4, 5, 5);  // E -> F
    g.addEdge(4, 6, 4);  // E -> G
    g.addEdge(5, 6, 3);  // F -> G
    g.addEdge(6, 7, 8);  // G -> H
    g.addEdge(7, 8, 7);  // H -> I
    g.addEdge(8, 9, 6);  // I -> J
    g.addEdge(9, 0, 6);  // J -> A

    g.printAdjacencyList();
    g.printAdjacencyMatrix();

    auto start = high_resolution_clock::now();
    g.BFS(0, 6); // A -> G
    auto end = high_resolution_clock::now();
    cout << "BFS Execution Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";

    start = high_resolution_clock::now();
    g.DFS(0, 6); // A -> G
    end = high_resolution_clock::now();
    cout << "DFS Execution Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";

    start = high_resolution_clock::now();
    int shortestDistance = g.dijkstraShortestPath(0, 6); // A -> G
    end = high_resolution_clock::now();
    cout << "Dijkstra's Shortest Path Distance: " << shortestDistance
        << " \nExecution Time: " << duration_cast<microseconds>(end - start).count() << " microseconds\n";

    return 0;
}
