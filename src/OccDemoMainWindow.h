#pragma once

#include "GlobalDefines.h"

#include <QtWidgets/QMainWindow>
#include "QStatusBar"
#include "CentralViewWidget.h"
#include "SARibbonCategory.h"
#include "SARibbonBar.h"
#include "SARibbonMenu.h"
#include "SARibbonQuickAccessBar.h"
#include <StlAPI_Writer.hxx>
#include <qmdiarea.h>
#include <QDockWidget>
#include <QDebug>
#include <QFileDialog>
#include "QDialogManager.h"
#include "src/Dialog/DialogFeatureCube.h"
#include "QOccDocument.h"
#include "src/ModelTree/LeftTreeViewWidget.h"
#include <QMdiSubWindow>
#include <SARibbonMainWindow.h>

//这个类控制MainWindow的初始化和显示，同时控制view和document以及对应的消息路由。
class OccDemoMainWindow : public SARibbonMainWindow
{
    Q_OBJECT
        // 普通方法
public:

    OccDemoMainWindow(QWidget* parent = nullptr);
    ~OccDemoMainWindow();
    void _initializeRibbonBarButtons();
    void OnOpenSphereDialog();
    void OnOpenCubeDialog();
    void OnOpenCylinderDialog();

    QMdiArea* getMdiArea() const;

    bool OnNewMDIWindow();

    void ConnectSignalAndSlots();

    bool OnSaveDocument();
    bool OnLoadDocument();
    bool OnLoadSTL();
    bool OnLoadSTEP();


    QString _OpenFileDialog(FileFormat f);
    //must be called after mdi_area has initialized.
    void _initializeTreeDockWindow();

public slots:
    // 手动切换subWindow之后，需要通知Document切换currDocument
    void OnChangeSubWindow(QMdiSubWindow* subWin);
    CentralViewWidget* GetActiveViewWidget();
    //根据Document中的内容更新View。
    void UpdateView();
    void UpdateTreeView();

// 获取DocumentView数据
public:
    bool AddViewDocItem(std::pair<CentralViewWidget*, QOccDocument*> item);
    CentralViewWidget* getCentralWidgetByDocument(QOccDocument* doc);
    QOccDocument* getDocumentByCentralWidget(CentralViewWidget* view);

signals:
    //To QDocumentManager:
    //此信号用于New/Load Document时发出
    void signalAddNewDocument(bool isLoad, const QString& path);
    void signalSaveDocument(const QString& path);


    //导入几何体，如stl文件等。导入到当前Document
    void signalLoadGeometry(const QString& path, FileFormat format);
    //这意味着切换了标签页，需要改变CurrentDocument。
    //tag:Document的tag
    void signalChangeCurrDocument(QOccDocument* doc);

    //To QCentralViewManager

    //静态方法
public:
    static OccDemoMainWindow* getInstance();
protected:

private:
    static OccDemoMainWindow* instance;
private:

    SARibbonBar* m_ribbonBar = nullptr;

    SARibbonCategory* m_categoryMain = nullptr;
    QStatusBar* m_statusBar = nullptr;

    CentralViewWidget* m_centralWidget = nullptr;
    QMdiArea* m_mdiArea = nullptr;

    QDockWidget* m_treeDock = nullptr;

    QDialogManager* m_dialogManager = nullptr;


    //SARibbonPanels
    SARibbonPannel* panel_files;
    SARibbonPannel* panel_feature2D;
    SARibbonPannel* panel_feature3D;
    SARibbonPannel* panel_basic;


    //需要存储subwindow Tag和View的一对一关系
    std::map< int,CentralViewWidget* > m_tabViewMap;
    //View和Doc的关系
    std::unordered_map<QOccDocument*, CentralViewWidget*> _docViewMap;
    std::unordered_map<CentralViewWidget*, QOccDocument*> _viewDocMap;

    QMdiSubWindow* m_lastActiveSubWindow = nullptr;

    LeftTreeViewWidget* m_treeViewWidget = nullptr;

    void OnOpenChamferDialog();
};
