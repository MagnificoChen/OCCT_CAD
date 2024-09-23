#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QDebug>

#include "DialogBase.h"
#include "DialogFeatureBase.h"
#include "QPushButton"
#include "QLabel"
#include "QDoubleSpinBox"



class DialogInputPosition :
    public QDialog
{
    Q_OBJECT
public:
    DialogInputPosition(Qt::WindowFlags f = Qt::Dialog);
    ~DialogInputPosition() override;
    void OnOK();
    void OnCancel();


private:
    QLabel* m_cubeXLabel;
    QDoubleSpinBox* m_cubeXSpinbox;
    QLabel* m_cubeYLabel;
    QDoubleSpinBox* m_cubeYSpinbox;
    QLabel* m_cubeZLabel;
    QDoubleSpinBox* m_cubeZSpinbox;

    QPushButton* m_OK;
    QPushButton* m_Cancel;

    QVBoxLayout* m_layout;
};

