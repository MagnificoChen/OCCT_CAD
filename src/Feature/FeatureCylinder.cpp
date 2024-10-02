#include "FeatureCylinder.h"

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>


FeatureCylinder::FeatureCylinder(QOccDocument* mDoc, double bottomRadius, double topRadius, double height)
        : FeatureIsolate(mDoc), BottomRadius(bottomRadius),
          TopRadius(topRadius), height(height) {
    if (BottomRadius == TopRadius) {
        m_shape = BRepPrimAPI_MakeCylinder(BottomRadius, height).Shape();
    } else {
        m_shape = BRepPrimAPI_MakeCone(BottomRadius, TopRadius, height);
    }

    addFeature();
}

FeatureCylinder::~FeatureCylinder() {
}


bool FeatureCylinder::isCone() {
    return BottomRadius == TopRadius;
}

void FeatureCylinder::addFeature() {
    FeatureIsolate::addFeature();
}
