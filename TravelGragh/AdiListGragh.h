#pragma once
#include <map>
#include <list>
using namespace std;

struct node {
	char adj_vertex;
	//int weight; /* For network */
	struct node *next;
};

struct AdjNode {
	char vertex;
	bool wasVisited;   //����Ƿ񱻷��ʹ�
	struct node *first;
};

class AdiListGragh
{
public:
	AdiListGragh();
	~AdiListGragh();
	void addEdge(char lab, list<char> adjLabs);  //��ӱ�
	void PrintAdiListGragh(); //��ӡ����
	void showVertex(char v);
	void DFS();  //�����������
	void BFS();  //�����������

private:
	map<char, AdjNode*> m_AdjNodeList;
	char getAdjUnvisitedVertex(char v);
	void addVertex(char lab);
};
