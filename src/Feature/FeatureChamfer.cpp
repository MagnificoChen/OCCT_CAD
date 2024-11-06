//
// Created by 85147 on 9/25/2024.
//

#include <TNaming_Tool.hxx>
#include "FeatureChamfer.h"
#include "BRepFilletAPI_MakeChamfer.hxx"
#include "BRepTools.hxx"
#include "TNaming_NamedShape.hxx"
#include "TopExp.hxx"

TopoDS_Shape FeatureChamfer::FindParentSolidOrShell(const TopoDS_Edge& edge, const TopoDS_Shape& fullShape)
{
    TopTools_IndexedDataMapOfShapeListOfShape edgeAncestorMap;

    // 创建从 Edge 到 Solid 的映射
    TopExp::MapShapesAndAncestors(fullShape, TopAbs_EDGE, TopAbs_SOLID, edgeAncestorMap);

    if (edgeAncestorMap.Contains(edge))
    {
        const TopTools_ListOfShape& parentSolids = edgeAncestorMap.FindFromKey(edge);
        if (!parentSolids.IsEmpty())
        {
            return parentSolids.First();
        }
    }

    // 如果没有找到 Solid，尝试查找 Shell
    edgeAncestorMap.Clear();
    TopExp::MapShapesAndAncestors(fullShape, TopAbs_EDGE, TopAbs_SHELL, edgeAncestorMap);

    if (edgeAncestorMap.Contains(edge))
    {
        const TopTools_ListOfShape& parentShells = edgeAncestorMap.FindFromKey(edge);
        if (!parentShells.IsEmpty())
        {
            return parentShells.First();
        }
    }

    return TopoDS_Shape(); // 如果既没有找到 Solid 也没有找到 Shell，返回空形状
}

FeatureChamfer::FeatureChamfer(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Edge edge) : FeatureAttach(mDoc) {

    m_solid = shape;
    m_edge = edge;
    auto chamfer = BRepFilletAPI_MakeChamfer(shape);
    chamfer.Add(edge);
    m_hShape.Shape(chamfer.Shape());

    m_shape = m_hShape.Shape();


    addFeature();
}

FeatureChamfer::FeatureChamfer(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Edge edge, double r) : FeatureAttach(mDoc) {

    //TODO: 判断r的合法性
    if(r<0) return;

    m_solid = shape;
    m_edge = edge;

    auto chamfer = BRepFilletAPI_MakeChamfer(m_solid);
    chamfer.Add(r, edge);
    m_hShape.Shape(chamfer.Shape());

    m_shape = m_hShape.Shape();

    addFeature();
}

FeatureChamfer::~FeatureChamfer() {

}

void FeatureChamfer::addFeature() {
    //暂时屏蔽父类的addfeature方法
    //FeatureAttach::addFeature();

}
void FeatureChamfer::updateFeature(){
    //刷新attachlist的TDF_Label
    for(auto item: m_attachList){
        Handle(TNaming_NamedShape) hAttr;
        item.FindAttribute(TNaming_NamedShape::GetID(),hAttr);
        TNaming_Builder builder(item);
        builder.Modify(TNaming_Tool::GetShape(hAttr), m_hShape.Shape());
    }

}
