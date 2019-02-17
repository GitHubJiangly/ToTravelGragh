#include "stdafx.h"
#include <iostream>
#include "ToPracticeGragh.h"


ToPracticeGragh::ToPracticeGragh()
{
	InitGragh();
	_ContainCircle = false;
}

ToPracticeGragh::~ToPracticeGragh()
{
	map<char, VNode*>::iterator it = _VertexList.begin();
	while (it  != _VertexList.end())
	{
		ENode* eN = it->second->firstNode;
		ENode* curN = eN;
		while (eN)
		{
			curN = eN;
			eN = eN->Next;
			delete curN;
		}
		delete it->second;
		it++;
	}
}

void ToPracticeGragh::AddEdges(char vertex, list<char> adjVerList)
{
	VNode* vN = new VNode(vertex, false);
	ENode* firstNode = nullptr;
	ENode* preEN = nullptr;
	for each(char adjV in adjVerList)
	{
		ENode* eN = new ENode(adjV);
		if (firstNode == nullptr)
		{
			firstNode = eN;
		}
		else
		{
			preEN->Next = eN;
		}
		preEN = eN;
	}

	vN->firstNode = firstNode;
	_VertexList[vertex] = vN;
}

bool ToPracticeGragh::TravelVertex(char vertex)
{
	if (_VertexList[vertex]->Traveled == true)
	{
		return false;
	}
	//cout << vertex << " ";
	_CurrentTravelPath.push_back(vertex);
	_VertexList[vertex]->Traveled = true;

	return true;
}

void ToPracticeGragh::TravelVertexAndPushToQueue(char vertex, queue<char>& qVers)
{
	if (TravelVertex(vertex))
	{
		qVers.push(vertex);
	}
}

void ToPracticeGragh::TravelVertexAndPushToStack(char vertex, stack<char>& sVers)
{
	if (TravelVertex(vertex))
	{
		sVers.push(vertex);
	}
}

void ToPracticeGragh::DFS(char ver)
{
	TravelVertex(ver);
	char adjV;
	if (GetAdjUnVisitedVer(ver, adjV))
	{
		DFS(adjV);
	}
}

void ToPracticeGragh::ToJudgeCircleByDFS(char ver, int parentVer)
{
	TravelVertex(ver);
	vector<char> adjVers = GetAdjVers(ver);
	for each (char adjV in adjVers)
	{
		if (!_VertexList[adjV]->Traveled)
		{
			ToJudgeCircleByDFS(adjV, ver);
		}
		else if (adjV != parentVer) // adjV、parentVer已经被遍历过， 它们同属ver先前节点，则形成环
		{
			_ContainCircle = true;
			return;
		}
	}		
}

void ToPracticeGragh::ToJudgeBinaryGragh(char ver)
{
	TravelVertex(ver);
	if (_BinaryColor.find(ver) == _BinaryColor.end())
	{
		_BinaryColor[ver] = true;
	}
	vector<char> adjVers = GetAdjVers(ver);
	for each (char adjV in adjVers)
	{
		if (!_VertexList[adjV]->Traveled)
		{
			_BinaryColor[adjV] = !_BinaryColor[ver];
			ToJudgeBinaryGragh(adjV);
		}
		else if (_BinaryColor[adjV] == _BinaryColor[ver]) // 相邻节点的颜色相同，一定不是二分图
		{
			_BinaryGragh = false;
			return;
		}
	}
}

void ToPracticeGragh::DFSByStack(char ver)
{
	stack<char> sVers;
	TravelVertexAndPushToStack(ver, sVers);
	while (sVers.size() > 0)
	{
		char adjV;
		if (GetAdjUnVisitedVer(sVers.top(), adjV))
		{
			TravelVertexAndPushToStack(adjV, sVers);
		}
		else
		{
			sVers.pop();
		}
	}
}

void ToPracticeGragh::BFS(char ver)
{
	queue<char> qVers;
	TravelVertexAndPushToQueue(ver, qVers);
	while (qVers.size() > 0)
	{
		for each (char adjV in GetAdjUnVisitedVers(qVers.front()))
		{
			TravelVertexAndPushToQueue(adjV, qVers);
		}
		qVers.pop();
	}
}

bool ToPracticeGragh::JudgeContainCircle()
{
	_ContainCircle = false;
	map<char, VNode*>::iterator it = _VertexList.begin();
	while (it != _VertexList.end())
	{
		if (!it->second->Traveled)
		{
			ToJudgeCircleByDFS(it->first, it->first);
		}

		it++;
	}

	it = _VertexList.begin();
	while (it != _VertexList.end())
	{
		it->second->Traveled = false;
		it++;
	}

	return _ContainCircle;
}

bool ToPracticeGragh::JudgeBinaryGragh()
{
	_BinaryGraghPath.clear();
	map<char, VNode*>::iterator it = _VertexList.begin();
	while (it != _VertexList.end())
	{
		if (!it->second->Traveled)
		{
			_BinaryGragh = true;
		  ToJudgeBinaryGragh(it->first);
			_BinaryGraghPath.push_back(_BinaryGragh);
		}

		it++;
	}

	it = _VertexList.begin();
	while (it != _VertexList.end())
	{
		it->second->Traveled = false;
		it++;
	}

	for each (bool isBinaryGragh in _BinaryGraghPath)
	{
		if (isBinaryGragh)
		{
			return true;
		}
	}
	return false;
}

void ToPracticeGragh::TravelGragh(TravelType travelType)
{
	if (travelType == TravelType::DFS)
	{
		_DFSTravelPaths.clear();
	}	
	else if (travelType == TravelType::BFS)
	{
		_BFSTravelPaths.clear();
	}

	map<char, VNode*>::iterator it = _VertexList.begin();
	while (it != _VertexList.end())
	{
		if (!it->second->Traveled)
		{
			if (travelType == TravelType::DFS)
			{
				_CurrentTravelPath.clear();
				DFSByStack(it->first);
				//DFS(it->first);
				if (_CurrentTravelPath.size() > 0)
				{
					_DFSTravelPaths.push_back(_CurrentTravelPath);
				}
			}
			else if (travelType == TravelType::BFS)
			{
				_CurrentTravelPath.clear();
				BFS(it->first);
				if (_CurrentTravelPath.size() > 0)
				{
					_BFSTravelPaths.push_back(_CurrentTravelPath);
				}
			}
		}
	
		it++;
	}


	if (travelType == TravelType::DFS)
	{
		cout << "DFS: " << endl;
		int iPath = 0;
		for each (vector<char> path in _DFSTravelPaths)
		{
			cout << "Path " << ++iPath << " :" << endl;
			for each (char ver in path)
			{
				cout << ver << " ";
			}
			cout << endl;
		}
	}
	else if (travelType == TravelType::BFS)
	{
		cout << endl  << "BFS: " << endl;
		int iPath = 0;
		for each (vector<char> path in _BFSTravelPaths)
		{
			cout << "Path " << ++iPath << " :" << endl;
			for each (char ver in path)
			{
				cout << ver << " ";
			}
			cout << endl;
		}
	}


	it = _VertexList.begin();
	while (it != _VertexList.end())
	{
		it->second->Traveled = false;
		it++;
	}
	cout << endl;
}

vector<char> ToPracticeGragh::GetAdjUnVisitedVers(char ver)
{
	vector<char> retData;
	ENode* curN = _VertexList[ver]->firstNode;
	while (curN)
	{
		if (!_VertexList[curN->Vertex]->Traveled)
		{
			retData.push_back(curN->Vertex);
		}
		curN = curN->Next;
	}

	return retData;
}

vector<char> ToPracticeGragh::GetAdjVers(char ver)
{
	vector<char> retData;
	ENode* curN = _VertexList[ver]->firstNode;
	while (curN)
	{
  	retData.push_back(curN->Vertex);
		curN = curN->Next;
	}

	return retData;
}

bool ToPracticeGragh::GetAdjUnVisitedVer(char ver, char& adjVer)
{
	ENode* curN = _VertexList[ver]->firstNode;
	while (curN)
	{
		if (!_VertexList[curN->Vertex]->Traveled)
		{
			adjVer = curN->Vertex;
			return true;
		}
		curN = curN->Next;
	}

	return false;
}

void ToPracticeGragh::InitGragh()
{
	AddEdges('A', list<char>{'B'});
	AddEdges('B', list<char>{'A'});

	AddEdges('a', list<char>{'b'});
	AddEdges('b', list<char>{'c'});
	AddEdges('c', list<char>{'a'});
}

void ToPracticeGragh::PrintGragh()
{
	map<char, VNode*>::iterator it = _VertexList.begin();
	while (it != _VertexList.end())
	{
		cout << it->first << ": ";
		ENode* eN = it->second->firstNode;
		while (eN)
		{
			cout << eN->Vertex <<" ";
			eN = eN->Next;
		}

		cout <<endl;
		it++;
	}
}
