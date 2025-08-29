#pragma once
#include <vector>
#include <QString>

struct Edge {
	// Distance deltas TODO: Find units suitable for this use case
	double dx;
	double dy;
	// Edge Link (statically two)
	std::pair<Node, Node> m_link;
};

class Node {
public:
	Node(const double x, const double y);
	~Node();
	const double getX();
	const double getY();
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