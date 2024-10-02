#pragma once
#include "FeatureIsolate.h"
#include <BRepPrimAPI_MakeBox.hxx>
class FeatureCube : public FeatureIsolate
{
public:

    FeatureCube(QOccDocument* mDoc, double x, double y, double z);

    ~FeatureCube();

    void addFeature() override;

private:
    BRepPrimAPI_MakeBox box;

    double x ;
    double y ;
    double z ;
};
