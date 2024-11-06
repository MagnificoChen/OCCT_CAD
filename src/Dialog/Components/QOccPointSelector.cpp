////
//// Created by 85147 on 9/26/2024.
////
//
//#include "QOccPointSelector.h"
//#include "QAction"
//#include "QToolButton"
//#include "src/CentralViewWidget.h"
//
//QOccPointSelector::QOccPointSelector(IVtk_SelectionMode mode, QWidget* parent)
//    : QOccGeoSelector(parent)
//{
////    {
////        QAction *pAction = new QAction("顶点");
////        m_toolbutton_selMode->addAction(pAction);
//////        connect(pAction, &QAction::triggered, this, &QOccPointSelector::OnChangeSelectMode);
////
////        pAction = new QAction("边上中点");
////        m_toolbutton_selMode->addAction(pAction);
//////        connect(pAction, &QAction::triggered, this, &QOccPointSelector::OnChangeSelectMode);
////
////        pAction = new QAction("边上自由点");
////        m_toolbutton_selMode->addAction(pAction);
//////        connect(pAction, &QAction::triggered, this, &QOccPointSelector::OnChangeSelectMode);
////
////        pAction = new QAction("面上自由点");
////        m_toolbutton_selMode->addAction(pAction);
//////        connect(pAction, &QAction::triggered, this, &QOccPointSelector::OnChangeSelectMode);
////
////        pAction = new QAction("无");
////        m_toolbutton_selMode->addAction(pAction);
//////        connect(pAction, &QAction::triggered, this, &QOccPointSelector::OnChangeSelectMode);
////    }
//}
//
////点的多种选择方式
//void QOccPointSelector::OnChangeSelectMode()
//{
//    QAction* action = qobject_cast<QAction*>(sender());
//    if (!m_toolbutton_sel->isChecked()) return;
//    if (action->text() == "顶点")
//    {
//        SelectModeChanged(SM_Vertex);
//        m_currSelMode = SMP_VERTEX;
//    }
//    if (action->text() == "边上中点")
//    {
//        SelectModeChanged(SM_Edge);
//        m_currSelMode = SMP_EDGE_MIDPOINT;
//    }
//    if (action->text() == "边上自由点")
//    {
//        SelectModeChanged(SM_Face);
//        m_currSelMode = SMP_EDGE_FREEPOINT;
//    }
//    if (action->text() == "面上自由点")
//    {
//        SelectModeChanged(SM_Shape);
//        m_currSelMode = SMP_FACE_FREEPOINT;
//    }
//    if (action->text() == "无")
//    {
//        SelectModeChanged(SM_None);
//        m_toolbutton_sel->setText("已禁用");
//    }
//}
//
//void QOccPointSelector::OnSelectButtonToggled()
//{
//    if (!m_toolbutton_sel->isChecked())
//    {
//        emit SelectModeChanged(SM_None);
//        m_toolbutton_sel->setText("已禁用");
//        ownerWidget->SetDefaultInteractor();
//
//    }
//    else
//    {
//        //通知InteractorStyle，记录选择内容和当前选择器
////        emit SelectModeChanged(m_currSelMode);
//        //通知对话框，禁用其他选择器
//        QMetaObject::invokeMethod(parent(), "DisableAllGeoSelector", Qt::DirectConnection);
//        switch (m_currSelMode)
//        {
//        case SM_Vertex:
//            {
//                m_toolbutton_sel->setText("选择点");
//                break;
//            }
//        case SM_Edge:
//            {
//                m_toolbutton_sel->setText("选择边");
//                break;
//            }
//        case SM_Face:
//            {
//                m_toolbutton_sel->setText("选择面");
//                break;
//            }
//        case SM_Shape:
//            {
//                m_toolbutton_sel->setText("选择体");
//                break;
//            }
//        default: break;
//        }
//    }
//}
//
//void QOccPointSelector::OnDeleteButtonToggled()
//{
//    //仅在激活时有效
//    if (!m_toolbutton_sel->isChecked()) return;
//
//    emit DeSelected();
//    m_selectedShapes.clear();
//}
//
//QOccPointSelector::~QOccPointSelector() {
//
//}
//
//void QOccPointSelector::clearSelectedShape() {
//
//}
//
//void QOccPointSelector::resetTitle() {
//    m_toolbutton_sel->setText("选择点");
//
//}
//
//void QOccPointSelector::OnGeoSelected() {
//
//}
