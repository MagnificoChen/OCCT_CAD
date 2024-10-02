//
// Created by 85147 on 9/28/2024.
//

#ifndef OCCT_CAD_QOCCSHELLSELECTOR_H
#define OCCT_CAD_QOCCSHELLSELECTOR_H


#include "QOccGeoSelector.h"
#include "TopoDS_Shape.hxx"
#include "TopoDS.hxx"

class QOccShellSelector : public QOccGeoSelector{
public:

    QOccShellSelector(CentralViewWidget* widget);

    ~QOccShellSelector();


public:
    //添加选中的shape
    bool addSelectedShape(const TopoDS_Shape &Shape) override;

    //获取当前第一个Shape
    TopoDS_Shape getSelectedShape();

    //获取所有的Shape
    std::vector<TopoDS_Shape> getSelectedShapes();

    //检查元素是否合法
    bool isDataValid();

    //删除已选中的元素
    bool deleteSelectedShape(const TopoDS_Shape &shape) override;

    //实现选择后，改变按钮状态
    void OnGeoSelected();

    //清除所有选中
    void clearSelectedShape();

    void OnSelectButtonToggled() override;

    void resetTitle() override;

private:

    std::vector<TopoDS_Shape> m_selectedShapes;

};


#endif //OCCT_CAD_QOCCSHELLSELECTOR_H
