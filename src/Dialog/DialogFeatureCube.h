#pragma once

#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QDebug>

#include "DialogBase.h"
#include "DialogFeatureBase.h"
#include "QPushButton"
#include "QLabel"
#include "QDoubleSpinBox"

class DialogFeatureCube : public DialogFeatureBase
{
    Q_OBJECT

public:
    DialogFeatureCube(QWidget* parent);
    ~DialogFeatureCube();
    void OnApply() override;
    void OnCancel() override;
    void OnOK() override;

public:
    void DisableAllGeoSelector() override;
    void OnOpenPosDialog();
    void OnPosReceived();

private:
    QLabel* m_cubeXLabel;
    QDoubleSpinBox* m_cubeXSpinbox;
    QLabel* m_cubeYLabel;
    QDoubleSpinBox* m_cubeYSpinbox;
    QLabel* m_cubeZLabel;
    QDoubleSpinBox* m_cubeZSpinbox;

    QPushButton* m_buttonOpenPosDialog;

};
