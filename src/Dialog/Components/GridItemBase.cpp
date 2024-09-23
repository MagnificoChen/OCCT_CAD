#include "GridItemBase.h"
#include <qaction.h>
#include <TColStd_MapOfInteger.hxx>

GridItemBase::GridItemBase(QString mainButtonText)
{
    m_layout = new QHBoxLayout(this);
    m_mainButton = new QToolButton();
    m_mainButton->setText(mainButtonText);
    m_mainButton->setCheckable(true);
    connect(m_mainButton, &QToolButton::toggled, this, &GridItemBase::OnMainButtonToggled);

    m_toolButton1 = new QToolButton();
    m_toolButton1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   


    m_layout->addWidget(m_mainButton, 4);
    m_layout->addWidget(m_toolButton1, 1);
    m_mainButton->setMinimumSize({120, 40});
    m_mainButton->setMaximumWidth(1000);
    m_toolButton1->setMinimumSize({40, 40});
}

BOOL GridItemBase::Create(QDialog* parent, QStringList list1, QList<QIcon> iconList1)
{
    m_pParentDlg = parent;
    mapper1 = new QSignalMapper(this);

    if (list1.size() == iconList1.size())
    {
        m_toolButton1->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        for (int i = 0; i < list1.size(); ++i)
        {
            QAction* pAction = new QAction(list1[i]);
            pAction->setIcon(iconList1[i]);
            m_toolButton1->addAction(pAction);
            mapper1->setMapping(pAction, i);
            connect(mapper1, &QSignalMapper::mappedInt, this, &GridItemBase::OnToolButton1Clicked);
        }
    }
    else
    {
        for (int i = 0; i < list1.size(); ++i)
        {
            QAction* pAction = new QAction(list1[i]);
            m_toolButton1->addAction(pAction);
            mapper1->setMapping(pAction, i);
            connect(mapper1, &QSignalMapper::mappedInt, this, &GridItemBase::OnToolButton1Clicked);
        }
    }

    return true;
}

GridItemBase::~GridItemBase()
{
}

void GridItemBase::EnableSecondOption(QStringList list2, QList<QIcon> iconList)
{
    m_toolButton2 = new QToolButton();
    m_toolButton2->setToolButtonStyle(Qt::ToolButtonTextOnly);
    mapper2 = new QSignalMapper(this);

    if (list2.size() == iconList.size())
    {
        m_toolButton2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        for (int i = 0; i < list2.size(); ++i)
        {
            QAction* pAction = new QAction(list2[i]);
            pAction->setIcon(iconList[i]);
            m_toolButton2->addAction(pAction);
            mapper2->setMapping(pAction, i);
            connect(mapper2, &QSignalMapper::mappedInt, this, &GridItemBase::OnToolButton2Clicked);
        }
    }
    else
    {
        for (int i = 0; i < list2.size(); ++i)
        {
            QAction* pAction = new QAction(list2[i]);
            m_toolButton2->addAction(pAction);
            mapper2->setMapping(pAction, i);
            connect(mapper2, &QSignalMapper::mappedInt, this, &GridItemBase::OnToolButton2Clicked);
        }
    }
    m_layout->addWidget(m_toolButton2, 1);
    m_toolButton2->setMinimumSize({40, 40});
}

void GridItemBase::BindButton1Function(std::function<void(int)> func)
{
    button1ItemFunction = func;
}

void GridItemBase::BindButton2Function(std::function<void(int)> func)
{
    button2ItemFunction = func;
}


void GridItemBase::OnToolButton1Clicked(int index)
{
    if (button1ItemFunction)
    {
        button1ItemFunction(index);
    }
}

void GridItemBase::OnToolButton2Clicked(int index)
{
    if (button2ItemFunction)
    {
        button2ItemFunction(index);
    }
}

void GridItemBase::OnFocus()
{
}

void GridItemBase::OnUnFocus()
{
}



void GridItemBase::OnMainButtonToggled()
{
    if (m_mainButton->isChecked())
    {
        OnFocus();
    }
    else
    {
        OnUnFocus();
    }
}
