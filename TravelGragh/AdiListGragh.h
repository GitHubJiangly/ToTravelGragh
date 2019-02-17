#pragma once
#include <map>
#include <vector>
#include <queue>
#include <list>
using namespace std;

struct node {
	char adj_vertex;
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
	void DFS2(char v);  //�����������
	void TravelGraghByDFS2();
	//void BFS();  //�����������
	void BFS2(char v);  //�����������
	void TravelGraghByBFS2();
private:
	map<char, AdjNode*> m_AdjNodeList;
	char getAdjUnvisitedVertex(char v);
	void TravelVertex(char v);
	void TravelVertex2(char v,queue<char>& qTraveled);
	vector<char> getAllUnvistedVertex(char v);
	void addVertex(char lab);
	map<char, char> m_parentNode;
};
