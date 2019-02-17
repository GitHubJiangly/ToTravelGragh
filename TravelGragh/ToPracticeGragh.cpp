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
			delete eN;
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
	_VertexList[vertex]->Traveled = true;

	return true;
}

void ToPracticeGragh::TravelVertex(char vertex, queue<char>& qVers)
{
	if (TravelVertex(vertex))
	{
		qVers.push(vertex);
	}
}

void ToPracticeGragh::DFS(char ver)
{
	TravelVertex(ver);
	vector<char> adjVers = GetAdjUnVisitedVers(ver);
	for each (char adjV in adjVers)
	{
		DFS(adjV);
	}
}

void ToPracticeGragh::BFS(char ver)
{
	queue<char> qVers;
	TravelVertex(ver, qVers);
	while (qVers.size() > 0)
	{
		for each (char adjV in GetAdjUnVisitedVers(qVers.front()))
		{
			TravelVertex(adjV, qVers);
		}
	  qVers.pop();
	}
}

void ToPracticeGragh::TravelGragh(TravelType travelType)
{
	if (travelType == TravelType::DFS)
	{
		cout << endl << endl << "DFS: " << endl;
	}	
	else if (travelType == TravelType::BFS)
	{
		cout << endl << endl << "BFS: " << endl;
	}

	map<char, VNode*>::iterator it = _VertexList.begin();
	while (it != _VertexList.end())
	{
		if (!it->second->Traveled)
		{
			if (travelType == TravelType::DFS)
			{
				DFS(it->first);
			}
			else if (travelType == TravelType::BFS)
			{
				BFS(it->first);
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