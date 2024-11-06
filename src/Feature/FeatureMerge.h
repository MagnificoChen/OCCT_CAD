//
// Created by 85147 on 9/28/2024.
//

#ifndef OCCT_CAD_FEATUREMERGE_H
#define OCCT_CAD_FEATUREMERGE_H

#include "FeatureBase.h"

class FeatureMerge :public FeatureBase {
public:
    explicit FeatureMerge(QOccDocument* mDoc);

    ~FeatureMerge() override;

    void addFeature() override;

    virtual void createRenderPipeline();

    void UpdatePipeline();

    void AddToDeleteList(const Standard_Integer tag);

    void AddToModifyList(const Standard_Integer tag);

    std::vector<TDF_Label>& getCreatedFeatureList(){
        return m_createList;
    };

protected:
    std::vector<TDF_Label> m_deleteList;
    std::vector<TDF_Label> m_modifyList;
    std::vector<TDF_Label> m_createList;

private:
};


#endif //OCCT_CAD_FEATUREMERGE_H
