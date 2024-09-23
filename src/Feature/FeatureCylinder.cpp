#include "FeatureCylinder.h"

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>

FeatureCylinder::FeatureCylinder() : FeatureBase(), BottomRadius(1),TopRadius(1), height(1)
{
    if(BottomRadius == TopRadius)
    {
        m_shape = BRepPrimAPI_MakeCylinder(BottomRadius, height).Shape();
    }else
    {
        m_shape = BRepPrimAPI_MakeCone(BottomRadius, TopRadius, height);
    }

}

FeatureCylinder::~FeatureCylinder()
{
}


bool FeatureCylinder::isCone()
{
    return BottomRadius == TopRadius;
}
