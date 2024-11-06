#pragma once

#include <TDocStd_Document.hxx>
#include <TopoDS_Shape.hxx>
#include <vtkRenderer.h>
#include <BRepBuilderAPI_Transform.hxx>
#include <TNaming_Builder.hxx>
#include <TopoDS_HShape.hxx>

#include "src/QOccDocument.h"


//需要初始化TDFLabel后执行构造函数
class FeatureBase : public QObject {
public:
    FeatureBase(QOccDocument* m_doc);

    virtual ~FeatureBase();

    //添加feature
    virtual void addFeature() = 0;

    //刷新渲染
    virtual void UpdatePipeline(const TopoDS_Shape& newShape) {} ;

signals:
    // void positionChanged();

public:


    void SetPosition(vtkVector3d pos);

    //获取所属Document
    QOccDocument* getDocument() { return m_document; }

    void SetLabel(TDF_Label label);

    TDF_Label GetLabel();

    //获取Label的Tag
    Standard_Integer GetTag();

private:

    //渲染用的实体

    //坐标系
    gp_Ax3 _axis;

    //位置
    vtkVector3d m_pos = {0, 0, 0};

    //是否可修改
    bool m_bCanModefied = false;

protected:
    TopoDS_HShape m_hShape;
    //对应的Shape数据
    TopoDS_Shape m_shape;

    //文档指针
    QOccDocument* m_document;

    //在OCAF中的Label
    TDF_Label m_label;

    //渲染数据
    Handle(QOccVtkSelPipeline) _attachedRenderPipeline;
};

