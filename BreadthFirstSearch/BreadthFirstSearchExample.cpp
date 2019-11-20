// TreeStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"


#include "Graph.h"





template <class T>
void Test() {
	Node<T>* newNode = new Node<T>(0);
	Node<T>* newNode1 = new Node<T>(1);
	Node<T>* newNode2 = new Node<T>(2);
	Node<T>* newNode3 = new Node<T>(3);
	
	newNode->AddNeighbour(newNode1, 0);
	newNode->AddNeighbour(newNode2, 0);
	
	newNode1->AddNeighbour(newNode2, 0);

	newNode2->AddNeighbour(newNode, 0);
	newNode2->AddNeighbour(newNode3, 0);

	newNode3->AddNeighbour(newNode3, 0);

	Graph<int>* g = new Graph<int>();
	g->SetRootNode(newNode2);
	g->BreadthFirstSearch();
	
}

int main()
{
	Graph<string>* g = new Graph<string>();
	g->ReadNodesFromFile();
	g->SetRootNode(g->DoesNodeWithValueExist("2"));
	g->BreadthFirstSearch();
	return 0;

}

