#pragma once
#include <TopoDS_Shape.hxx>

#include "DialogBase.h"
#include "src/Feature/FeatureBase.h"

class DialogFeatureBase :
    public DialogBase
{
    Q_OBJECT
public:
    DialogFeatureBase(QWidget* parent);
    bool AddFeatureToDocument();
public:
    QVBoxLayout* m_vLayout;

private:
    FeatureBase* feature_to_be_added;

};

