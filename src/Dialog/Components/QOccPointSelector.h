////
//// Created by 85147 on 9/26/2024.
////
//
//#ifndef OCCT_CAD_QOCCPOINTSELECTOR_H
//#define OCCT_CAD_QOCCPOINTSELECTOR_H
//
//
//#include "QOccGeoSelector.h"
//
//enum SELECTMODEPOINT {
//    SMP_VERTEX,
//    SMP_EDGE_MIDPOINT,
//    SMP_EDGE_FREEPOINT,
//    SMP_FACE_FREEPOINT,
//};
//
//class QOccPointSelector : public QOccGeoSelector {
//
//public:
//    QOccPointSelector(IVtk_SelectionMode mode, QWidget* parent = nullptr);
//
//    //修改选择器时候发出:只有按钮被激活，才可以修改选择器。
//    void SelectModeChanged(IVtk_SelectionMode mode);
//
//    //选择后发出
//    void Selected();
//
//    void DeSelected();
//
//    //处理并发出信号
//    void OnChangeSelectMode();
//
//    void OnSelectButtonToggled();
//
//    void OnDeleteButtonToggled();
//
//    ~QOccPointSelector() override;
//
//    void clearSelectedShape() override;
//
//    void resetTitle() override;
//
//    void OnGeoSelected() override;
//
//public:
//    SELECTMODEPOINT m_currSelMode;
//
////     m_selected;
//};
//
//
//#endif //OCCT_CAD_QOCCPOINTSELECTOR_H
