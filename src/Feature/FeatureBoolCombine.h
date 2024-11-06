//
// Created by 85147 on 10/4/2024.
//

#ifndef OCCT_CAD_FEATUREBOOLCOMBINE_H
#define OCCT_CAD_FEATUREBOOLCOMBINE_H

#include "FeatureMerge.h"
class FeatureBoolCombine :public FeatureMerge{
public:
explicit FeatureBoolCombine(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Shape shape2);
    ~FeatureBoolCombine() override;
    void addFeature();

    void updateFeature();

private:
    TopoDS_Shape m_shape1;
    TopoDS_Shape m_shape2;


};


#endif //OCCT_CAD_FEATUREBOOLCOMBINE_H
