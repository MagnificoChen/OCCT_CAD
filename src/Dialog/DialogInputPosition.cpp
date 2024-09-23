#include "DialogInputPosition.h"

DialogInputPosition::DialogInputPosition(Qt::WindowFlags f)
{
    m_cubeXLabel = new QLabel("输入X");
    m_cubeXSpinbox = new QDoubleSpinBox();
    m_layout = new QVBoxLayout(this);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m_cubeXLabel, 1);
    layout->addWidget(m_cubeXSpinbox, 2);
    m_layout->addLayout(layout);


    m_cubeYLabel = new QLabel("输入Y");
    m_cubeYSpinbox = new QDoubleSpinBox();
    layout = new QHBoxLayout();
    layout->addWidget(m_cubeYLabel, 1);
    layout->addWidget(m_cubeYSpinbox, 2);
    m_layout->addLayout(layout);

    m_cubeZLabel = new QLabel("输入Z");
    m_cubeZSpinbox = new QDoubleSpinBox();
    layout = new QHBoxLayout();
    layout->addWidget(m_cubeZLabel, 1);
    layout->addWidget(m_cubeZSpinbox, 2);
    m_layout->addLayout(layout);

    m_OK = new QPushButton("确认");
    m_Cancel = new QPushButton("取消");
    layout = new QHBoxLayout();
    QSpacerItem* spacer = new QSpacerItem(20, 10);
    layout->addSpacerItem(spacer);
    layout->addWidget(m_OK, 1);
    layout->addWidget(m_Cancel, 1);
    connect(m_OK, &QPushButton::pressed, this,&DialogInputPosition::OnOK);
    connect(m_Cancel, &QPushButton::pressed, this,&DialogInputPosition::OnCancel);

    m_layout->addLayout(layout);

}

DialogInputPosition::~DialogInputPosition()
{
}

void DialogInputPosition::OnOK()
{
    QDialog::accept();
}

void DialogInputPosition::OnCancel()
{
    QDialog::reject();
}


