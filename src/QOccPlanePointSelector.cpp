#include "QOccPlanePointSelector.h"



QOccPlanePointSelector::QOccPlanePointSelector(QWidget* parent)
    : QWidget(parent)
{
    //init components
    m_layout = new QHBoxLayout(this);
    m_label = new QLabel("选择线");
    m_button = new QToolButton();
    m_button->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_button->setAutoRaise(true);
    m_button->setIcon(QIcon(":/image/resource/cube.png"));


    m_layout->addWidget(m_label);
    m_layout->addWidget(m_button);
    QAction* action;
    
}


QOccPlanePointSelector::~QOccPlanePointSelector()
{
    
}