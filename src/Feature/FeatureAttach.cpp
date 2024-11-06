//
// Created by 85147 on 9/28/2024.
//

#include <TNaming.hxx>
#include "FeatureAttach.h"
#include "TNaming_NamedShape.hxx"
#include "TNaming_Builder.hxx"
#include "TNaming_Tool.hxx"

FeatureAttach::FeatureAttach(QOccDocument* mDoc) : FeatureBase(mDoc) {

}

FeatureAttach::~FeatureAttach() {

}

void FeatureAttach::addFeature() {
    qDebug() << "[LOG] Adding feature to renderer...";

    if (m_hShape.Shape().IsNull()) {
        qDebug() << "[ERROR]: addFeature trying to add a null shape";
        return;
    }

    TDF_Label shapelabel = m_document->GetShapeRoot().NewChild();
    Handle(XCAFDoc_ShapeTool) tool = XCAFDoc_ShapeTool::Set(m_document->GetShapeRoot());
    tool->SetShape(shapelabel, m_hShape.Shape());
    SetLabel(shapelabel);

    TNaming_Builder featureNaming(m_label);
    featureNaming.Generated(m_hShape.Shape());
}



void FeatureAttach::AddToAttachList(const Standard_Integer tag) {
    auto label = m_document->GetShapeRoot().FindChild(tag, false);
    if (label.IsNull()) {
        qDebug()<<"[ERROR]: Could not find TDF_Label by Tag.";
        return;
    }
    m_attachList.push_back(label);
}