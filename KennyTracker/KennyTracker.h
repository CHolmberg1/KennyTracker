#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include "ui_KennyTracker.h"
#include "Graph.h"
#include "MapWidget.h"

class KennyTracker : public QMainWindow
{
    Q_OBJECT

public:
    KennyTracker(QWidget *parent = nullptr);
    ~KennyTracker();

    void renderGraph();

signals:
    void kennyUpdate();
protected:
    void keyPressEvent(QKeyEvent* event) override;
private:
    void startKenny();
    Ui::KennyTrackerClass ui;
    Graph* m_graph;
    MapWidget* m_mapWidget;
    Kenny* m_kenny;
};