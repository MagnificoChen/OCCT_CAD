#pragma once

#include <IVtk_Types.hxx>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <TopoDS_Shape.hxx>
#include <unordered_set>


class CentralViewWidget;

class QOccGeoSelector : public QWidget {
Q_OBJECT

public:
    QOccGeoSelector(CentralViewWidget* widget);

    ~QOccGeoSelector();


public:

    //查询是否启用选择
    bool isEnabled();

    //启用/禁用选择
    void EnableItem(bool isEnable);

public:
    //设置第一个按钮的文本
    void setLabelText(QString text);

    //设置大小
    void setCapacity(int n);



    //清除选中
    virtual void clearSelectedShape() = 0;

    virtual bool addSelectedShape(const TopoDS_Shape &Shape) = 0;

    virtual bool deleteSelectedShape(const TopoDS_Shape &Shape) = 0;

    virtual void resetTitle() = 0;

    virtual TopoDS_Shape getSelectedShape() = 0;

    void SetTag(Standard_Integer tag){m_tag = tag;}
    Standard_Integer GetTag(){return m_tag;}

public slots:
    //弹起按钮，恢复未选中状态
    [[maybe_unused]] void Disable();
    virtual void OnGeoSelected() = 0;
    virtual void OnSelectButtonToggled();

signals:
    void SelectModeChanged(IVtk_SelectionMode mode);
    void OnDisableOtherSelectors();

protected:
    Standard_Integer m_tag = -1;

    QHBoxLayout* m_layout;
    //存储这个存储器选定的Shapes
    QToolButton* m_toolbutton_delete;
    QToolButton* m_toolbutton_sel;
    QToolButton* m_toolbutton_selMode;
    CentralViewWidget* ownerWidget = nullptr;
    //capacity，1 means single selector.
    int m_capacity = 1;
};
