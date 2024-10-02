//
// Created by 85147 on 9/28/2024.
//

#include "FeatureMerge.h"

FeatureMerge::FeatureMerge(QOccDocument* mDoc) : FeatureBase(mDoc) {

}

FeatureMerge::~FeatureMerge() {

}

void FeatureMerge::addFeature() {
    qDebug()<<"[LOG] Adding feature to renderer...";

    if(m_hShape.Shape().IsNull()) {
        qDebug()<<"[ERROR]: addFeature trying to add a null shape";
        return;
    }

    TDF_Label shapelabel = m_document->GetShapeRoot().NewChild();
    Handle(XCAFDoc_ShapeTool) tool = XCAFDoc_ShapeTool::Set(m_document->GetShapeRoot());
    tool->SetShape(shapelabel, m_hShape.Shape());
    SetLabel(shapelabel);

    TNaming_Builder featureNaming(m_label);
    featureNaming.Generated(m_hShape.Shape());

}

void FeatureMerge::createRenderPipeline() {
    qDebug()<<"test";
}

void FeatureMerge::UpdatePipeline() {

}
