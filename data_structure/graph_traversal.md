# 图的遍历

图的遍历即对图中的每个顶底访问一次，与树的遍历类似。但与树的遍历算法不同的是：1.图中可能包含环，如果用简单的树遍历算法用于图中，则可能造成死循环，因此图的遍历通常需要对已遍历过的节点进行标记；2.图中可能存在孤立的节点，因此采用树的遍历算法，可能导致遗漏部分顶点。

## **深度优先遍历**

### 邻接表

深度优先遍历的过程是先访问初始节点v，再访问与顶点v临接的未访问顶点。如果顶点v没有邻接顶点，**或者已经访问过其邻接顶点**，则回溯到顶点v的前驱节点。如果回溯到遍历开始的第一个顶点，则遍历结束。**如果图中仍然有未访问的顶点，则遍历将继续从未访问的下一个顶点开始**。

如下图，选择1为初始顶点，先访问1，1有邻接节点2，访问2；2有邻接节点0和3，先访问0，0有邻接节点1，但1已被访问，因此回溯到0的前驱节点2，并访问节点2的下一个邻接节点3。顺序为1，2，0，3

![ezgif.com-gif-maker61](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/ezgif.com-gif-maker61.gif)

```c++
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
```

当从顶点1开始，遍历上图时

```c++
int main(){
    Graph G;
    G.add_edge(0,1);
    G.add_edge(0,2);
    G.add_edge(1,2);
    G.add_edge(2,0);
    G.add_edge(2,3);
    G.add_edge(3,3)
    G.DFS(1);
}
```

上面的深度优先算法仍然存在问题，原因是当图中存在孤立节点或者孤立的子图时，会有部分节点不能访问到。因此我们需要遍历图中顶点的集合，对没有访问过的顶点再进行搜索。

```c++
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

    void DFSUtil(int node){
        visit[node] = true;
        cout << node << " ";
        for(auto itr = adjList[node].begin(); itr != adjList[node].end(); itr++){
            if(visit[*itr])
                continue;
            DFSUtil(*itr);
        }
    }

    void DFS(){
        for(auto item : adjList){
            if(!visit[item.first]) // 如果当前顶点没有被访问过，则对当前节点进行搜素
                DFSUtil(item.first);
        }
    }
private:
    map<int,list<int> > adjList; 
    map<int,bool> visit;
};
```

**时空复杂度：**

时间复杂度：O(V+E)，V为顶点个数，所有顶点中邻接表的顶点数总和为E(即边数)，因此时间复杂度为O(V+E)

空间复杂度：O(V)，遍历需要额外的容器来存储已访问过的顶点，顶点数为V，因此空间复杂度为O(V)

### 邻接矩阵

使用邻接矩阵遍历图与使用邻接表类似。

```c++
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
```



## 宽度优先搜索

图的宽度优先遍历算法是一个分层搜索的过程，和数的层序遍历算法相同。图的宽度优先遍历需要一个队列作为保存当期节点的子节点的数据结构。如下图，从初始顶点2访问连通图。先访问顶点2，顶点2有0,3两个邻接顶点，因此先访问0和3，最后访问顶点1。

![image-20210701193426998](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20210701193426998.png)

```c++
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
	// 假设图为连通图
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
```

从顶点2开始遍历上图

```c++
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
```

输出结果为

```
2 0 3 1
```

图的搜索算法是图中最基本的算法，通过图的搜索算法可以解决一些常见的图问题，如检查图是否为连通图，检查图是有环等。
