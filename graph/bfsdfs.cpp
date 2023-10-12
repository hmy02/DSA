#include"Graph.h"
#include<iostream>
#include<queue>
using namespace std;

void DFS(Graph& G, int v) {

    G.Mark[v] = VISITED;
    cout << v << " ";
    for (Edge e = G.FirstEdge(v); G.isEdge(e); e = G.NextEdge(e)) {
        if (G.Mark[G.ToVertex(e)] == UNVISITED) {
            DFS(G, G.ToVertex(e));
        }
    }
}

void BFS(Graph& G, int v) {
    using std::queue;
    queue<int>Q;
    cout << v << " ";
    G.Mark[v] = VISITED;
    Q.push(v);
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (Edge e = G.FirstEdge(u); G.isEdge(e); e = G.NextEdge(e)) {
            if (G.Mark[G.ToVertex(e)] == UNVISITED) {
                cout << G.ToVertex(e)<<" ";
                G.Mark[G.ToVertex(e)] = VISITED;
                Q.push(G.ToVertex(e));
            }
        }
    }
}

void test_DFS() {
    Graphl G(7);
    int matrix[7][7] = { 0,1,0,0,0,0,0,
                         1,0,1,1,0,1,0,
                         0,1,0,1,0,0,0,
                         0,1,1,0,0,0,0,
                         0,0,0,0,0,1,1,
                         0,1,0,0,1,0,1,
                         0,0,0,0,1,1,0 };
    G.Init(matrix, 7);
    cout << "dfs res:" << endl;
    DFS(G, 0);
    cout << endl;


void test_BFS() {
    Graphl G(7);
    int matrix[7][7] = { 0,1,1,1,0,0,0,
                         1,0,1,1,0,1,0,
                         1,1,0,1,0,0,0,
                         1,1,1,0,0,0,1,
                         0,0,0,0,0,1,1,
                         0,1,0,0,1,0,1,
                         0,0,0,1,1,1,0 };
    G.Init(matrix, 7);
    cout << "bfs res:" << endl;
    BFS(G, 0);
    cout << endl;
}

int main() {
    test_DFS();
    test_BFS();
    return 0;
}