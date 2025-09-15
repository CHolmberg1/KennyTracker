#include "Graph.h"
#include <QFile>
#include <QTextStream>

#define PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
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

// KENNY METHODS

Kenny::Kenny() : m_kennyPic("kenny.png"), m_graphPtr(nullptr), m_location(QPoint(250,250)), m_direction(PI), m_targetNode(nullptr)
{}

QPoint Kenny::getKennyPos() 
{
    return m_location.toPoint();
}

void Kenny::setKennyTarget(int currentNodeID, int targetNodeID) 
{
    static bool first = true;
    if (!m_graphPtr)
        return;
    Node* currNode = m_graphPtr->getNodeByID(currentNodeID);
    m_targetNode = m_graphPtr->getNodeByID(targetNodeID);
    Edge* targetEdge = nullptr;
    if (!currNode)
        return;
    if (first)
    {
        m_location = QPointF(currNode->getX(), currNode->getY());
        first = false;
    }
    if (!m_targetNode)
        return;
    for (auto& i : m_graphPtr->getEdges()) 
    {
        if (!i)
            continue;
        if ((i->m_link.first == currNode && i->m_link.second == m_targetNode) || (i->m_link.first == m_targetNode && i->m_link.second == currNode))
        {
            targetEdge = i;
        }
    }
    // TODO
    if (!targetEdge)
        return;
    if (targetEdge->m_link.first == currNode) 
        m_direction = atan2(targetEdge->m_dy, targetEdge->m_dx);
    else
        m_direction = atan2(-targetEdge->m_dy, -targetEdge->m_dx);
}

void Kenny::update()
{
    static double dx = 0.0, dy = 0.0;
    double x = m_location.x();
    double y = m_location.y();
    m_location.setX(x + cos(m_direction));
    m_location.setY(y + sin(m_direction));
    if (!m_targetNode) 
    {
        // Set a new target
    }
    if (m_location.toPoint() == QPoint(m_targetNode->getX(), m_targetNode->getY())
        || ((m_location.x() < m_targetNode->getX() && cos(m_direction) < 0) || (m_location.x() > m_targetNode->getX() && cos(m_direction) > 0)
        && (m_location.y() < m_targetNode->getY() && sin(m_direction) < 0) || (m_location.y() > m_targetNode->getY() && sin(m_direction) > 0)))
    {
        // We reached the target, set a random adjacent node as the next one!
        std::size_t edge = rand() % m_targetNode->getEdges().size();
        auto edgeLink = m_targetNode->getEdges()[edge]->m_link;
        int targetID;
        if (edgeLink.first == m_targetNode)
            targetID = edgeLink.second->getUniqueID();
        else
            targetID = edgeLink.first->getUniqueID();
        setKennyTarget(m_targetNode->getUniqueID(), targetID);
    }
}