//
// Created by 85147 on 9/24/2024.
//

#ifndef OCCT_CAD_DIALOGFEATURECHAMFER_H
#define OCCT_CAD_DIALOGFEATURECHAMFER_H


#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include "src/Dialog/Components/QOccEdgeSelector.h"
#include "src/Dialog/Components/QOccShellSelector.h"
#include "DialogFeatureBase.h"

enum FILLET_TYPE {
     FILLET_CHAMFER = 0,
     FILLET_FILLET,
};

class DialogFeatureChamfer : public DialogFeatureBase{
Q_OBJECT
public:
    explicit DialogFeatureChamfer(QWidget* parent);

    virtual ~DialogFeatureChamfer();

public:
    QLabel* m_radiusLabel;

    QLabel* m_comboBoxLabel;
    QComboBox* m_comboBox;
    QDoubleSpinBox* m_blendRadiusSpinbox;

    QOccEdgeSelector* m_selectorEdge;
    QOccShellSelector* m_selectorShape;

    void OnApply() override;

    void DisableAllGeoSelector() override;

    QComboBox* m_blendTypeComboBox;

public:
    void OnOK() override;
    void OnCancel() override;

private:
    FILLET_TYPE _curType = FILLET_CHAMFER;

    void OnComboBoxChanged(int index);
};


#endif //OCCT_CAD_DIALOGFEATURECHAMFER_H
