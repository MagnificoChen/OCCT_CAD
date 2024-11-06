//
// Created by 85147 on 10/2/2024.
//

#ifndef OCCT_CAD_FEATUREFILLET_H
#define OCCT_CAD_FEATUREFILLET_H


#include "FeatureAttach.h"

class FeatureFillet :public FeatureAttach{
public:
    explicit FeatureFillet(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Edge edge);

    FeatureFillet(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Edge edge, double r);

    ~FeatureFillet() override;

    void addFeature();

    void updateFeature();
private:
    TopoDS_Shape m_solid;
    TopoDS_Shape m_edge;


};

#endif //OCCT_CAD_FEATUREFILLET_H
