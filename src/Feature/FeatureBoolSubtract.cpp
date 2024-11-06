//
// Created by 85147 on 10/4/2024.
//

#include "FeatureBoolSubtract.h"
#include <TNaming_Tool.hxx>
#include "BRepTools.hxx"
#include "BRepAlgoAPI_Cut.hxx"
#include "TNaming_NamedShape.hxx"

FeatureBoolSubtract::FeatureBoolSubtract(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Shape tool) : FeatureMerge(
        mDoc) {

    m_shape = shape;
    m_tool = tool;
    auto subtract = BRepAlgoAPI_Cut(shape, tool);
    m_hShape.Shape(subtract.Shape());

    m_shape = m_hShape.Shape();

    addFeature();
}

FeatureBoolSubtract::~FeatureBoolSubtract() {

}


void FeatureBoolSubtract::addFeature() {
    //暂时屏蔽父类的addfeature方法
    //FeatureAttach::addFeature();
    TDF_Label shapeLabel = m_document->GetShapeRoot().NewChild();
    Handle(XCAFDoc_ShapeTool) tool = XCAFDoc_ShapeTool::Set(m_document->GetShapeRoot());
    tool->SetShape(shapeLabel, m_hShape.Shape());
    SetLabel(shapeLabel);

    TNaming_Builder featureNaming(m_label);
    featureNaming.Generated(m_hShape.Shape());
}

void FeatureBoolSubtract::updateFeature() {
    //刷新List中的的TDF_Label

    //Shape标记为modify
    Handle(TNaming_NamedShape) hAttr;
    m_modifyList[0].FindAttribute(TNaming_NamedShape::GetID(), hAttr);
    TNaming_Builder builderShape(m_modifyList[0]);
//    builderShape.Modify(TNaming_Tool::GetShape(hAttr), m_hShape.Shape());
    builderShape.Delete(TNaming_Tool::GetShape(hAttr));

    //Tool标记为Delete
    for (auto item: m_deleteList) {
        Handle(TNaming_NamedShape) hdAttr;
        item.FindAttribute(TNaming_NamedShape::GetID(), hdAttr);
        TNaming_Builder bs(item);
        bs.Delete(TNaming_Tool::GetShape(hdAttr));
    }

}
