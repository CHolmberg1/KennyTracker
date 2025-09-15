#include "KennyTracker.h"
#include <QKeyEvent>
#include <QTimer>
#include <QThread>

#define kennyloop while(1 != 0)

KennyTracker::KennyTracker(QWidget *parent)
    : QMainWindow(parent), m_graph(new Graph()), m_kenny(new Kenny())
{
    ui.setupUi(this);
    m_mapWidget = new MapWidget(this);
    setCentralWidget(m_mapWidget);
    m_graph->loadNodes("testData.csv");
    // Kenny Thread
    QThread* updateThread = QThread::create([this]() {
        startKenny();
        });
    updateThread->start();
    renderGraph();
}

KennyTracker::~KennyTracker()
{}

void KennyTracker::keyPressEvent(QKeyEvent* event) 
{
    if (event->key() == Qt::Key_F11)
    {
        if (!window()->isFullScreen())
        {
            window()->showFullScreen();
        }
        else
        {
            window()->showMaximized();
        }
    }
    if (event->key() == Qt::Key_0)
    {
        if (m_mapWidget->edgesShown())
        {
            m_mapWidget->setEdgesShown(false);
        }
        else
        {
            m_mapWidget->setEdgesShown(true);
        }
    }
    if (event->key() == Qt::Key_1)
    {
        if (m_mapWidget->nodesShown())
        {
            m_mapWidget->setNodesShown(false);
        }
        else
        {
            m_mapWidget->setNodesShown(true);
        }
    }
    if (event->key() == Qt::Key_S)
    {
        m_graph->saveEdges("edges.csv");
    }
}

void KennyTracker::renderGraph() 
{
    // Render Nodes
    std::vector<Node*> nodes = m_graph->getNodes();
    std::vector<NodeCoordinates> nodeVec;
    for (auto* i : nodes) 
    {
        if (!i)
            continue;
        NodeCoordinates coords;
        coords.p1 = QPointF(i->getX(), i->getY()-20);
        coords.id = QString::number(i->getUniqueID());
        nodeVec.push_back(coords);
    }
    m_mapWidget->setNodes(nodeVec);
    // Render Edges
    std::vector<Edge*> edges = m_graph->getEdges();
    std::vector<PaintCoordinates> coordVec;
    for (auto* i : edges) 
    {
        if (!i)
            continue;
        PaintCoordinates coords;
        coords.p1 = QPointF(i->m_link.first->getX(), i->m_link.first->getY()-20);
        coords.p2 = QPointF(i->m_link.second->getX(), i->m_link.second->getY()-20);
        coordVec.push_back(coords);
    }
    m_mapWidget->setEdges(coordVec);
    // Render Kenny!!!
    m_mapWidget->setKennyPos(m_kenny->getKennyPos());
    update();
}

void KennyTracker::startKenny() 
{
    int k = 1;
    m_kenny->setGraph(m_graph);
    m_kenny->setKennyTarget(0, 1);
    while (k != 0) 
    {
        m_kenny->update();
        m_mapWidget->setKennyPos(m_kenny->getKennyPos());
        update();
        QThread::msleep(50);
    }
}