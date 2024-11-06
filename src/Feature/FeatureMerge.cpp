//
// Created by 85147 on 9/28/2024.
//

#include "FeatureMerge.h"
#include "src/OccDemoMainWindow.h"

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

//TODO 未完成类行为：融合特征产出的几何体可能是多个，目前仅处理一个的情况
void FeatureMerge::createRenderPipeline() {
    if(m_hShape.Shape().IsNull()) {
        qDebug()<<"[ERROR]: createRenderPipeline trying to create a null shape";
        return;
    }

    Handle(QOccVtkSelPipeline) pipeline = new QOccVtkSelPipeline(m_hShape.Shape(), m_label.Tag());
    _attachedRenderPipeline = pipeline;
    //添加
    OccDemoMainWindow::getInstance()->getCentralWidgetByDocument(m_document)->addPipelineToRenderer(pipeline);
}

void FeatureMerge::UpdatePipeline() {

}


void FeatureMerge::AddToDeleteList(const Standard_Integer tag) {
    auto label = m_document->GetShapeRoot().FindChild(tag, false);
    if (label.IsNull()) {
        qDebug()<<"[ERROR]: Could not find TDF_Label by Tag.";
        return;
    }
    m_deleteList.push_back(label);
}


void FeatureMerge::AddToModifyList(const Standard_Integer tag) {
    auto label = m_document->GetShapeRoot().FindChild(tag, false);
    if (label.IsNull()) {
        qDebug()<<"[ERROR]: Could not find TDF_Label by Tag.";
        return;
    }
    m_modifyList.push_back(label);
}