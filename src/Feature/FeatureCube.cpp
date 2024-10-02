#include "FeatureCube.h"
#include <BRepFilletAPI_MakeFillet.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>

FeatureCube::FeatureCube(QOccDocument* mDoc, double x, double y, double z) : FeatureIsolate(mDoc), x(x), y(y), z(z) {
    box = BRepPrimAPI_MakeBox(x,y,z);
    m_hShape.Shape(box);

    addFeature();
}
FeatureCube::~FeatureCube()
{
}


void FeatureCube::addFeature() {
    FeatureIsolate::addFeature();
    auto BoxLabel = GetLabel();
    TDF_Label Top1      = BoxLabel.FindChild(1);
    TDF_Label Bottom1   = BoxLabel.FindChild(2);
    TDF_Label Right1    = BoxLabel.FindChild(3);
    TDF_Label Left1     = BoxLabel.FindChild(4);
    TDF_Label Front1    = BoxLabel.FindChild(5);
    TDF_Label Back1     = BoxLabel.FindChild(6);

    TNaming_Builder Box1Ins (BoxLabel);
    Box1Ins.Generated (m_hShape.Shape());

//    TopoDS_Face Top1Face = box.TopFace ();
//    TNaming_Builder Top1FaceIns (Top1);
//    Top1FaceIns.Generated (Top1Face);
//
//    TopoDS_Face Bottom1Face = box.BottomFace ();
//    TNaming_Builder Bottom1FaceIns (Bottom1);
//    Bottom1FaceIns.Generated (Bottom1Face);
//
//    TopoDS_Face Right1Face = box.RightFace ();
//    TNaming_Builder Right1FaceIns (Right1);
//    Right1FaceIns.Generated (Right1Face);
//
//    TopoDS_Face Left1Face = box.LeftFace ();
//    TNaming_Builder Left1FaceIns (Left1);
//    Left1FaceIns.Generated (Left1Face);
//
//    TopoDS_Face Front1Face = box.FrontFace ();
//    TNaming_Builder Front1FaceIns (Front1);
//    Front1FaceIns.Generated (Front1Face);
//
//    TopoDS_Face Back1Face = box.BackFace ();
//    TNaming_Builder Back1FaceIns (Back1);
//    Back1FaceIns.Generated (Back1Face);
}
