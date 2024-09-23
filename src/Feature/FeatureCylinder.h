#pragma once
#include "FeatureBase.h"

class FeatureCylinder : public FeatureBase
{
public:
    FeatureCylinder();
    ~FeatureCylinder();
    bool isCone();
private:
    double BottomRadius;
    double TopRadius;
    double height;
    gp_Ax2 axisAndLoc;
};