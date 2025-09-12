#include "Graph.h"
#include <QFile>
#include <QTextStream>

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
    //for (auto* i : m_nodes) 
    //{
    //    for (auto* j : m_nodes) 
    //    {
    //        if (i == j)
    //            continue;
    //        Edge* val = i->addEdge(j); // Add edges to connect every node
    //        if(val)
    //            m_allEdges.push_back(val);
    //    }
    //}
    loadEdges("edges.csv"); /* Use once all edges are defined */
}

void Graph::loadEdges(QString fileName)
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
        for (auto& i : words)
            wordList.append(i);
    }
    if (wordList.size() % 2 != 0)
        return; // We have an uneven amount of coordinates!
    for (qsizetype i = 0; i < wordList.size(); i = i + 2)
    {
        if (Node* node = getNodeByID(wordList[i].toInt()); node)
        {
            Node* connectingNode = getNodeByID(wordList[i+1].toInt());
            if (connectingNode)
            {
                Edge* val = node->addEdge(connectingNode); // Add edges to connect every node
                m_allEdges.push_back(val);
                continue;
            }
                
        }
        if (Node* node = getNodeByID(wordList[i+1].toInt()); node)
        {
            Node* connectingNode = getNodeByID(wordList[i].toInt());
            if (connectingNode) 
            {
                Edge* val = node->addEdge(connectingNode); // Add edges to connect every node
                m_allEdges.push_back(val);
            }
        }
    }
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

const std::vector<Node*> Graph::getNodes() 
{
    return m_nodes;
}

const std::vector<Edge*> Graph::getEdges() 
{
    return m_allEdges;
}

void Graph::saveEdges(QString fileName) 
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return;
    }
    QTextStream stream(&file);
    for (auto& i : m_allEdges) 
    {
        // CSV
        stream << QString::number(i->m_link.first->getUniqueID()) << ',' << QString::number(i->m_link.second->getUniqueID()) << '\n';
    }
    file.close();
}

Node* Graph::getNodeByID(int nodeID) 
{
    for (auto& i : m_nodes) {
        if (i->getUniqueID() == nodeID)
            return i;
    }
    return nullptr;
}