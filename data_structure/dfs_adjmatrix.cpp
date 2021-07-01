#include <iostream>
#include <map>
using namespace std;

class Graph{
public:
    Graph(int n){
        this->v = n;
        adjMatrix = new int*[n];
        // 初始化矩阵
        for(int row = 0; row < n; row++){
            adjMatrix[row] = new int[n];
            for(int col = 0; col < n; col++)
                adjMatrix[row][col] = 0;
        }
    }
    // 假设图为无向图，使用1表示有边
    void add_edge(int i,int j){
        adjMatrix[i][j] = 1;
        adjMatrix[j][i] = 1;
    }

    void DFS(int start){
        cout << start << " ";
        visit[start] = true;
        for (int i = 0; i < v; i++)
        {
            if(adjMatrix[start][i] == 1 && visit[i]== false) //顶点i与当前顶点存在边,且i未访问
                DFS(i);
        }
        
    }
public:
    int** adjMatrix; 
    map<int,bool> visit;
    int v; //记录顶点个数
};

// Driver code
int main()
{
    int v = 5;
  
    Graph G(v);
    G.add_edge(0, 1);
    G.add_edge(0, 2);
    G.add_edge(0, 3);
    G.add_edge(0, 4);

    G.DFS(0);
}