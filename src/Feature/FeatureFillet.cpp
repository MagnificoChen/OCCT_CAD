//
// Created by 85147 on 10/2/2024.
//

#include "FeatureFillet.h"
//
// Created by 85147 on 9/25/2024.
//

#include <TNaming_Tool.hxx>
#include "FeatureChamfer.h"
#include "BRepFilletAPI_MakeFillet.hxx"
#include "BRepTools.hxx"
#include "TNaming_NamedShape.hxx"



FeatureFillet::FeatureFillet(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Edge edge) : FeatureAttach(mDoc) {

    m_solid = shape;
    m_edge = edge;
    auto chamfer = BRepFilletAPI_MakeFillet(shape);
    chamfer.Add(edge);
    m_hShape.Shape(chamfer.Shape());

    m_shape = m_hShape.Shape();


    addFeature();
}

FeatureFillet::FeatureFillet(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Edge edge, double r) : FeatureAttach(mDoc) {

    //TODO: 判断r的合法性
    if(r<0) return;

    m_solid = shape;
    m_edge = edge;

    auto chamfer = BRepFilletAPI_MakeFillet(shape);
    chamfer.Add(r, edge);
    m_hShape.Shape(chamfer.Shape());

//    Handle(XCAFDoc_ShapeTool) tool = XCAFDoc_ShapeTool::Set(m_document->GetShapeRoot());
//    auto test = tool->FindSubShape(m_solid);
//    qDebug()<<test.Tag();

    m_shape = m_hShape.Shape();

    addFeature();
}

FeatureFillet::~FeatureFillet() {

}

void FeatureFillet::addFeature() {
    //暂时屏蔽父类的addfeature方法
    //FeatureAttach::addFeature();

}
void FeatureFillet::updateFeature(){
    //刷新attachlist的TDF_Label
    for(auto item: m_attachList){
        Handle(TNaming_NamedShape) hAttr;
        item.FindAttribute(TNaming_NamedShape::GetID(),hAttr);
        TNaming_Builder builder(item);
        builder.Modify(TNaming_Tool::GetShape(hAttr), m_hShape.Shape());
//        _attachedRenderPipeline->updatePrimaryPipeline()
    }
}
