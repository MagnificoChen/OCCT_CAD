#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QDebug>

#include "DialogBase.h"
#include "QPushButton"
#include "QLabel"
#include "QDoubleSpinBox"
#include "src/OccDemoMainWindow.h"
#include "src/QDocumentManager.h"

class DialogFeatureSphere : public DialogBase
{
    Q_OBJECT

public:
    DialogFeatureSphere(QWidget* parent);
    ~DialogFeatureSphere();
    void OnApply() override;
    void OnCancel() override;
    void OnOK() override;

public:
    //
    void DisableAllGeoSelector() override;
private:
    QLabel* m_cubeRadiusLabel;
    QLabel* m_cubeXLabel;
    QLabel* m_cubeYLabel;
    QLabel* m_cubeZLabel;
    QDoubleSpinBox* m_cubeXSpinbox;
    QDoubleSpinBox* m_cubeYSpinbox;
    QDoubleSpinBox* m_cubeZSpinbox;
    QDoubleSpinBox* m_cubeRadiusSpinbox;
};
