# 图算法

## 图的遍历

图的遍历即对图中的每个顶底访问一次，与树的遍历类似。但与树的遍历算法不同的是：1.图中可能包含环，如果用简单的树遍历算法用于图中，则可能造成死循环，因此图的遍历通常需要对已遍历过的节点进行标记；2.图中可能存在孤立的节点，因此采用树的遍历算法，可能导致遗漏部分顶点。

**深度优先遍历**

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

