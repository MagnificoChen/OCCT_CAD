#pragma once
#include <TDocStd_Document.hxx>
#include <TopoDS_Shape.hxx>
#include <vtkRenderer.h>
#include <BRepBuilderAPI_Transform.hxx>
#include <TNaming_Builder.hxx>

#include "src/QOccDocument.h"

enum class FeatureType
{
    F_VERTEX,
    F_EDGE
};

//需要初始化TDFLabel后执行构造函数
class FeatureBase : public QObject
{
public:
    FeatureBase();
    virtual ~FeatureBase();
    //
    void addFeature();
    TDF_Label m_label;
    //自定义tag
    int m_tag = -1;
    //OCAF Tag
    int m_shapeTag;
    TopoDS_Shape m_shape;


signals:
    // void positionChanged();

public:

    void SetPosition(vtkVector3d pos);

    void SetLabel(TDF_Label label);
    TDF_Label GetLabel();

    void SetTag(int tag);
    int GetTag();

private:
    vtkVector3d m_pos = { 0,0,0 };
    QOccDocument* m_document;
};

