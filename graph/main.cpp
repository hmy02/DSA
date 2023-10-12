#include <iostream>
#include "Graph.h"
#include "Minheap.h"
using namespace std;

class Dist {
public:
    int index;
    int length;
    int pre;
    bool operator>(Dist b) { return this->length > b.length; }
    bool operator == (Dist b) { return this->length == b.length; }
    bool operator <(Dist b) { return this->length < b.length; }
};

void print_trace(Dist* D, Dist d, int s) {
    if (d.pre != s) {
        print_trace(D, D[d.pre], s);
    }
    cout << "->" << d.index;

}

void Dijkstra(Graph& G, int s, Dist*& D) {   // s为源点
    D = new Dist[G.VerticesNum()];
    for (int i = 0; i < G.VerticesNum(); i++) {
        G.Mark[i] = UNVISITED;
        D[i].index = i;
        D[i].length = INFINITY;
        D[i].pre = s;
    }
    D[s].length = 0;
    Minheap<Dist>H(G.VerticesNum());
    H.Insert(D[s]);

    for (int i = 0; i < G.VerticesNum(); i++) {
        bool FOUND = false;
        Dist d;
        while (!H.isempty()) {
            d = H.RemoveMin();
            if (G.Mark[d.index] == UNVISITED) {
                cout << "【V" << s << "->V" << d.index << "】" << endl <<  "最短路径长度: ";
                cout << d.length ; cout << endl;
                cout << "路径为" << s;
                print_trace(D, d, s);
                cout << endl;
                FOUND = true;
                break;
            }
        }
        if (!FOUND) break;
        int v = d.index;
        G.Mark[v] = VISITED;
        for (Edge e = G.FirstEdge(v); G.isEdge(e); e = G.NextEdge(e)) {
            if (D[G.ToVertex(e)].length > (D[v].length + G.Weight(e))) {
                D[G.ToVertex(e)].length = D[v].length + G.Weight(e);
                D[G.ToVertex(e)].pre = v;
                H.Insert(D[G.ToVertex(e)]);
            }

        }
    }
}
int main() {
    Graphm G(5);
    G.setEdge(0, 1, 10);
    G.setEdge(0, 3, 30);
    G.setEdge(0, 4, 100);
    G.setEdge(1, 2, 50);
    G.setEdge(2, 4, 10);
    G.setEdge(3, 2, 20);
    G.setEdge(3, 1, 10);
    G.setEdge(3, 4, 60);
    Dist* D;
    Dijkstra(G, 3, D);
    return 0;
}
