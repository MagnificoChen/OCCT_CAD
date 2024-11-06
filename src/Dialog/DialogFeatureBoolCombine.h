//
// Created by 85147 on 10/8/2024.
//

#ifndef OCCT_CAD_DIALOGFEATUREBOOLCOMBINE_H
#define OCCT_CAD_DIALOGFEATUREBOOLCOMBINE_H


#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>
#include "src/Dialog/Components/QOccEdgeSelector.h"
#include "src/Dialog/Components/QOccShellSelector.h"
#include "DialogFeatureBase.h"


class DialogFeatureBoolCombine : public DialogFeatureBase{
Q_OBJECT
public:
    explicit DialogFeatureBoolCombine(QWidget* parent);

    virtual ~DialogFeatureBoolCombine();

public:


    QOccShellSelector* m_selectorShape1;
    QOccShellSelector* m_selectorShape2;

    void OnApply() override;

    void DisableAllGeoSelector() override;


public:
    void OnOK() override;
    void OnCancel() override;

private:


};




#endif //OCCT_CAD_DIALOGFEATUREBOOLCOMBINE_H
