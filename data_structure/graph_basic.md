# 图论基础

图是由一系列顶点(vertices)和一系列连接任意两个顶点的边(edges)所组成的数据结构。图有许多种应用场合，在现实中，很多问题都可以通过将研究目标抽象成图这种数据结构，并利用图论中的算法，从而解决问题。以我所在的微电子行业为例，通过硬件描述语言(如verilog)生成电路图(netlist)时，netlist此时便可以抽象成图，用图中的顶点代表各种元器件，图中的边即表示元器件中的连接关系。

![img](https://media.geeksforgeeks.org/wp-content/cdn-uploads/undirectedgraph.png)

通常而言，图用`G(V,E)`表示，其中`V`表示顶点集合，`E`表示边集，如上图，点集合`v = {0,1,2,3,4}`，边集合`E = {<0,1>, <1,2>, <2,3>, <3,4>, <0,4>, <1,4>, <1,3>}`

> 专业名词中带英文注释，能够方便日后阅读相关的英文资料

## 图的分类

按照边是否有方向，图可以分为**有向图**(Directed Graph)和**无向图**(Undirected Graph)。有向图即表示边具有方向性，点`V1`到点`v2`的边与点`v2`到点`v1`的边是不同的两条边，而无向图边没有方向性，因此点`V1`到点`v2`的边与点`v2`到点`v1`的边可以用通一条边表示。如下图所示。

![Directed and Undirected graph. Ref 7 | Download Scientific Diagram](https://www.researchgate.net/profile/Debojoti-Kuzur/publication/282653028/figure/fig2/AS:282176378687493@1444287499817/Directed-and-Undirected-graph-Ref-7.png)

按照图中边的疏密程度，图可以分为**稀疏图**(Sparse graph)和**稠密图**(Dense graph)

![image-20210625205149132](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20210625205149132.png)

按照图中边是否有权，图可以分为**有权图**(Weighted)和**无权图**(Unweighted)。边的权重可以用来表示两个顶点之间连接的紧密程度，如用来表示社交网络中，不同人之间的友好程度。如下图，即为带有权重的图。

![embedded_image631dlA2bWxfUcxrFTcOic5s8ihoKMqUyEvIoS5dJtw-GPk_10_Bs2ItdkpPk](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/embedded_image631dlA2bWxfUcxrFTcOic5s8ihoKMqUyEvIoS5dJtw-GPk_10_Bs2ItdkpPk.png)

当图中的任意两个顶点都有边相连时，则称为**完全图**(Complete graph)。由此可得出，无向完全图边的数量为`n*(n-1)/2`，有向完全图边的数量为`n*(n-1)`(n个顶点，每个顶点具有n-1条边)。

对于一个图，如果以任意一个点为起点，在图上沿着边走都可以到达其他所有点，那么这个图就称为**连通图**(connected graph)

图还可以以图中是否有环分为有环图(Cyclic graph)和无环图(Acyclic graph)，如下图所示(有向图中的环必须是同一个方向才能称之为环)。

![Intro to Graphs - NY Comdori Computer Science Note](https://nycomdorics.com/wp-content/uploads/2020/03/graph_example3.png)

## 图中的度

在无向图中，度(degress)是指某个顶点连出的边数。如下图，无向图各顶点的度如红色数字所示。



![image-20210625204225560](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20210625204225560.png)



在有向图中，则有入度(in-degress)和出度(out-degree)之分。如下图，有向图各顶点的入度/出度如图所示。

![image-20210625204655673](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20210625204655673.png)



### 图的表示方法

图通常有两种表示方法：

1. 邻接矩阵(Adjacency Matrix)
2. 邻接表(Adjacency List)

同时还有其他中表示方法，如关联矩阵(Incidence Matrix)和关联表(Incidence List)。

**邻接矩阵**

邻接矩阵是VxV的二维矩阵，V为图中顶点的数量。假设用`adj[][]`表示一张图，当顶点`i`和顶点`j`有边时，即可以用`adj[i][j] = 1`来表示`i`到`j`的边。当图为有权图时，则可以用`adj[i][j] = w`来表示一张有权图(w表示边的权重)。当图为无权图时，邻接矩阵为对称阵，如下图所示，分别为有向图，无向图，无权图，有权图的邻接矩阵表示方法。

![image-20210625212111857](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20210625212111857.png)

使用邻接矩阵表示图时，图的空间复杂度为o(v^2)，边的增删查改的时间复杂度为o(1)。可见，使用邻接矩阵表示图，能够快速的访问边，但当图中的边比较稀疏时，图的空间复杂度始终为o(v^2)。因此，邻接矩阵通常不适用于稀疏图。

邻接矩阵代码示例：

```c++
#include <iostream>
#include <vector>
using namespace std;

class Graph{
public:
    // 构造函数，生成一个v*v的二维数组，v为顶点数量
    Graph(int v){
        for(int i = 0 ;i < v; i++){
            adjMatrix.push_back(vector<int>(v,0));
        }
    }
    // 打印图
    void print(){
        for(int i = 0; i < adjMatrix.size(); i++){
            for(int j = 0; j < adjMatrix.size(); j++)
                cout << adjMatrix[i][j] << " ";
            cout << "\n";
        }
    }

    // 设置点i到点j的边的权重，假设图为有向有权图
    void set_edge(int i,int j, float w){
       adjMatrix[i][j] = w;
    }
    // 删除边
    void del_edge(int i, int j){
        set_edge(i,j,0);
    }
private:
    vector<vector<int> > adjMatrix;
};
```

当使用如上定义的邻接矩阵表示下图时，

![image-20210626104516002](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20210626104516002.png)

```c++
int main(){
    Graph G(4);
    G.set_edge(0,1,10);
    G.set_edge(0,2,3);
    G.set_edge(0,3,2);
    G.set_edge(1,3,7);
    G.set_edge(2,3,6);
    G.print();
}
```



**邻接表**

在邻接表，每个顶点都有对应的一个序列容器，当点`i`与点`j`有边时，便将点`j`放入到点`i`对应的序列容器中。如下图为有向图的邻接表表示方法。

![image-20210625213307796](https://void-pointer-imgsubmit.oss-cn-shanghai.aliyuncs.com/img/image-20210625213307796.png)

使用邻接表表示图时，图的空间复杂度为o(|v|+|e|)，边的访问时间复杂度为o(v)。当图边数密集时，最糟情况下空间复杂度可为o(v^2)(如完全图，边的数量为`v*(v-1)`，因此，邻接表通常更适用于表示稀疏图。

邻接表示例代码

```c++
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
```

同理，使用邻接表表示上面那张图时

```c++
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
```

输出

```
vertex: 0->{vertex:1 weighted: 10} {vertex:2 weighted: 3} {vertex:3 weighted: 2}
vertex: 1->{vertex:3 weighted: 7}
vertex: 2->{vertex:3 weighted: 6}
remove edge vertex0->vertex2
vertex: 0->{vertex:1 weighted: 10} {vertex:3 weighted: 2}
vertex: 1->{vertex:3 weighted: 7}
vertex: 2->{vertex:3 weighted: 6}
```

