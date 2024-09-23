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
    bool AddViewDocItem(std::pair<CentralViewWidget*, int> item);
    //根据Document中的内容更新View。
    void UpdateView();
    std::map< CentralViewWidget*, int> getViewDocMap() const;
    std::map<int, CentralViewWidget*> getDocViewMap() const;

    void UpdateTreeView();
    

signals:
    //To QDocumentManager:
    //此信号用于New/Load Document时发出
    void signalAddNewDocument(bool isLoad, const QString& path);
    void signalSaveDocument(const QString& path);


    //导入几何体，如stl文件等。导入到当前Document
    void signalLoadGeometry(const QString& path, FileFormat format);
    //这意味着切换了标签页，需要改变CurrentDocument。
    void signalChangeCurrDocument(int tag);

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

    //需要存储Tag和SubWindow的一对一关系
    std::map< CentralViewWidget*,int> m_viewDocMap;
    //需要存储Tag和SubWindow的一对一关系
    std::map< int,CentralViewWidget* > m_docViewMap;

    QMdiSubWindow* m_lastActiveSubWindow = nullptr;

    LeftTreeViewWidget* m_treeViewWidget = nullptr;
};
