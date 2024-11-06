#include "FeatureCylinder.h"

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeCone.hxx>


FeatureCylinder::FeatureCylinder(QOccDocument* mDoc, double bottomRadius, double topRadius, double height)
        : FeatureIsolate(mDoc), BottomRadius(bottomRadius),
          TopRadius(topRadius), height(height) {
    if (BottomRadius == TopRadius) {
        m_hShape.Shape(BRepPrimAPI_MakeCylinder(BottomRadius, height));
    } else {
        m_hShape.Shape(BRepPrimAPI_MakeCone(BottomRadius, TopRadius, height));
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
