#include "stdafx.h"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include "AdiListGragh.h"
using namespace std;

AdiListGragh::AdiListGragh()
{
}


AdiListGragh::~AdiListGragh()
{
}

void AdiListGragh::addVertex(char lab)
{
	AdjNode* adjNode = new AdjNode();
	adjNode->vertex = lab;
	m_AdjNodeList[lab] = adjNode;
}

void AdiListGragh::addEdge(char lab, list<char> adjLabs)
{
	addVertex(lab);
	if (adjLabs.size() > 0)
	{
		node* preNode = new node();
		node* headNode = preNode;
		preNode->adj_vertex = adjLabs.front();
		for each (char var in adjLabs)
		{
			if (preNode->adj_vertex == var)
			{
				continue;
			}

			node* curNd = new node();
			curNd->adj_vertex = var;
			preNode->next = curNd;
			preNode = curNd;
		}
		m_AdjNodeList[lab]->first = headNode;
	}
}

void AdiListGragh::PrintAdiListGragh()
{
	if (m_AdjNodeList.size() == 0)
	{
		return;
	}

	map<char, AdjNode*>::iterator iter;
	for (iter = m_AdjNodeList.begin(); iter != m_AdjNodeList.end(); iter++)
	{
		cout << iter->first << ": ";
		node* curNode = iter->second->first;
		while (1)
		{
			if (curNode == nullptr)
			{
				break;
			}
			cout << curNode->adj_vertex << ' ';
			curNode = curNode->next;
		}
		cout << endl;
	}
}

void AdiListGragh::showVertex(char v)
{
	cout << v << " ";
}

void AdiListGragh::DFS()
{
	stack<char> gStack;
	map<char, AdjNode*>::iterator iter = m_AdjNodeList.begin();
	if (iter != m_AdjNodeList.end())
	{
		iter->second->wasVisited = true;
		showVertex(iter->second->vertex);
		gStack.push(iter->second->vertex); //压入堆栈
	}


	int v;
	while (gStack.size() > 0)
	{
		v = getAdjUnvisitedVertex(gStack.top());
		if (v == -1)   //没有下一个
			gStack.pop();
		else {
			m_AdjNodeList[v]->wasVisited = true;
			showVertex(v);
			gStack.push(v); //压入堆栈
		}
	}
	cout << endl;

  //搜索完后重新设置为false 以便多次搜索
	for (iter = m_AdjNodeList.begin(); iter != m_AdjNodeList.end(); iter++)
	{
		iter->second->wasVisited = false;
	}

}

void AdiListGragh::BFS()
{
	queue<char> gQueue;
	map<char, AdjNode*>::iterator iter = m_AdjNodeList.begin();
	if (iter != m_AdjNodeList.end())
	{
		iter->second->wasVisited = true;
		showVertex(iter->second->vertex);
		gQueue.push(iter->second->vertex);
	}

	char Vert1, Vert2;
	while (gQueue.size() > 0)
	{
		Vert1 = gQueue.front();
		gQueue.pop();
		Vert2 = getAdjUnvisitedVertex(Vert1);
		while (Vert2 != -1)
		{
			m_AdjNodeList[Vert2]->wasVisited = true;
			showVertex(Vert2);
			gQueue.push(Vert2);
			Vert2 = getAdjUnvisitedVertex(Vert1);
		}
	}
	cout << endl;
	for (iter = m_AdjNodeList.begin(); iter != m_AdjNodeList.end(); iter++)
	{
		iter->second->wasVisited = false;
	}
}

char AdiListGragh::getAdjUnvisitedVertex(char v)
{
	if (m_AdjNodeList[v]->first != nullptr)
	{
		node* curNd = m_AdjNodeList[v]->first;
		while (curNd)
		{
			if (m_AdjNodeList[curNd->adj_vertex]->wasVisited == false)
			{
				return curNd->adj_vertex;
			}
			curNd = curNd->next;
		}
	}
	
	return -1;
}
