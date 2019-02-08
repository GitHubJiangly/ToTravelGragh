#include "stdafx.h"
#include "MatrixGragh.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;
MatrixGragh::MatrixGragh()  //构造函数
{
	nVerts = 0;
	for (int i = 0; i < MAX_VERTS; i++)
		for (int j = 0; j < MAX_VERTS; j++)
			adjMat[i][j] = 0;   //全部初始化为0
}
MatrixGragh::~MatrixGragh()
{
	for (int i = 0; i < nVerts; i++)
		delete vertexList[i];
}
void MatrixGragh::addVertex(char lab)
{
	vertexList[nVerts++] = new Vertex(lab);
}
void MatrixGragh::addEdge(int Start, int End) //增加一条边
{
	adjMat[Start][End] = 1;
	adjMat[End][Start] = 1;   //矩阵是对称的
}
void MatrixGragh::PrintMatrix()
{
	for (int i = 0; i < nVerts; i++)
	{
		for (int j = 0; j < nVerts; j++)
			cout << adjMat[i][j] << " ";
		cout << endl;
	}
}
void MatrixGragh::showVertex(int v)
{
	cout << vertexList[v]->Label << " ";
}
void MatrixGragh::BFS()//广度优先搜索 使用队列
{
	queue<int> gQueue;
	vertexList[0]->wasVisited = true;
	showVertex(0);
	gQueue.push(0);
	int Vert1, Vert2;
	while (gQueue.size() > 0)
	{
		Vert1 = gQueue.front();
		gQueue.pop();
		Vert2 = getAdjUnvisitedVertex(Vert1);
		while (Vert2 != -1)
		{
			vertexList[Vert2]->wasVisited = true;
			showVertex(Vert2);
			gQueue.push(Vert2);
			Vert2 = getAdjUnvisitedVertex(Vert1);
		}
	}
	cout << endl;
	for (int i = 0; i < nVerts; i++)
		vertexList[i]->wasVisited = false;
}
void MatrixGragh::DFS()  //深度优先搜索 使用堆栈
{
	stack<int> gStack;
	vertexList[0]->wasVisited = true;
	showVertex(0);
	gStack.push(0); //压入堆栈
	int v;
	while (gStack.size() > 0)
	{
		v = getAdjUnvisitedVertex(gStack.top());
		if (v == -1)   //没有下一个
			gStack.pop();
		else {
			vertexList[v]->wasVisited = true;
			showVertex(v);
			gStack.push(v); //压入堆栈
		}
	}
	cout << endl;
	for (int i = 0; i < nVerts; i++)
		vertexList[i]->wasVisited = false;  //搜索完后重新设置为false 以便多次搜索
}
int MatrixGragh::getAdjUnvisitedVertex(int v)  //访问下一个
{
	for (int j = 0; j < nVerts; j++)
	{
		if ((adjMat[v][j] == 1) && (vertexList[j]->wasVisited == false))  //查看是否邻接的而且未被访问过的
			return j;
	}
	return -1;
}
