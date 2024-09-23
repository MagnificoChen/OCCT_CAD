#pragma once
#include "FeatureBase.h"

class FeatureCube : public FeatureBase
{
public:
    FeatureCube();
    ~FeatureCube();
private:
    double x ;
    double y ;
    double z ;
};
