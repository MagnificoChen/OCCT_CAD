#include "FeatureCube.h"

#include <BRepPrimAPI_MakeBox.hxx>

FeatureCube::FeatureCube() : FeatureBase(), x(1), y(1), z(1)
{
    m_shape = BRepPrimAPI_MakeBox(x,y,z).Shape();
}

FeatureCube::~FeatureCube()
{
}
