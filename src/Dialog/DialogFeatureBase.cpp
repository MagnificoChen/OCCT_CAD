#include "DialogFeatureBase.h"

#include "src/QDocumentManager.h"

DialogFeatureBase::DialogFeatureBase(QWidget* parent):DialogBase(parent,OkCancel)
{
    m_vLayout = new QVBoxLayout();
    GetMainLayout()->insertLayout(0, m_vLayout);


}

bool DialogFeatureBase::AddFeatureToDocument()
{
    if (feature_to_be_added == nullptr) return false;

    feature_to_be_added->addFeature();
    return true;
}

bool DialogFeatureBase::AddSelector(QOccGeoSelector* selector) {

    if(!selector)return false;
    else{
        selectors.push_back(selector);
        connect(selector, &QOccGeoSelector::OnDisableOtherSelectors,this , &DialogFeatureBase::DisableAllSelector);
    }
}

void DialogFeatureBase::DisableAllSelector() {
    for(auto item:selectors){
        if(item == sender()) continue;
        item->Disable();
    }
}