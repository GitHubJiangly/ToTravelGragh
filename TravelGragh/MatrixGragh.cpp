#include "stdafx.h"
#include "MatrixGragh.h"
#include <iostream>
#include <stack>
#include <queue>

using namespace std;
MatrixGragh::MatrixGragh()  //���캯��
{
	nVerts = 0;
	for (int i = 0; i < MAX_VERTS; i++)
		for (int j = 0; j < MAX_VERTS; j++)
			adjMat[i][j] = 0;   //ȫ����ʼ��Ϊ0
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
void MatrixGragh::addEdge(int Start, int End) //����һ����
{
	adjMat[Start][End] = 1;
	adjMat[End][Start] = 1;   //�����ǶԳƵ�
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
void MatrixGragh::BFS()//����������� ʹ�ö���
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
void MatrixGragh::DFS()  //����������� ʹ�ö�ջ
{
	stack<int> gStack;
	vertexList[0]->wasVisited = true;
	showVertex(0);
	gStack.push(0); //ѹ���ջ
	int v;
	while (gStack.size() > 0)
	{
		v = getAdjUnvisitedVertex(gStack.top());
		if (v == -1)   //û����һ��
			gStack.pop();
		else {
			vertexList[v]->wasVisited = true;
			showVertex(v);
			gStack.push(v); //ѹ���ջ
		}
	}
	cout << endl;
	for (int i = 0; i < nVerts; i++)
		vertexList[i]->wasVisited = false;  //���������������Ϊfalse �Ա�������
}
int MatrixGragh::getAdjUnvisitedVertex(int v)  //������һ��
{
	for (int j = 0; j < nVerts; j++)
	{
		if ((adjMat[v][j] == 1) && (vertexList[j]->wasVisited == false))  //�鿴�Ƿ��ڽӵĶ���δ�����ʹ���
			return j;
	}
	return -1;
}
