#pragma once
#include "FeatureIsolate.h"

class FeatureCylinder : public FeatureIsolate
{
public:

    FeatureCylinder(QOccDocument* mDoc, double bottomRadius, double topRadius, double height);

    ~FeatureCylinder();
    bool isCone();

    void addFeature() override;

private:
    double BottomRadius;
    double TopRadius;
    double height;

    gp_Ax2 axisAndLoc;
};