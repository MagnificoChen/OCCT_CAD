#pragma once
#include "FeatureIsolate.h"

class FeatureSphere : public FeatureIsolate
{
public:

    FeatureSphere(QOccDocument* mDoc, double radius = 5);

    ~FeatureSphere() override;

    void addFeature() override;

private:
    double m_radius = 5;
};

