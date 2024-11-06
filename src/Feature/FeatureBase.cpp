#include "FeatureBase.h"

#include <BRepPrimAPI_MakeSphere.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include "TNaming_NamedShape.hxx"
#include "TNaming.hxx"

#include "src/QDocumentManager.h"


FeatureBase::FeatureBase(QOccDocument* m_doc) {
    m_document = m_doc;
}

FeatureBase::~FeatureBase()
{
}


void FeatureBase::SetPosition(vtkVector3d pos)
{
    m_pos = pos;

    gp_Trsf TRSF;
    TRSF.SetTranslation(gp_Vec{ pos.GetX(),pos.GetY(),pos.GetZ() });
    TopLoc_Location loc(TRSF);
    TDF_LabelMap scope;
    TDF_ChildIterator itchild;
    for (itchild.Initialize(m_label,Standard_True); itchild.More();itchild.Next()) {
        if (itchild.Value().IsAttribute(TNaming_NamedShape::GetID())) scope.Add(itchild.Value());
    }
    if (m_label.IsAttribute(TNaming_NamedShape::GetID())) scope.Add(m_label);
    TDF_MapIteratorOfLabelMap it(scope);
    for (;it.More();it.Next())
        TNaming::Displace(it.Key(), loc, Standard_True);//with oldshapes

}

void  FeatureBase::SetLabel(TDF_Label label)
{
    m_label = label;
}

TDF_Label FeatureBase::GetLabel()
{
    return m_label;
}

Standard_Integer FeatureBase::GetTag()
{
    return m_label.Tag();
}



