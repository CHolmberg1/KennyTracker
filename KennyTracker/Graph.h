#pragma once
#include <vector>
#include <QString>
#include <QPoint>

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
	Node(const double x, const double y) : m_x(x), m_y(y), m_id(createUniqueID()) {}
	~Node() {}
	const double getX() { return m_x; }
	const double getY() { return m_y; }
	const int createUniqueID() { static int i = 0; return i++; }
	const int getUniqueID() { return m_id; }
	Edge* addEdge(Node* connectingNode) 
	{
		if (!connectingNode)
			return nullptr;
		for (auto* i : m_edges) 
		{
			if ((i->m_link.first == this && i->m_link.second == connectingNode) || (i->m_link.first == connectingNode && i->m_link.second == this))
				return nullptr; // Edge already exists!
		}
		Edge* newEdge = new Edge(abs(getX() - connectingNode->getX()), abs(getY() - connectingNode->getY()), this, connectingNode);
		m_edges.push_back(newEdge);
		connectingNode->m_edges.push_back(newEdge);
		return newEdge;
	}
private:
	// Coordinates on the blacksburg map
	const int m_id;
	const double m_x;
	const double m_y;
	std::vector<Edge*> m_edges;
};

class Graph {
public:
	Graph();
	~Graph();
	void loadNodes(QString fileName);
	void loadEdges(QString fileName);
	const std::vector<Edge*> getEdges();
	const std::vector<Node*> getNodes();
	void saveEdges(QString fileName);
private:
	void addNode(const double x, const double y, bool isSubNode = false);
	Node* getNodeByID(int nodeID);
	std::vector<Node*> m_nodes;
	std::vector<Edge*> m_allEdges;
};