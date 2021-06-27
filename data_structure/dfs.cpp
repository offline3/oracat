#include <iostream>
#include <map>
#include <list>
using namespace std;

class Graph{
public:
    Graph(){}

    void add_edge(int i, int j){
        adjList[i].push_back(j);
    }

    void DFS(int node){
        visit[node] = true;
        cout << node << " ";
        for(auto itr = adjList[node].begin(); itr != adjList[node].end(); itr++){
            if(visit[*itr])
                continue;
            DFS(*itr);
        }
    }
private:
    map<int,list<int> > adjList; 
    map<int,bool> visit;
};

int main(){
    Graph G;
    G.add_edge(0,1);
    G.add_edge(0,2);
    G.add_edge(1,2);
    G.add_edge(2,0);
    G.add_edge(2,3);
    G.add_edge(3,3);
    G.DFS(1);
}