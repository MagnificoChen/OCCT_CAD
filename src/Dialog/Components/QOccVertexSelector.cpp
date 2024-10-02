//
// Created by 85147 on 9/27/2024.
//

#include <TopoDS_Vertex.hxx>
#include "QOccVertexSelector.h"
#include "TopoDS.hxx"
#include "TopoDS_Shape.hxx"
#include "QDebug"
#include "QToolButton"

QOccVertexSelector::QOccVertexSelector(CentralViewWidget* widget)
        : QOccGeoSelector(widget){

}

QOccVertexSelector::~QOccVertexSelector() {

}

bool QOccVertexSelector::addSelectedShape(const TopoDS_Shape &shape) {
    auto copyShape = shape;

    if (shape.ShapeType() != TopAbs_VERTEX) {
        qDebug()<<"WARNING: trying to delete a non-Vertex shape via VertexSelector.";
        return false;
    }
    if (m_capacity <= m_selectedVertices.size()) return false;
    auto it = std::find_if(m_selectedVertices.begin(), m_selectedVertices.end(),
                           [&shape](const TopoDS_Shape& ref) {
                               return ref == shape;
                           });
    if (it != m_selectedVertices.end()) {
        return false;
    }
    m_selectedVertices.push_back(copyShape);
    OnGeoSelected();
    return true;
}


bool QOccVertexSelector::deleteSelectedShape(const TopoDS_Shape &shape) {
    // 查找 shape 是否存在于 m_selectedShapes 中
    auto it = std::find_if(m_selectedVertices.begin(), m_selectedVertices.end(),
                           [&shape](const TopoDS_Shape& ref) {
                               return ref == shape;
                           });
    // 如果找到了 shape
    if (it != m_selectedVertices.end()) {
        // 从向量中删除 shape
        m_selectedVertices.erase(it);
        OnGeoSelected();
        return true; // 表示成功删除
    }

    resetTitle();
    return true;
}

std::vector<TopoDS_Shape> QOccVertexSelector::getSelectedVertices() {
    return m_selectedVertices;
}

const TopoDS_Vertex &QOccVertexSelector::getSelectedVertex() {
    if (m_selectedVertices.empty()) {
        qDebug() << "[ERROR]: Getting shape from empty list.";
    }
    return TopoDS::Vertex(m_selectedVertices[0]);
}


bool QOccVertexSelector::isDataValid() {
    if(m_selectedVertices.empty()) return false;
    for(auto item:m_selectedVertices){
        if(item.ShapeType() != TopAbs_VERTEX) return false;
    }
    return true;
}


void QOccVertexSelector::OnGeoSelected() {
    if (!m_toolbutton_sel->isChecked()) return;
    if (m_selectedVertices.empty()) {
        m_toolbutton_sel->setText("未选中任何点");
    } else {
        auto str = QString("已选中 %1 个顶点").arg(m_selectedVertices.size());
        qDebug() << str;
        m_toolbutton_sel->setText(str);
    }
}


void QOccVertexSelector::clearSelectedShape() {
    m_selectedVertices.clear();
    //TODO: 发送信号？
}

void QOccVertexSelector::resetTitle() {
    m_toolbutton_sel->setText("选择顶点");

}

void QOccVertexSelector::OnSelectButtonToggled() {
    QOccGeoSelector::OnSelectButtonToggled();
    if(m_toolbutton_sel->isChecked()){
            SelectModeChanged(SM_Vertex);
        }else{
            SelectModeChanged(SM_None);
        }

}

TopoDS_Shape QOccVertexSelector::getSelectedShape() {
    if (isDataValid()) {
        return m_selectedVertices[0];
    }
}




