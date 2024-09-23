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
