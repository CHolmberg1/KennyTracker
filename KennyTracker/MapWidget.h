#pragma once

#include <QtWidgets/QWidget>
#include <QPainter>
#include <QEvent>

struct PaintCoordinates 
{
	QPointF p1;
	QPointF p2;
};

struct NodeCoordinates 
{
	QPointF p1;
	QString id;
};

class MapWidget : public QWidget 
{

	Q_OBJECT

public:
	MapWidget(QWidget* parent = nullptr);
	void setNodes(std::vector<NodeCoordinates> nodes);
	void setNodesShown(bool nodesShown) { m_nodesShown = nodesShown; update(); }
	bool nodesShown() { return m_nodesShown; }
	void setEdges(std::vector<PaintCoordinates> edges);
	void setEdgesShown(bool edgesShown) { m_edgesShown = edgesShown; update(); }
	bool edgesShown() { return m_edgesShown; }
	void setKennyPos(QPoint kennyPos);
	const QPoint getCursorPos() const;
protected:
	void paintEvent(QPaintEvent *event) override;
	void mousePressEvent(QMouseEvent* event) override;
private:
	std::vector<NodeCoordinates> m_nodes;
	std::vector<PaintCoordinates> m_edges;
	QPoint m_cursorPos;
	bool m_nodesShown, m_edgesShown;
	QPoint m_kennyPos;
};