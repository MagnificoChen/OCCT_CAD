#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QDebug>

#include "DialogBase.h"
#include "DialogFeatureBase.h"
#include "QPushButton"
#include "QLabel"
#include "QDoubleSpinBox"

class DialogFeatureCylinder : public DialogFeatureBase
{
    Q_OBJECT

public:
    DialogFeatureCylinder(QWidget* parent);
    ~DialogFeatureCylinder();
    void OnApply() override;
    void OnCancel() override;
    void OnOK() override;

public:
    void DisableAllGeoSelector() override;
    void OnOpenPosDialog();
    void OnPosReceived();

private:
    QLabel* m_cubeRadiusLabel;
    QDoubleSpinBox* m_cubeRadiusSpinbox;
    QLabel* m_cubeHeightLabel;
    QDoubleSpinBox* m_cubeHeightSpinbox;


    QPushButton* m_buttonOpenPosDialog;

};


