//
// Created by 85147 on 9/24/2024.
//

#include <TopoDS_Solid.hxx>
#include "DialogFeatureChamfer.h"

#include "TopExp_Explorer.hxx"
#include "../Feature/FeatureChamfer.h"
#include "../Dialog/Components/QOccEdgeSelector.h"
#include "../QDocumentManager.h"
#include "BRepTools.hxx"

DialogFeatureChamfer::DialogFeatureChamfer(QWidget* parent)
        : DialogFeatureBase(parent){

    QHBoxLayout* layout = new QHBoxLayout();
    m_comboBox = new QComboBox();
    m_comboBox->addItems({"倒圆角","倒斜角"});
    m_comboBox->setCurrentIndex(0);
    connect(m_comboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &DialogFeatureChamfer::OnComboBoxChanged);
    m_comboBoxLabel = new QLabel("倒角模式：");

    layout->addWidget(m_comboBoxLabel, 1);
    layout->addWidget(m_comboBox, 2);
    m_vLayout->addLayout(layout);


    layout = new QHBoxLayout();
    m_radiusLabel = new QLabel("半径：");
    m_blendRadiusSpinbox = new QDoubleSpinBox();
    m_blendRadiusSpinbox->setValue(2);
    layout->addWidget(m_radiusLabel, 1);
    layout->addWidget(m_blendRadiusSpinbox, 2);
    m_vLayout->addLayout(layout);


    m_selectorEdge = new QOccEdgeSelector(getOwnerWidget());
    m_selectorShape = new QOccShellSelector(getOwnerWidget());
    m_vLayout->addWidget(m_selectorEdge);
    m_vLayout->addWidget(m_selectorShape);
    AddSelector(m_selectorShape);
    AddSelector(m_selectorEdge);

    GetMainLayout()->insertLayout(0,layout);
}

DialogFeatureChamfer::~DialogFeatureChamfer() {

}

void DialogFeatureChamfer::OnOK() {
    if(!m_selectorEdge->isDataValid() || !m_selectorShape->isDataValid()){
        done(QDialog::Rejected);
        return;
    }
    else{

        FeatureChamfer feature(QDocumentManager::getInstance()->getCurrentDocument(),m_selectorShape->getSelectedShape(), TopoDS::Edge(m_selectorEdge->getSelectedShape() ),0.1);

        feature.AddToAttachList(m_selectorShape->GetTag());
        feature.updateFeature();
        getOwnerWidget()->UpdateView();
    }
    done(QDialog::Accepted);

}

void DialogFeatureChamfer::OnCancel() {

    done(QDialog::Rejected);
}

void DialogFeatureChamfer::OnApply() {

}

void DialogFeatureChamfer::DisableAllGeoSelector() {

}
void DialogFeatureChamfer::OnComboBoxChanged(int index) {
    _curType = static_cast<FILLET_TYPE>(index);
}

