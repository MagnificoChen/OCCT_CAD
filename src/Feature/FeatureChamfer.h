//
// Created by 85147 on 9/25/2024.
//

#ifndef OCCT_CAD_FEATURECHAMFER_H
#define OCCT_CAD_FEATURECHAMFER_H
#include "FeatureAttach.h"

class FeatureChamfer :public FeatureAttach{
public:
    explicit FeatureChamfer(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Edge edge);

    FeatureChamfer(QOccDocument* mDoc, TopoDS_Shape shape, TopoDS_Edge edge, double r);

    ~FeatureChamfer() override;

    void addFeature();

    void updateFeature();
private:
    TopoDS_Shape m_solid;
    TopoDS_Shape m_edge;


};


#endif //OCCT_CAD_FEATURECHAMFER_H
