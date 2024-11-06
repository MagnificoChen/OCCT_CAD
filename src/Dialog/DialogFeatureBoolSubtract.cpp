//
// Created by 85147 on 10/4/2024.
//

#include "DialogFeatureBoolSubtract.h"
#include "src/Feature/FeatureBoolSubtract.h"
#include "src/QDocumentManager.h"

DialogFeatureBoolSubtract::DialogFeatureBoolSubtract(QWidget* parent) : DialogFeatureBase(parent) {

    m_selectorTool = new QOccShellSelector(getOwnerWidget());
    m_selectorShape = new QOccShellSelector(getOwnerWidget());
    m_vLayout->addWidget(m_selectorShape);
    m_vLayout->addWidget(m_selectorTool);
    AddSelector(m_selectorShape);
    AddSelector(m_selectorTool);

}

DialogFeatureBoolSubtract::~DialogFeatureBoolSubtract() {

}

void DialogFeatureBoolSubtract::OnApply() {

}

void DialogFeatureBoolSubtract::OnOK() {
    if (!m_selectorShape->isDataValid() || !m_selectorTool->isDataValid()) {
        done(QDialog::Rejected);
        return;
    } else {

            FeatureBoolSubtract feature(QDocumentManager::getInstance()->getCurrentDocument(),
                                   m_selectorShape->getSelectedShape(),
                                   m_selectorTool->getSelectedShape());

            feature.AddToModifyList(m_selectorShape->GetTag());
            feature.AddToDeleteList(m_selectorTool->GetTag());

            feature.createRenderPipeline();
            feature.updateFeature();
            //作为修改后的测试
            getOwnerWidget()->UpdateView();
    }
    done(QDialog::Accepted);
}

void DialogFeatureBoolSubtract::OnCancel() {

    done(QDialog::Rejected);
}

void DialogFeatureBoolSubtract::DisableAllGeoSelector() {

}
