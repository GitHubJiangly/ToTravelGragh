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
	bool wasVisited;   //检查是否被访问过
	struct node *first;
};

class AdiListGragh
{
public:
	AdiListGragh();
	~AdiListGragh();
	void addEdge(char lab, list<char> adjLabs);  //添加边
	void PrintAdiListGragh(); //打印矩阵
	void showVertex(char v);
	void DFS();  //深度优先搜索
	void DFS2(char v);  //深度优先搜索
	void TravelGraghByDFS2();
	//void BFS();  //广度优先搜索
	void BFS2(char v);  //广度优先搜索
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
