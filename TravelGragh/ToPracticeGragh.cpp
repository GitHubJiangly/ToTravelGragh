#include "stdafx.h"
#include <iostream>
#include "ToPracticeGragh.h"


ToPracticeGragh::ToPracticeGragh()
{
	InitGragh();
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
	cout << vertex << " ";
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

void ToPracticeGragh::TravelGragh(TravelType travelType)
{
	if (travelType == TravelType::DFS)
	{
		cout << endl << endl << "DFS: " << endl;
		_DFSTravelPaths.clear();
	}	
	else if (travelType == TravelType::BFS)
	{
		cout << endl << endl << "BFS: " << endl;
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
	AddEdges('A', list<char>{'B', 'D'});
	AddEdges('B', list<char>{'A', 'E'});
	AddEdges('C', list<char>{'E'});
	AddEdges('D', list<char>{'A', 'E'});
	AddEdges('E', list<char>{'B', 'C', 'D'});

	AddEdges('a', list<char>{'b', 'd'});
	AddEdges('b', list<char>{'a', 'e'});
	AddEdges('c', list<char>{'e'});
	AddEdges('d', list<char>{'a', 'e'});
	AddEdges('e', list<char>{'b', 'c', 'd'});
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
