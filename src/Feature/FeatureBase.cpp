#include "FeatureBase.h"

#include <BRepPrimAPI_MakeSphere.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include "TNaming_NamedShape.hxx"
#include "TNaming.hxx"

#include "src/QDocumentManager.h"


FeatureBase::FeatureBase()
{
    m_document = QDocumentManager::getInstance()->getCurrentDocument();
}

FeatureBase::~FeatureBase()
{
}


void FeatureBase::addFeature()
{
    if(m_shape.IsNull()) return;

    TDF_Label shapelabel = m_document->GetShapeRoot().NewChild();
    Handle(XCAFDoc_ShapeTool) tool = XCAFDoc_ShapeTool::Set(m_document->GetShapeRoot());
    tool->SetShape(shapelabel, m_shape);
    SetLabel(shapelabel);

    TNaming_Builder featureNaming(m_label);
    featureNaming.Generated(m_shape);


    m_document->getCentralWidget()->addShapeToRenderer(m_shape);
}



void FeatureBase::SetPosition(vtkVector3d pos)
{
    m_pos = pos;

    // 创建一个平移变换
    gp_Trsf transformation2;
    transformation2.SetTranslation(gp_Vec{ 0,20,0 });
    // 应用变换
    BRepBuilderAPI_Transform transform2(m_shape, transformation2, false , true);
    TopLoc_Location loc(transformation2);
    TNaming::Displace(m_label, loc, Standard_True);

    //发出一个消息，让OCAF刷新
    //emit positionChanged();
}

void  FeatureBase::SetLabel(TDF_Label label)
{
    m_label = label;
}

TDF_Label FeatureBase::GetLabel()
{
    return m_label;
}

void FeatureBase::SetTag(int tag)
{
    m_tag = tag;
}

int FeatureBase::GetTag()
{
    return m_tag;
}



