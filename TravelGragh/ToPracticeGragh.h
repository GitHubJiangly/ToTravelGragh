#pragma once
#include <map>
#include <vector>
#include <queue>
#include <list>
#include <stack>
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
	void TravelGragh(TravelType travelType);
	void PrintGragh();
	bool JudgeContainCircle();
private:
	void InitGragh();
	void AddEdges(char vertex, list<char> adjVerList);

	bool TravelVertex(char vertex);
	void TravelVertexAndPushToQueue(char vertex, queue<char>& qVers);
	void TravelVertexAndPushToStack(char vertex, stack<char>& sVers);

	vector<char> GetAdjUnVisitedVers(char ver);
	vector<char> GetAdjVers(char ver);
	bool GetAdjUnVisitedVer(char ver, char& adjVer);

	void DFS(char ver);
	void ToJudgeCircleByDFS(char ver, int parentVer);
	void DFSByStack(char ver);
	void BFS(char ver);

private:
	map<char, VNode*> _VertexList;
	vector<vector<char>> _DFSTravelPaths;
	vector<vector<char>> _BFSTravelPaths;
	vector<char> _CurrentTravelPath;
	bool _ContainCircle;
};

