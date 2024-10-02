//
// Created by 85147 on 9/28/2024.
//

#ifndef OCCT_CAD_FEATUREISOLATE_H
#define OCCT_CAD_FEATUREISOLATE_H

#include "FeatureBase.h"

class FeatureIsolate : public FeatureBase {
public:
    explicit FeatureIsolate(QOccDocument* mDoc);
    ~FeatureIsolate() override;

    void addFeature() override;

    //渲染实体
    virtual void createRenderPipeline();

    void UpdatePipeline() ;

protected:

};


#endif //OCCT_CAD_FEATUREISOLATE_H
