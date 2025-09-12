#include "MapWidget.h"

MapWidget::MapWidget(QWidget* parent) : QWidget(parent), m_nodesShown(false), m_edgesShown(false)
{
	setMinimumSize(500, 500);
    setMouseTracking(true);
}

void MapWidget::mousePressEvent(QMouseEvent* event) 
{
    m_cursorPos = cursor().pos();
    update();
}

void MapWidget::paintEvent(QPaintEvent* event) 
{
    static bool first = false;
    QPainter p(this);

    if (!first) 
    {
        // Draw Map Image
        p.drawImage(QPoint(-100, 0), QImage("blacksburg_map.png"));
    }
    p.setPen(QPen(Qt::red, 5));
    p.setBrush(QBrush(Qt::green));
    if (m_nodesShown)
    {
        for (auto& i : m_nodes) 
        {
            p.drawPoint(i.p1);
            p.drawText(i.p1, i.id);
        }
    }
    p.setPen(QPen(Qt::blue, 2));
    p.setBrush(QBrush(Qt::green));
    if (m_edgesShown)
    {
        for (auto& i : m_edges)
        {
            p.drawLine(int(i.p1.x()), int(i.p1.y()), int(i.p2.x()), int(i.p2.y()));
        }
    }
    p.drawText(QPoint(450, 450), QString::number(m_cursorPos.x()) + ',' + QString::number(m_cursorPos.y()));
    //p.drawRect(50, 50, 100, 75); // x, y, width, height
}

void MapWidget::setEdges(std::vector<PaintCoordinates> edges) 
{
    m_edges = edges;
}

void MapWidget::setNodes(std::vector<NodeCoordinates> nodes)
{
    m_nodes = nodes;
}

const QPoint MapWidget::getCursorPos() const
{
    return m_cursorPos;
}