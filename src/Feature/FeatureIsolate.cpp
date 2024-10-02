//
// Created by 85147 on 9/28/2024.
//

#include "FeatureIsolate.h"
#include "src/OccDemoMainWindow.h"

FeatureIsolate::FeatureIsolate(QOccDocument* mDoc) : FeatureBase(mDoc) {


}



FeatureIsolate::~FeatureIsolate() {

}

void FeatureIsolate::addFeature() {
    qDebug()<<"[LOG] Adding feature to OCAF...";

    if(m_hShape.Shape().IsNull()) {
        qDebug()<<"[ERROR]: addFeature trying to add a null shape to OCAF, aborting...";
        return;
    }

    TDF_Label shapeLabel = m_document->GetShapeRoot().NewChild();
    Handle(XCAFDoc_ShapeTool) tool = XCAFDoc_ShapeTool::Set(m_document->GetShapeRoot());
    tool->SetShape(shapeLabel, m_hShape.Shape());
    SetLabel(shapeLabel);

    TNaming_Builder featureNaming(m_label);
    featureNaming.Generated(m_hShape.Shape());

}

void FeatureIsolate::createRenderPipeline() {
    if(m_hShape.Shape().IsNull()) {
        qDebug()<<"[ERROR]: createRenderPipeline trying to create a null shape";
        return;
    }

    Handle(QOccVtkSelPipeline) pipeline = new QOccVtkSelPipeline(m_hShape.Shape(), m_label.Tag());
    _attachedRenderPipeline = pipeline;
    //添加
    OccDemoMainWindow::getInstance()->getCentralWidgetByDocument(m_document)->addPipelineToRenderer(pipeline);
}

void FeatureIsolate::UpdatePipeline() {

}
