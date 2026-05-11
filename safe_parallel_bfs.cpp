#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Add edge
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // Safe Parallel BFS
    void parallelBFS(int start) {

        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "Parallel BFS Traversal: ";

        while (!q.empty()) {

            int node;

            // Safe queue access
            #pragma omp critical
            {
                node = q.front();
                q.pop();
            }

            cout << node << " ";

            // Parallel processing of neighbors
            #pragma omp parallel for
            for (int i = 0; i < adj[node].size(); i++) {

                int neighbor = adj[node][i];

                // Critical section for shared data
                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
        }

        cout << endl;
    }
};

int main() {

    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    cout << "Enter number of edges: ";
    cin >> E;

    cout << "Enter edges (u v):" << endl;

    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;

        // Validation
        if (u >= 0 && u < V && v >= 0 && v < V) {
            g.addEdge(u, v);
        } else {
            cout << "Invalid edge skipped: "
                 << u << " " << v << endl;
        }
    }

    int start;

    cout << "Enter starting vertex: ";
    cin >> start;

    if (start < 0 || start >= V) {
        cout << "Invalid starting vertex!" << endl;
        return 1;
    }

    g.parallelBFS(start);

    return 0;
}
