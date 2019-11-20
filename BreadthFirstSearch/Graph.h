#pragma once
#include <fstream>
#include <iostream>
#include <sstream>

#include <vector>
#include <list>

#include "Node.h"


void split(std::string str, std::string splitBy, std::vector<std::string>& tokens)
{
	/* Store the original string in the array, so we can loop the rest
	 * of the algorithm. */
	tokens.push_back(str);

	// Store the split index in a 'size_t' (unsigned integer) type.
	size_t splitAt;
	// Store the size of what we're splicing out.
	size_t splitLen = splitBy.size();
	// Create a string for temporarily storing the fragment we're processing.
	std::string frag;
	// Loop infinitely - break is internal.
	while (true)
	{
		/* Store the last string in the vector, which is the only logical
		 * candidate for processing. */
		frag = tokens.back();
		/* The index where the split is. */
		splitAt = frag.find(splitBy);
		// If we didn't find a new split point...
		if (splitAt == string::npos)
		{
			// Break the loop and (implicitly) return.
			break;
		}
		/* Put everything from the left side of the split where the string
		 * being processed used to be. */
		tokens.back() = frag.substr(0, splitAt);
		/* Push everything from the right side of the split to the next empty
		 * index in the vector. */
		tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
	}
}

template<class T>
class Graph {
	Node<T>* rootNode = nullptr;
	list<Node<T>*> listOfNodes;
	
public:
	const char *path = "C:/Users/Alex/Desktop/graph.txt";

	void SetRootNode(Node<T>* root) {
		rootNode = root;
		cout << "\nRoot setted to node with value: " << rootNode->GetNodeValue() << "\n\n";
	}

	list<Node<T>*> GetListOfNodes() {
		return listOfNodes;
	}

	void BreadthFirstSearch() {
		list<Node<T>*> queue;
		rootNode->visited = true;
		queue.push_back(rootNode);
		cout << "\n---Starting BFS from root: " << rootNode->GetNodeValue() << "\n\n";

		while (!queue.empty()) {
			Node<T>* currentNode = queue.front();
			queue.pop_front();
			cout << "Current node: " << currentNode->GetNodeValue() << ",  -Neighbours: ";

			for (auto const& x : currentNode->GetNeighbours())
			{
				cout << x.first->GetNodeValue() << ", ";
				if (x.first->visited == false) {
					x.first->visited = true;
					queue.push_back(x.first);
				}

			}
			cout << "\n\n";
		}
	}
	// Add a new node to this graph. Returns true if were able
	Node<T>* AddNewNode(T value) {
		cout << " \nTrying to add node with value: " << value << "...  ";
		Node<T>* newNode = DoesNodeWithValueExist(value);
		if (newNode != nullptr) {
			cout << "  Node already exists \n";
			return newNode;
		}
		else {
			Node<T>* newNode = new Node<T>(value);
			listOfNodes.push_back(newNode);
			cout << "  New node created \n";
			return newNode;
		}

	}

	Node<T>* DoesNodeExist(Node<T>* nodeToSearch) {

		for (auto it = listOfNodes.begin(); it != listOfNodes.end(); ++it) {
			if (listOfNodes[it] == nodeToSearch) {
				return listOfNodes[it];
			}
		}
		return nullptr;
	}

	Node<T>* DoesNodeWithValueExist(T valueToSeach) {
		cout << "  Searching for node with value: " << valueToSeach << "... ";
		for (auto const& x : listOfNodes) {

			if (x->GetNodeValue() == valueToSeach) {
				cout << " Node found: " << x->GetNodeValue() << '\n';
				return x;
			}
		}
		cout << " Could NOT find node with value: " << valueToSeach << '\n';
		return nullptr;
	}

	void ReadNodesFromFile() {
		int numberOfLines = 0;
		ifstream infile;
		infile.open(path);
		if (!infile) {
			cerr << "Unable to open file datafile.txt";
			exit(1);   // call system to stop
		}
		std::string line;
		cout << "File opened succesfuly" << '\n';
		while (std::getline(infile, line)) {

			std::vector<std::string> results;
			cout << "\n\nFirst line: " << line << "  ";
			split(line, ":", results);
			auto it1 = std::next(results.begin(), 1);
			cout << " -New node string: " << results.front() << "  -Neighbours line: " << *it1 << '\n';
			std::stringstream convertedToNode(results.front());
			T value;
			convertedToNode >> value;
			results.erase(results.begin());
			Node<T>* newNode =AddNewNode(value);
			string neighbours = results.front();
			results.clear();
			split(neighbours, ",", results);
			for (string it : results) {
				std::stringstream convertedNeighbour(it);
				convertedNeighbour >> value;
				Node<T>* newNeighbourNode = AddNewNode(value);
				newNode->AddNeighbour(newNeighbourNode, 0);
			}
			numberOfLines++;
		}
		infile.close();
		cout << "\n\n SUM OF LINES = " << numberOfLines << "\n\n";
	}
};

