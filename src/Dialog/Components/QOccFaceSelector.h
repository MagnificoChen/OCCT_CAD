//
// Created by 85147 on 9/27/2024.
//

#ifndef OCCT_CAD_QOCCFACESELECTOR_H
#define OCCT_CAD_QOCCFACESELECTOR_H




#include "QOccGeoSelector.h"
#include "TopoDS_Shape.hxx"
#include "TopoDS.hxx"

class QOccFaceSelector :public QOccGeoSelector{
public:

    QOccFaceSelector(CentralViewWidget* widget);

    ~QOccFaceSelector();


public:
    //添加选中的shape
    bool addSelectedShape(const TopoDS_Shape &faceShape);

    //获取当前第一个Face
    const TopoDS_Face &getSelectedFace();

    //获取所有的Vertex,以Shape的方式返回
    std::vector<TopoDS_Shape> getSelectedFaces();

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

    TopoDS_Shape getSelectedShape() override;

private:

    std::vector<TopoDS_Shape> m_selectedFaces;

};


#endif //OCCT_CAD_QOCCFACESELECTOR_H
