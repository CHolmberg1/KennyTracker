#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_KennyTracker.h"
#include "Graph.h"

class KennyTracker : public QMainWindow
{
    Q_OBJECT

public:
    KennyTracker(QWidget *parent = nullptr);
    ~KennyTracker();

private:
    Ui::KennyTrackerClass ui;
    Graph* m_graph;
};

