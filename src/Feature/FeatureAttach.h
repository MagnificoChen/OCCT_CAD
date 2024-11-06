//
// Created by 85147 on 9/28/2024.
//

#ifndef OCCT_CAD_FEATUREATTACH_H
#define OCCT_CAD_FEATUREATTACH_H
#include "FeatureBase.h"


/// Feature Attach: 依附特征。此特征依附于其他体。
/// 此特征：
/// - 有独立的TDF_Label
/// - 有独立的shape，仅用于更新，不参与渲染，没有Pipeline
/// - 有依附的特征列表 m_attachList
/// - 在特征建立后会对AttachList中的Label进行Modify操作（更新）
class FeatureAttach :public FeatureBase{
public:
    explicit FeatureAttach(QOccDocument* mDoc);
    ~FeatureAttach() override;

    void addFeature() override;


    /// 添加需要依附的特征
    /// ! 必须在初始化后调用
    /// \param tag 特征的tag，由Selector获取
    void AddToAttachList(const Standard_Integer tag);

    /// 更新依附的特征
    virtual void updateFeature() = 0;
protected:
    std::vector<TDF_Label> m_attachList;
};


#endif //OCCT_CAD_FEATUREATTACH_H
