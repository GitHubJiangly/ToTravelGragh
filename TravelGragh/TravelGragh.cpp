// TravelGragh.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#include "MatrixGragh.h"
#include "AdiListGragh.h"
#include "ToPracticeGragh.h"



#if 0
void InitMatrixGragh(MatrixGragh &g)
{
	g.addVertex('A');
	g.addVertex('B');
	g.addVertex('C');
	g.addVertex('D');
	g.addVertex('E');

	g.addEdge(0, 1);  //A-B
	g.addEdge(0, 3);  //A-D
	g.addEdge(1, 0);  //B-A
	g.addEdge(1, 4);  //B-E
	g.addEdge(2, 4);  //C-E
	g.addEdge(3, 0);  //D-A
	g.addEdge(3, 4);  //D-E
	g.addEdge(4, 1);  //E-B
	g.addEdge(4, 2);  //E-C
	g.addEdge(4, 3);  //E-D
}
void InitAdiListGragh(AdiListGragh &g)
{
	g.addEdge('A', list<char>{'B', 'D'});
	g.addEdge('B', list<char>{'A', 'E'});
	g.addEdge('C', list<char>{'E'});
	g.addEdge('D', list<char>{'A', 'E'});
	g.addEdge('E', list<char>{'B', 'C', 'D'});
}
int main()
{
	// test MatrixGragh
	cout << "To test MatrixGragh:" << endl;
	MatrixGragh g;
	InitMatrixGragh(g);
	g.PrintMatrix();
	cout << "DFS:" << endl;
	g.DFS();
	cout << "BFS:" << endl;
	g.BFS();


	// test AdiListGragh
	cout << endl << endl << endl;

	cout << "To test AdiListGragh:" << endl;
	AdiListGragh adjListGragh;
	InitAdiListGragh(adjListGragh);
	adjListGragh.PrintAdiListGragh();
	cout << "DFS:" << endl;
	adjListGragh.TravelGraghByDFS2();
	cout << "BFS:" << endl;
	adjListGragh.TravelGraghByBFS2();


	return 0;
}
#endif

void main()
{
	ToPracticeGragh gragh;
	gragh.PrintGragh();
	gragh.TravelGragh(TravelType::BFS);
	gragh.TravelGragh(TravelType::DFS);
}



