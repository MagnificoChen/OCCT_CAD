#pragma once
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QToolButton>
#include <qwidget.h>

#include "src/CentralViewWidget.h"

class GridItemBase :
    public QWidget
{
    Q_OBJECT

public:
    GridItemBase(QString mainButtonText = QString("GridItemBase"));
    virtual ~GridItemBase();

public:
    QHBoxLayout* m_layout;
    QToolButton* m_mainButton;
    QToolButton* m_toolButton1;
    QToolButton* m_toolButton2;
    QSignalMapper* mapper1;
    QSignalMapper* mapper2;

    std::function<void(int)> button1ItemFunction;
    std::function<void(int)> button2ItemFunction;

    QDialog* m_pParentDlg = nullptr;

public:
    //APIs: Used for customize button functions

    /**
     * Uses first item in list to initialize a toolButton with menu.
     * Does not load icon if not match.
     *
     * @param list2 list of Options
     * @param iconList list of Option
     */
    void EnableSecondOption(QStringList list2, QList<QIcon> iconList);


    void BindButton1Function(std::function<void(int)> func);
    void BindButton2Function(std::function<void(int)> func);
    // void BindFocusFunction(std::function<void(int)> func);
    // void BindUnFocusFunction(std::function<void(int)> func);

    virtual void OnFocus();
    virtual void OnUnFocus();

public:
    virtual BOOL Create(QDialog* parent, QStringList list1, QList<QIcon> iconList1);


    //inline functions
public:
    inline QDialog* getParentDlg()
    {
        return m_pParentDlg;
    }
public slots:
    void OnToolButton1Clicked(int index);
    void OnToolButton2Clicked(int index);

    void OnMainButtonToggled();

signals:
    // virtual void OnFocus() = 0;
};
