//
// Created by 85147 on 9/27/2024.
//
#include "QOccEdgeSelector.h"
#include <TopoDS_Edge.hxx>
#include "TopoDS.hxx"
#include "TopoDS_Shape.hxx"
#include "QDebug"
#include "QToolButton"

QOccEdgeSelector::QOccEdgeSelector(CentralViewWidget* widget)
        : QOccGeoSelector(widget) {

}

QOccEdgeSelector::~QOccEdgeSelector() {

}

bool QOccEdgeSelector::addSelectedShape(const TopoDS_Shape &shape) {

    auto copyShape = shape;
    if (shape.ShapeType() != TopAbs_EDGE) {
        qDebug() << "WARNING: trying to delete a non-Edge shape via EdgeSelector.";
        return false;
    }
    if (m_capacity <= m_selectedEdges.size()) return false;
    auto it = std::find_if(m_selectedEdges.begin(), m_selectedEdges.end(),
                           [&shape](const TopoDS_Shape& ref) {
                               return ref == shape;
                           });
    if (it != m_selectedEdges.end()) {
        return false;
    }
    m_selectedEdges.emplace_back(copyShape);
    OnGeoSelected();
    return true;
}


bool QOccEdgeSelector::deleteSelectedShape(const TopoDS_Shape &shape) {
    // 查找 shape 是否存在于 m_selectedShapes 中
    auto it = std::find_if(m_selectedEdges.begin(), m_selectedEdges.end(),
                           [&shape](const TopoDS_Shape& ref) {
                               return ref == shape;
                           });
    // 如果找到了 shape
    if (it != m_selectedEdges.end()) {
        // 从向量中删除 shape
        m_selectedEdges.erase(it);
        OnGeoSelected();
        return true; // 表示成功删除
    }

    resetTitle();
    return true;
}

std::vector<TopoDS_Shape> QOccEdgeSelector::getSelectedEdges() {
    return m_selectedEdges;
}

const TopoDS_Edge &QOccEdgeSelector::getSelectedEdge() {
    if (m_selectedEdges.empty()) {
        qDebug() << "[ERROR]: Getting shape from empty list.";
    }
    return TopoDS::Edge(m_selectedEdges[0]);
}


bool QOccEdgeSelector::isDataValid() {
    if (m_selectedEdges.empty()) return false;
    for (auto item : m_selectedEdges) {
        if (item.ShapeType() != TopAbs_EDGE) return false;
    }
    return true;
}


void QOccEdgeSelector::OnGeoSelected() {
    if (!m_toolbutton_sel->isChecked()) return;
    if (m_selectedEdges.empty()) {
        m_toolbutton_sel->setText("未选中任何边");
    } else {
        auto str = QString("已选中 %1 条边").arg(m_selectedEdges.size());
        qDebug() << str;
        m_toolbutton_sel->setText(str);
    }

}


void QOccEdgeSelector::clearSelectedShape() {
    m_selectedEdges.clear();
    //TODO: 发送信号？
}

void QOccEdgeSelector::resetTitle() {
    m_toolbutton_sel->setText("选择边");
}

void QOccEdgeSelector::OnSelectButtonToggled() {
    QOccGeoSelector::OnSelectButtonToggled();
    if (m_toolbutton_sel->isChecked()) {
        SelectModeChanged(SM_Edge);
    } else {
        SelectModeChanged(SM_None);
    }
}

TopoDS_Shape QOccEdgeSelector::getSelectedShape() {
    if(isDataValid()){
        return m_selectedEdges[0];
    }
}





