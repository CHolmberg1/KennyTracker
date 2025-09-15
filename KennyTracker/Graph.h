#pragma once
#include <vector>
#include <QString>
#include <QPoint>
#include <QImage>

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
		Edge* newEdge = new Edge(connectingNode->getX()- getX(), connectingNode->getY() - getY(), this, connectingNode);
		m_edges.push_back(newEdge);
		connectingNode->m_edges.push_back(newEdge);
		return newEdge;
	}
	std::vector<Edge*> getEdges() {
		return m_edges;
	}
private:
	// Coordinates on the blacksburg map
	const int m_id;
	const double m_x;
	const double m_y;
	std::vector<Edge*> m_edges;
};

class Graph;

class Kenny {
public:
	Kenny();
	QPoint getKennyPos();
	void setKennyTarget(int currentNodeID, int targetNodeID);
	void setGraph(Graph* graph) { m_graphPtr = graph; }
public slots:
	void update();
private:
	QPointF m_location;
	QImage m_kennyPic;
	Graph* m_graphPtr;
	double m_direction;
	Node* m_targetNode;
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
	Node* getNodeByID(int nodeID);
private:
	void addNode(const double x, const double y, bool isSubNode = false);
	std::vector<Node*> m_nodes;
	std::vector<Edge*> m_allEdges;
};