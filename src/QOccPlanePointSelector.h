#pragma once
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <QToolButton>
#include <TopoDS_Shape.hxx>

#include "CentralViewWidget.h"
class QOccPlanePointSelector: public QWidget
{

    Q_OBJECT

public:
    QOccPlanePointSelector(QWidget* parent = nullptr);
    ~QOccPlanePointSelector();

signals:



public slots:
    //处理并发出信号

private:
    QHBoxLayout* m_layout;
    QLabel* m_label;
    QToolButton* m_button;

    CentralViewWidget* ownerWidget = nullptr;

    //
    bool _isSelectModeChangeable = false;
};