#pragma once
#include <iterator>
#include <iostream>


#include <sstream>
#include <string>
#include <map>


using namespace std;



template <class T>
class Node
{
	std::map<Node<T>*, int> neighbours;
	Node<T>* parent;
	T value;

public:
	

	// A node with a value, neighbours and cost paths
	Node(T);
	// Returns node's value
	T GetNodeValue();
	// Returns the map with neighbours and the cost of the path
	std::map<Node<T>*, int> GetNeighbours();
	// Check if a node is a neighbour
	bool IsNeighbour(Node<T>*);

	// Add a new neighbour to the map
	void AddNeighbour(Node<T>*, int);
	// Remove a new neighbour to the map
	void RemoveNeighbour(Node<T>*);
	// Change a neighbour's path cost
	void ChangeNeighbourEdgeWeight(Node<T>*, int);
	
	// Helping nodes when traversing and building paths //

	// Set the parent of this node
	void SetParentNode(Node<T>*);
	// Get parent node
	Node<T>* GetParentNode();

	bool visited = false;

	
	// Printing functions //

	// Print the neighbours and the cost of their path
	void PrintNeighbours();
};


// A node with a value, neighbours and cost paths
template <class T>
Node<T>::Node(T valueOfNode)
{
	value = valueOfNode;
}
// Get this node value
template <class T>
T Node<T>::GetNodeValue() {
	return value;
}
// Returns the map with neighbours and the cost of the path
template <class T>
std::map<Node<T>*, int> Node<T>::GetNeighbours() {
	return neighbours;
}
// Check if a node is a neighbour
template <class T>
bool Node<T>::IsNeighbour(Node<T>* nodeToCheck) {
	for (auto itr = neighbours.begin(); itr != neighbours.end(); ++itr) {
		if (itr->first == nodeToCheck) {
			return true;
		}
	}
	
	return false;
}

// Add a new neighbour to the map
template <class T>
void Node<T>::AddNeighbour(Node<T>* node, int weightOfEdge) {
	if (!IsNeighbour(node)) {
		neighbours.insert ({ node, weightOfEdge });
	}
	
}
// Remove a new neighbour to the map
template <class T> 
void Node<T>::RemoveNeighbour(Node<T>* node) {
	if (IsNeighbour(node)) {
		neighbours.erase(node);
	}
}
// Change a neighbour's path cost
template <class T>
void Node<T>::ChangeNeighbourEdgeWeight(Node<T>* nodeToChange, int newWeight) {
	if (IsNeighbour(nodeToChange)) {
		
		auto itr = neighbours.find(nodeToChange);
		itr->second = newWeight;
	}

}

// Utility function when traversing trees or building paths
template <class T>
Node<T>* Node<T>::GetParentNode()
{
	return parent;
}
// Utility function when traversing trees or building paths
template <class T>
void Node<T>::SetParentNode(Node<T>* node)
{
	parent = node;
}

// Print the neighbours and the cost of their path
template <class T>
void Node<T>::PrintNeighbours() {
	cout << "\nNeighbours of node: " << GetNodeValue() <<'\n';
	for (auto itr = neighbours.begin(); itr != neighbours.end(); ++itr) {
		cout << itr->first->GetNodeValue() << "  cost: " << itr->second << '\n';
	}
}

