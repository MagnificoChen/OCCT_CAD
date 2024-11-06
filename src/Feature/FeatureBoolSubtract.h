//
// Created by 85147 on 10/4/2024.
//

#ifndef OCCT_CAD_FEATUREBOOLSUBTRACT_H
#define OCCT_CAD_FEATUREBOOLSUBTRACT_H

#include "FeatureMerge.h"

class FeatureBoolSubtract :public FeatureMerge{
public:
    explicit FeatureBoolSubtract(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Shape tool);

    ~FeatureBoolSubtract() override;

    void addFeature() override;

    void updateFeature();

private:
    TopoDS_Shape m_shape;
    TopoDS_Shape m_tool;


};


#endif //OCCT_CAD_FEATUREBOOLSUBTRACT_H
