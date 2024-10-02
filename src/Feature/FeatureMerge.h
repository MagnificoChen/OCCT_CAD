//
// Created by 85147 on 9/28/2024.
//

#ifndef OCCT_CAD_FEATUREMERGE_H
#define OCCT_CAD_FEATUREMERGE_H

#include "FeatureBase.h"

class FeatureMerge :public FeatureBase{
public:
    explicit FeatureMerge(QOccDocument* mDoc);

    ~FeatureMerge() override;

    void addFeature() override;

    virtual void createRenderPipeline();

    void UpdatePipeline();

private:

};


#endif //OCCT_CAD_FEATUREMERGE_H
