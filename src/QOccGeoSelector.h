#pragma once

#include <IVtk_Types.hxx>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>
#include <TopoDS_Shape.hxx>
#include <unordered_set>

class CentralViewWidget;

class QOccGeoSelector : public QWidget
{
    Q_OBJECT

public:
    QOccGeoSelector(IVtk_SelectionMode mode, QWidget* parent = nullptr);
    ~QOccGeoSelector();

signals:
    //修改选择器时候发出:只有按钮被激活，才可以修改选择器。
    void SelectModeChanged(IVtk_SelectionMode mode);
    //选择后发出
    void Selected();
    void DeSelected();

public:
    void setLabelText(QString text);
    void setSelectModeChangeable(bool isChangeable);
    void setCapacity(int n);
    //弹起按钮，取消按钮功能
    void Disable();

    bool addSelectedShape(const TopoDS_Shape& shape);
    bool deleteSelectedShape(const TopoDS_Shape& shape);
    void clearSelectedShape();

public slots:
    //处理并发出信号
    void OnChangeSelectMode();
    void OnGeoSelected();
    void OnSelectButtonToggled();
    void OnDeleteButtonToggled();
private:

    IVtk_SelectionMode currSelMode = SM_None;
    QHBoxLayout* m_layout;
    QToolButton* m_toolbutton_sel;
    QToolButton* m_toolbutton_delete;
    QToolButton* m_toolbutton_selMode;

    //capacity，1 means single selector.
    int m_capacity = 1;


    //存储这个存储器选定的Shapes
    std::vector<std::reference_wrapper<const TopoDS_Shape>> m_selectedShapes;

    CentralViewWidget* ownerWidget = nullptr;

    //
    bool _isSelectModeChangeable = false;
};
