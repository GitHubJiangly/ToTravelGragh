#pragma once
#include <map>
#include <vector>
#include <queue>
#include <list>
using namespace std;

struct ENode
{
	ENode(char v)
		: Vertex(v), Next(nullptr) {}
	char Vertex;
	ENode* Next;
};

struct VNode
{
	VNode(char v, bool bTra)
		: Vertex(v), Traveled(bTra){}
	char Vertex;
	bool Traveled;
	ENode* firstNode;
};
enum TravelType
{
	DFS = 0,
	BFS
};
class ToPracticeGragh
{
public:
	ToPracticeGragh();
	~ToPracticeGragh();
	void AddEdges(char vertex, list<char> adjVerList);
	bool TravelVertex(char vertex);
	void TravelVertex(char vertex, queue<char>& qVers);
	void DFS(char ver);
	void BFS(char ver);
	void TravelGragh(TravelType travelType);
	vector<char> GetAdjUnVisitedVers(char ver);
	void InitGragh();
	void PrintGragh();
private:
	map<char, VNode*> _VertexList;
};

