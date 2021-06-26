#include <iostream>
#include <map>
#include <list>
using namespace std;

struct edge
{
    int node; // 边的一个顶点
    int weighted; // 边的权重
    edge(int n, int w){
        node = n;
        weighted = w;
    }
};

class Graph{
public:
    Graph(){}

    // 打印图
    void print(){
        for(auto itr = adjList.begin(); itr != adjList.end(); itr++){
            cout << "vertex: " << itr->first << "->";
            for(auto itrl = itr->second.begin(); itrl != itr->second.end(); itrl++){
                cout << "{vertex:" << itrl->node << " weighted: " << itrl->weighted << "} ";
            }
            cout << "\n";
        }
    }

    // 设置点i到点j的边的权重，假设图为有向有权图
    void add_edge(int i, int j ,int w){
        adjList[i].push_back(edge(j,w));
    }

    void del_edge(int i, int j){
        list<edge>::iterator itr;
        for(itr = adjList[i].begin(); itr != adjList[i].end(); itr++){ //边的访问需要遍历边集，因此时间复杂度为o(n)
            if(itr->node == j){
                cout << "remove edge vertex" << i << "->" << "vertex" <<j << "\n";
                adjList[i].erase(itr);
                break;
            }
        }
    }
private:
    map<int,list<edge> > adjList; // 使用链表存储边集，方便增删
};

int main(){
    Graph G;
    G.add_edge(0,1,10);
    G.add_edge(0,2,3);
    G.add_edge(0,3,2);
    G.add_edge(1,3,7);
    G.add_edge(2,3,6);
    G.print();
    G.del_edge(0,2);
    G.print();
}