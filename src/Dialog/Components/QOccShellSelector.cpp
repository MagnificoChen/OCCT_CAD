//
// Created by 85147 on 9/28/2024.
//

#include "QOccShellSelector.h"
#include <TopoDS_Face.hxx>
#include "TopoDS.hxx"
#include "TopoDS_Shape.hxx"
#include "QDebug"
#include "QToolButton"

QOccShellSelector::QOccShellSelector(CentralViewWidget* widget)
        : QOccGeoSelector(widget){

}

QOccShellSelector::~QOccShellSelector() {

}

bool QOccShellSelector::addSelectedShape(const TopoDS_Shape &shape) {

    auto copyShape = shape;

    if (shape.ShapeType() != TopAbs_SOLID) {
        qDebug()<<"WARNING: trying to delete a non-Shape shape via ShapeSelector.";
        return false;
    }
    if (m_capacity <= m_selectedShapes.size()) return false;
    auto it = std::find_if(m_selectedShapes.begin(), m_selectedShapes.end(),
                           [&shape](const TopoDS_Shape& ref) {
                               return ref == shape;
                           });
    if (it != m_selectedShapes.end()) {
        return false;
    }
    m_selectedShapes.push_back(copyShape);
    OnGeoSelected();
    return true;
}


bool QOccShellSelector::deleteSelectedShape(const TopoDS_Shape &shape) {
    // 查找 shape 是否存在于 m_selectedShapes 中
    auto it = std::find_if(m_selectedShapes.begin(), m_selectedShapes.end(),
                           [&shape](const TopoDS_Shape& ref) {
                               return ref == shape;
                           });
    // 如果找到了 shape
    if (it != m_selectedShapes.end()) {
        // 从向量中删除 shape
        m_selectedShapes.erase(it);
        OnGeoSelected();
        return true; // 表示成功删除
    }

    resetTitle();
    return true;
}

std::vector<TopoDS_Shape> QOccShellSelector::getSelectedShapes() {
    return m_selectedShapes;
}

TopoDS_Shape QOccShellSelector::getSelectedShape() {
    if (isDataValid()) {
        return m_selectedShapes[0];
    }
}


bool QOccShellSelector::isDataValid() {
    if(m_selectedShapes.empty()) return false;
    for(auto item:m_selectedShapes){
        if(item.ShapeType() != TopAbs_SOLID) return false;
    }
    return true;
}


void QOccShellSelector::OnGeoSelected() {
    if (!m_toolbutton_sel->isChecked()) return;
    if (m_selectedShapes.empty()) {
        m_toolbutton_sel->setText("未选中任何体");
    } else {
        auto str = QString("已选中 %1 个体").arg(m_selectedShapes.size());
        qDebug() << str;
        m_toolbutton_sel->setText(str);
    }
}


void QOccShellSelector::clearSelectedShape() {
    m_selectedShapes.clear();
    //TODO: 发送信号？
}

void QOccShellSelector::OnSelectButtonToggled() {
    QOccGeoSelector::OnSelectButtonToggled();
    if(m_toolbutton_sel->isChecked()){
            SelectModeChanged(SM_Solid);
        }else{
            SelectModeChanged(SM_None);
        }

}

void QOccShellSelector::resetTitle() {
    m_toolbutton_sel->setText("选择体");
}


