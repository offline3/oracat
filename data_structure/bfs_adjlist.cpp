#include <iostream>
#include <map>
#include <list>
#include <queue>
using namespace std;

class Graph{
public:
    Graph(){}

    void add_edge(int i, int j){
        adjList[i].push_back(j);
    }

    void BFS(int node){
        queue<int> q;
        q.push(node);
        visit[node] = true;
        while (!q.empty())
        {
            int cur_node = q.front();
            q.pop();
            cout << cur_node <<" ";
            for(auto itr = adjList[cur_node].begin(); itr != adjList[cur_node].end(); itr++){
                if(visit[*itr])
                    continue;
                q.push(*itr);
                visit[*itr] = true;
            }
        }
        
    }
private:
    map<int,list<int> > adjList; 
    map<int,bool> visit;
};

int main(){
    Graph G;
    G.add_edge(0, 1);
    G.add_edge(0, 2);
    G.add_edge(1, 2);
    G.add_edge(2, 0);
    G.add_edge(2, 3);
    G.add_edge(3, 3);
    G.BFS(2);
}