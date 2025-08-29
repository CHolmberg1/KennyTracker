#include "KennyTracker.h"


KennyTracker::KennyTracker(QWidget *parent)
    : QMainWindow(parent), m_graph(new Graph())
{
    ui.setupUi(this);
}

KennyTracker::~KennyTracker()
{}

