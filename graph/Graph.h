#include<iostream>
#define UNVISITED 0
#define VISITED 1
#define INFINITY 999999

class Edge{
public:
    int from, to, weight;
    Edge(){
        from=-1;to=-1;weight=-1;
    }
    Edge(int f, int t, int w){
        from=f;to=t;weight=w;
    }
};
//图基类
class Graph{
public:
    int numVertex;
    int numEdge;
    int* Mark;
    int* Indegree;

    Graph(int numVert){
        numVertex = numVert;
        numEdge = 0;
        Indegree = new int[numVertex];
        Mark = new int[numVertex];
        for(int i = 0; i < numVertex; i++) {
            Mark[i] = UNVISITED;
            Indegree[i] = 0;
        }
    };
    ~Graph() { delete[]Mark; delete[]Indegree; };
    int VerticesNum() { return numVertex; };
    bool isEdge(Edge oneEdge){
        if (oneEdge.weight > 0 && oneEdge.weight <= INFINITY && oneEdge.to >= 0) return true;
        return false;
    };

    int FromVertex(Edge oneEdge) { return oneEdge.from; };
    int ToVertex(Edge oneEdge) { return oneEdge.to; };
    int Weight(Edge oneEdge) { return oneEdge.weight; };

    virtual Edge FirstEdge(int oneVertex) = 0;
    virtual Edge NextEdge(Edge preEdge) = 0;
    virtual void setEdge(int fromVertex, int toVertex, int weight) = 0;
    virtual void delEdge(int fromVertex, int toVertex) = 0;


};

class Graphm:public Graph{
private:
    int** matrix;
public:
    Graphm(int numVert);
    ~Graphm();
    Edge FirstEdge(int oneVertex);
    Edge NextEdge(Edge preEdge);
    void setEdge(int from, int to, int weight);
    void delEdge(int from, int to);
    void setG(int mat[7][7], int n);
};

Graphm::Graphm(int numVert): Graph(numVert){
    int i, j;
    matrix = (int**)new int* [numVertex];
    for (i = 0; i < numVertex; i++)
        matrix[i] = new int[numVertex];
    for (i = 0; i < numVertex; i++) {
        for (j = 0; j < numVertex; j++) {
            matrix[i][j] = 0;
        }
    }
}

Graphm::~Graphm() {
    for (int i = 0; i < numVertex; i++) delete[]matrix[i];
    delete[]matrix;
}

Edge Graphm::FirstEdge(int oneVertex) {
    Edge myEdge;
    myEdge.from = oneVertex;
    int i = 0;
    while (i < numVertex && matrix[myEdge.from][i] == 0) i++;
    if (i >= numVertex)  return myEdge;	// myEdge.to默认为-1，虽然此步返回了一个Edge，但是可以在Graph::isEdge()中判断出无效
    myEdge.to = i;
    myEdge.weight = matrix[myEdge.from][myEdge.to];
    return myEdge;
}

Edge Graphm::NextEdge(Edge preEdge) {
    Edge myEdge;
    myEdge.from = preEdge.from;
    int i = preEdge.to + 1;
    while (i < numVertex&& matrix[myEdge.from][i] == 0) i++;
    if (i >= numVertex) return myEdge;
    myEdge.to = i;
    myEdge.weight = matrix[myEdge.from][myEdge.to];
    return myEdge;
}

void Graphm::setEdge(int from, int to, int weight) {
    if (matrix[from][to] <= 0) {
        numEdge++;
        Indegree[to]++;
    }
    matrix[from][to] = weight;
}

void Graphm::delEdge(int from, int to) {
    if (matrix[from][to] > 0) {
        Indegree[to]--;
        numEdge--;
    }
    matrix[from][to] = 0;
}

void Graphm::setG(int mat[7][7], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] > 0) {
                setEdge(i,j,mat[i][j]);
            }
        }
    }
}

struct listUnit {    //邻接表表目中数据部分的结构定义
    int vertex;      //边的终点
    int weight;      //边的权
};

template<class Elem>   //链表元素
class LinkNode {
public:
    Elem element;      //表目的数据
    LinkNode* next;        //表目指针，指向下一个表目
    LinkNode(const Elem& elemval, LinkNode* nextval = NULL) { //构造函数
        element = elemval;
        next = nextval;
    }
    LinkNode(LinkNode* nextval = NULL) { 					//构造函数
        next = nextval;
    }
};

template<class Elem>   //链表
class LList {
public:
    LinkNode<Elem>* head;  //head指针并不储存任何实际元素，其存在只是为了操作方便
    LList() {          //构造函数
        head = new LinkNode<Elem>();
    }
};

class Graphl :public Graph {
private:
    LList<listUnit>* graList;
public:
    Graphl(int numVert) :Graph(numVert) {
        graList = new LList<listUnit>[numVert];
    }

    Edge FirstEdge(int oneVertex);
    Edge NextEdge(Edge preEdge);
    void setEdge(int from, int to, int weight);
    void delEdge(int from, int to);
    void Init(int G[7][7], int n);
};


void Graphl::setEdge(int from, int to, int weight) {
    LinkNode<listUnit>* temp = graList[from].head;
    while (temp->next != NULL && temp->next->element.vertex < to) temp = temp->next;
    if (temp->next == NULL) {
        temp->next = new LinkNode<listUnit>;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        numEdge++;
        Indegree[to]++;
        return;
    }
    if (temp->next->element.vertex == to) {
        temp->next->element.weight = weight;
        return;
    }
    if (temp->next->element.vertex > to) {
        LinkNode<listUnit>* other = temp->next;
        temp->next = new LinkNode<listUnit>;
        temp->next->element.vertex = to;
        temp->next->element.weight = weight;
        temp->next->next = other;
        numEdge++;
        Indegree[to]++;
        return;
    }
}

Edge Graphl::FirstEdge(int oneVertex) {
    Edge e;
    e.from = oneVertex;
    LinkNode<listUnit>* temp = graList[oneVertex].head;
    if (temp->next != NULL) {
        e.to = temp->next->element.vertex;
        e.weight = temp->next->element.weight;
    }
    return e;

}

Edge Graphl::NextEdge(Edge preEdge) {
    Edge e;
    e.from = preEdge.from;
    LinkNode<listUnit>* temp = graList[preEdge.from].head;
    while (temp!= NULL && temp->element.vertex <= preEdge.to) temp = temp->next;
    if (temp != NULL) {
        e.to = temp->element.vertex;
        e.weight = temp->element.weight;
    }
    return e;
}


void Graphl::delEdge(int from, int to) {
    LinkNode<listUnit>* temp = graList[from].head;
    while (temp->next != NULL && temp->next->element.vertex < to) {
        temp = temp->next;
    }

    if (temp->next == NULL) return;
    if (temp->next->element.vertex == to) {
        LinkNode<listUnit>* t = temp->next;
        temp->next = temp->next->next;
        delete t;
        numEdge--;
        Indegree[to]--;
        return;
    }
    if (temp->next->element.vertex > to) return;

}


void Graphl::Init(int mat[7][7], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] > 0) {
                this->setEdge(i, j, mat[i][j]);
            }
        }
    }
}

