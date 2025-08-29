#pragma once
#include <vector>
#include <QString>

class Node;

struct Edge {
	// Constructor
	Edge(const double dx, const double dy, Node* n1, Node* n2) { m_dx = dx; m_dy = dy; m_link = std::make_pair(n1, n2); }
	// Distance deltas TODO: Find units suitable for this use case
	double m_dx;
	double m_dy;
	// Edge Link (statically two nodes per link)
	std::pair<Node*, Node*> m_link;
};

class Node {
public:
	Node(const double x, const double y) : m_x(x), m_y(y) {}
	~Node() {}
	const double getX() { return m_x; }
	const double getY() { return m_y; }
	void addEdge(Node* connectingNode) 
	{
		if (!connectingNode)
			return;
		for (auto* i : m_edges) 
		{
			if ((i->m_link.first == this && i->m_link.second == connectingNode) || (i->m_link.first == connectingNode && i->m_link.second == this))
				return; // Edge already exists!
		}
		Edge* newEdge = new Edge(abs(getX() - connectingNode->getX()), abs(getY() - connectingNode->getY()), this, connectingNode);
		m_edges.push_back(newEdge);
		connectingNode->m_edges.push_back(newEdge);
	}
private:
	// Coordinates on the blacksburg map
	const double m_x;
	const double m_y;
	std::vector<Edge*> m_edges;
};

class Graph {
public:
	Graph();
	~Graph();
	void loadNodes(QString fileName);
private:
	void addNode(const double x, const double y, bool isSubNode = false);
	void removeNode(const double x, const double y); // May replace with ID if more practical
	std::vector<Node*> m_nodes;
};