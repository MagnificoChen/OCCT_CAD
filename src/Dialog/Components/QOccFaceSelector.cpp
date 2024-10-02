//
// Created by 85147 on 9/27/2024.
//

#include "QOccFaceSelector.h"

#include <TopoDS_Face.hxx>
#include "TopoDS.hxx"
#include "TopoDS_Shape.hxx"
#include "QDebug"
#include "QToolButton"

QOccFaceSelector::QOccFaceSelector(CentralViewWidget* widget)
        : QOccGeoSelector(widget) {

}

QOccFaceSelector::~QOccFaceSelector() {

}

bool QOccFaceSelector::addSelectedShape(const TopoDS_Shape &shape) {
    auto copyShape = shape;
    if (shape.ShapeType() != TopAbs_FACE) {
        qDebug() << "WARNING: trying to delete a non-Face shape via FaceSelector.";
        return false;
    }
    if (m_capacity <= m_selectedFaces.size()) return false;
    auto it = std::find_if(m_selectedFaces.begin(), m_selectedFaces.end(),
                           [&shape](const TopoDS_Shape &ref) {
                               return ref == shape;
                           });
    if (it != m_selectedFaces.end()) {
        return false;
    }
    m_selectedFaces.push_back(copyShape);
    OnGeoSelected();
    return true;
}


bool QOccFaceSelector::deleteSelectedShape(const TopoDS_Shape &shape) {
    // 查找 shape 是否存在于 m_selectedShapes 中
    auto it = std::find_if(m_selectedFaces.begin(), m_selectedFaces.end(),
                           [&shape](const TopoDS_Shape &ref) {
                               return ref == shape;
                           });
    // 如果找到了 shape
    if (it != m_selectedFaces.end()) {
        // 从向量中删除 shape
        m_selectedFaces.erase(it);
        OnGeoSelected();
        return true; // 表示成功删除
    }

    resetTitle();
    return true;
}

std::vector<TopoDS_Shape> QOccFaceSelector::getSelectedFaces() {
    return m_selectedFaces;
}

const TopoDS_Face &QOccFaceSelector::getSelectedFace() {
    if (m_selectedFaces.empty()) {
        qDebug() << "[ERROR]: Getting shape from empty list.";
    }
    return TopoDS::Face(m_selectedFaces[0]);
}


bool QOccFaceSelector::isDataValid() {
    if (m_selectedFaces.empty()) return false;
    for (auto item: m_selectedFaces) {
        if (item.ShapeType() != TopAbs_FACE) return false;
    }
    return true;
}


void QOccFaceSelector::OnGeoSelected() {
    if (!m_toolbutton_sel->isChecked()) return;
    if (m_selectedFaces.empty()) {
        m_toolbutton_sel->setText("未选中任何面");
    } else {
        auto str = QString("已选中 %1 个面").arg(m_selectedFaces.size());
        qDebug() << str;
        m_toolbutton_sel->setText(str);
    }
}


void QOccFaceSelector::clearSelectedShape() {
    m_selectedFaces.clear();
    //TODO: 发送信号？
}


void QOccFaceSelector::resetTitle() {
    m_toolbutton_sel->setText("选择面");

}

void QOccFaceSelector::OnSelectButtonToggled() {
    QOccGeoSelector::OnSelectButtonToggled();
    if (m_toolbutton_sel->isChecked()) {
        SelectModeChanged(SM_Face);
    } else {
        SelectModeChanged(SM_None);
    }
}

TopoDS_Shape QOccFaceSelector::getSelectedShape() {
    if (isDataValid()) {
        return m_selectedFaces[0];
    }
}
