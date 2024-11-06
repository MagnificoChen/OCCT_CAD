//
// Created by 85147 on 10/4/2024.
//

#ifndef OCCT_CAD_DIALOGFEATUREBOOLSUBTRACT_H
#define OCCT_CAD_DIALOGFEATUREBOOLSUBTRACT_H



#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include "src/Dialog/Components/QOccEdgeSelector.h"
#include "src/Dialog/Components/QOccShellSelector.h"
#include "DialogFeatureBase.h"


class DialogFeatureBoolSubtract : public DialogFeatureBase{
Q_OBJECT
public:
    explicit DialogFeatureBoolSubtract(QWidget* parent);

    virtual ~DialogFeatureBoolSubtract();

public:


    QOccShellSelector* m_selectorShape;
    QOccShellSelector* m_selectorTool;

    void OnApply() override;

    void DisableAllGeoSelector() override;


public:
    void OnOK() override;
    void OnCancel() override;

private:


};



#endif //OCCT_CAD_DIALOGFEATUREBOOLSUBTRACT_H
