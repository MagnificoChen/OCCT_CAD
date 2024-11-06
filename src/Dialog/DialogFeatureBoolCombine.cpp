//
// Created by 85147 on 10/8/2024.
//

#include "DialogFeatureBoolCombine.h"


#include "src/Feature/FeatureBoolCombine.h"
#include "src/QDocumentManager.h"

DialogFeatureBoolCombine::DialogFeatureBoolCombine(QWidget* parent) : DialogFeatureBase(parent) {

    m_selectorShape2 = new QOccShellSelector(getOwnerWidget());
    m_selectorShape1 = new QOccShellSelector(getOwnerWidget());
    m_vLayout->addWidget(m_selectorShape1);
    m_vLayout->addWidget(m_selectorShape2);
    AddSelector(m_selectorShape1);
    AddSelector(m_selectorShape2);

}

DialogFeatureBoolCombine::~DialogFeatureBoolCombine() {

}

void DialogFeatureBoolCombine::OnApply() {

}

void DialogFeatureBoolCombine::OnOK() {
    if (!m_selectorShape1->isDataValid() || !m_selectorShape2->isDataValid()) {
        done(QDialog::Rejected);
        return;
    } else {

        FeatureBoolCombine feature(QDocumentManager::getInstance()->getCurrentDocument(),
                                    m_selectorShape1->getSelectedShape(),
                                    m_selectorShape2->getSelectedShape());

        feature.AddToModifyList(m_selectorShape1->GetTag());
        feature.AddToDeleteList(m_selectorShape2->GetTag());

        feature.createRenderPipeline();
        feature.updateFeature();
        //作为修改后的测试
        getOwnerWidget()->UpdateView();
    }
    done(QDialog::Accepted);
}

void DialogFeatureBoolCombine::OnCancel() {

    done(QDialog::Rejected);
}

void DialogFeatureBoolCombine::DisableAllGeoSelector() {

}
