#pragma once
/**使用邻接矩阵来表示一个图**/

#define MAX_VERTS 20

class Vertex
{
public:
	Vertex(char lab)
	{
		Label = lab;
		wasVisited = false;
	}
	bool wasVisited;   //检查是否被访问过
	char Label;
};

class MatrixGragh
{
public:
	MatrixGragh();
	~MatrixGragh();
	void addVertex(char lab);
	void addEdge(int Start, int End);  //添加边
	void PrintMatrix(); //打印矩阵
	void showVertex(int v);
	void DFS();  //深度优先搜索
	void BFS();  //广度优先搜索
private:
	Vertex* vertexList[MAX_VERTS]; //最多顶点的数量
	int nVerts;     //实际数组顶点的数量
	int adjMat[MAX_VERTS][MAX_VERTS];  //举证
	int getAdjUnvisitedVertex(int v);
};

