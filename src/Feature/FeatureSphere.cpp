#include "FeatureSphere.h"

#include <BRepPrimAPI_MakeSphere.hxx>



FeatureSphere::FeatureSphere(QOccDocument* mDoc, double radius) : FeatureIsolate(mDoc) {
    m_hShape.Shape(BRepPrimAPI_MakeSphere(radius));

    // 创建一个平移变换
    gp_Trsf transformation;
    transformation.SetTranslation(gp_Vec{ 0,5,0 });

    // 应用变换
    BRepBuilderAPI_Transform transform(m_hShape.Shape(), transformation, false, true);

    m_shape = transform.Shape();
    
    addFeature();
}

FeatureSphere::~FeatureSphere() {

}

void FeatureSphere::addFeature() {
    FeatureIsolate::addFeature();
}
