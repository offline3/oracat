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
    void add_edge(int i,int j, float w){
       adjMatrix[i][j] = w;
    }
    // 删除边,以0表示无边
    void del_edge(int i, int j){
        add_edge(i,j,0);
    }
private:
    vector<vector<int> > adjMatrix;
};

int main(){
    Graph G(4);
    G.add_edge(0,1,10);
    G.add_edge(0,2,3);
    G.add_edge(0,3,2);
    G.add_edge(1,3,7);
    G.add_edge(2,3,6);
    G.print();
}