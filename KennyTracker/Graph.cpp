#include "Graph.h"
#include <QFile>

Graph::Graph() 
{

}

Graph::~Graph() 
{

}

void Graph::loadNodes(QString fileName) 
{
    // Parse node coords from CSV
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) 
    {
        return;
    }

    QStringList wordList;
    while (!file.atEnd()) 
    {
        QString line = file.readLine();
        QStringList words = line.split(',');
        for(auto &i : words)
            wordList.append(i);
    }
    if (wordList.size() % 2 != 0)
        return; // We have an uneven amount of coordinates!
    for (qsizetype i = 0; i < wordList.size(); i = i + 2) 
    {
        addNode(wordList[i].toDouble(), wordList[i + 1].toDouble());
    }
    for (auto* i : m_nodes) {
        for (auto* j : m_nodes) {
            if (i == j)
                continue;
            i->addEdge(j); // Add edges to connect every node
        }
    }
    m_nodes[0];
}
void Graph::addNode(const double x, const double y, bool isSubNode) 
{
    Node* newNode = new Node(x, y);
    if (isSubNode) 
    {
        // TODO
    }
    m_nodes.push_back(newNode);
}
void Graph::removeNode(const double x, const double y) 
{
    // TODO: Check if node is at position and remove
}