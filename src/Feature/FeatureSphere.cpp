#include "FeatureSphere.h"

#include <BRepPrimAPI_MakeSphere.hxx>

FeatureSphere::FeatureSphere(double radius)
{
    m_shape =  BRepPrimAPI_MakeSphere(radius).Shape();

    // 创建一个平移变换
    gp_Trsf transformation;
    transformation.SetTranslation(gp_Vec{ 0,5,0 });

    // 应用变换
    BRepBuilderAPI_Transform transform(m_shape, transformation, false, true);

    m_shape = transform.Shape();


}
