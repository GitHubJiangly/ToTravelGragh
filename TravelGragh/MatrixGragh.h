#pragma once
/**ʹ���ڽӾ�������ʾһ��ͼ**/

#define MAX_VERTS 20

class Vertex
{
public:
	Vertex(char lab)
	{
		Label = lab;
		wasVisited = false;
	}
	bool wasVisited;   //����Ƿ񱻷��ʹ�
	char Label;
};

class MatrixGragh
{
public:
	MatrixGragh();
	~MatrixGragh();
	void addVertex(char lab);
	void addEdge(int Start, int End);  //��ӱ�
	void PrintMatrix(); //��ӡ����
	void showVertex(int v);
	void DFS();  //�����������
	void BFS();  //�����������
private:
	Vertex* vertexList[MAX_VERTS]; //��ඥ�������
	int nVerts;     //ʵ�����鶥�������
	int adjMat[MAX_VERTS][MAX_VERTS];  //��֤
	int getAdjUnvisitedVertex(int v);
};

