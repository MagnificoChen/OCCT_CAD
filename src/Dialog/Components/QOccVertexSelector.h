//
// Created by 85147 on 9/27/2024.
//

#ifndef OCCT_CAD_QOCCVERTEXSELECTOR_H
#define OCCT_CAD_QOCCVERTEXSELECTOR_H
#include "QOccGeoSelector.h"
#include "TopoDS_Shape.hxx"
#include "TopoDS.hxx"

class QOccVertexSelector :public QOccGeoSelector{
public:

    QOccVertexSelector(CentralViewWidget* widget);

    ~QOccVertexSelector();


public:
    //添加选中的shape
    bool addSelectedShape(const TopoDS_Shape &vertexShape) override;

    //获取当前第一个Vertex
    const TopoDS_Vertex &getSelectedVertex();

    //获取所有的Vertex,以Shape的方式返回
    std::vector<TopoDS_Shape> getSelectedVertices();

    //检查元素是否合法
    bool isDataValid();

    //删除已选中的元素
    bool deleteSelectedShape(const TopoDS_Shape &shape);

    //实现选择后，改变按钮状态
    void OnGeoSelected();

    //清除所有选中
    void clearSelectedShape();

    void resetTitle() override;

    void OnSelectButtonToggled() override;

    TopoDS_Shape getSelectedShape() override;

private:

    std::vector<TopoDS_Shape> m_selectedVertices;


};


#endif //OCCT_CAD_QOCCVERTEXSELECTOR_H
