#pragma once

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidgetItem>
#include <QSpacerItem>
#include <qevent.h>
#include <QDialogButtonBox>
#include "src/CentralViewWidget.h"

// LineEdit



// 布局为竖向排列的对话框基类
// abstract class
class DialogBase  : public QDialog
{
    Q_OBJECT
//enum
public:
    enum ButtonType { NoButton,Ok,OkCancel,All };
public:
    DialogBase(QWidget *parent, ButtonType type = OkCancel);

    DialogBase();

    virtual ~DialogBase() override;
    /**
     * 
     * @param type 需要使用哪些按钮： 无按钮/OK/OK+Cancel/OK+Apply+Cancel；
     */
    void initializeButtons(ButtonType type);
    QVBoxLayout* GetMainLayout() const;


    bool eventFilter(QObject* obj, QEvent* event) override;

    virtual void OnOK() = 0;
    virtual void OnApply() = 0;
    virtual void OnCancel() = 0;

    CentralViewWidget* getOwnerWidget(){
        return ownerWidget;
    }

public slots:
    //如果对话框的具体实现没有选择器，则不做如何操作
    virtual void DisableAllGeoSelector()=0;
private:
    QVBoxLayout* m_mainLayout = nullptr;
    QHBoxLayout* m_buttonsLayout = nullptr;
    QDialogButtonBox* buttonBox = nullptr;


    CentralViewWidget* ownerWidget = nullptr;
};
