#include "OccDemoMainWindow.h"
#include "BRepPrimAPI_MakeBox.hxx"
#include "src/Dialog/DialogFeatureCylinder.h"
#include "src/Dialog/DialogFeatureSphere.h"
#include "QDocumentManager.h"
#include "vtkOpenGLRenderWindow.h"
#include "QVTKOpenGLNativeWidget.h"
#include "src/Dialog/DialogFeatureChamfer.h"

OccDemoMainWindow* OccDemoMainWindow::instance = nullptr;


OccDemoMainWindow* OccDemoMainWindow::getInstance() {
    if (!instance) {
        instance = new OccDemoMainWindow();
    }
    return instance;
}


OccDemoMainWindow::OccDemoMainWindow(QWidget* parent)
        : SARibbonMainWindow(parent) {
    instance = this;

    setMinimumSize({800, 600});

    m_ribbonBar = ribbonBar();

    setWindowTitle("OpenCascade Demo");

    // QWidget模式下，没有必要再显示标题
    m_ribbonBar->setTitleVisible(false);
    m_ribbonBar->setContentsMargins(5, 0, 5, 0);
    QFont font("Microsoft YaHei", 12);
    ribbonBar()->setFont(font);
    // m_ribbonBar->setMinimumWidth(400);


    m_categoryMain = m_ribbonBar->addCategoryPage(tr("&Main"));
    m_categoryMain->setObjectName(("categoryMain"));

    // 初始化中心widget，存放一个QtMdiArea
    m_mdiArea = new QMdiArea();
    this->setCentralWidget(m_mdiArea);
    m_mdiArea->setViewMode(QMdiArea::TabbedView);
    m_mdiArea->setTabsMovable(true);
    m_mdiArea->setTabsClosable(true);
    // m_centralWidget = new CentralViewWidget();
    // this->setCentralWidget(m_centralWidget);


    //状态栏
    m_statusBar = new QStatusBar();
    m_statusBar->setStatusTip("就绪");
    this->setStatusBar(m_statusBar);


    _initializeRibbonBarButtons();
    _initializeTreeDockWindow();


    //init Dialog manager
    m_dialogManager = new QDialogManager();


    //所有单例和manager初始化之后，链接信号和槽
    ConnectSignalAndSlots();
}

OccDemoMainWindow::~OccDemoMainWindow() {
}

void OccDemoMainWindow::_initializeRibbonBarButtons() {
    panel_files = m_categoryMain->addPannel(("Files"));

    QAction* pAction = nullptr;

    //创建Action

    pAction = new QAction(this);
    pAction->setText("保存");
    pAction->setIcon(QIcon(":/image/resource/save-32.png"));
    pAction->setObjectName("actSave");
    connect(pAction, &QAction::triggered, this, &OccDemoMainWindow::OnSaveDocument);
    panel_files->addLargeAction(pAction);


    SARibbonMenu* menu = new SARibbonMenu(this);
    {
        {
            QAction* a = nullptr;
            a = menu->addAction(QIcon(":/image/resource/open-32.png"), tr("导入Session文件"));
            a->setObjectName(QStringLiteral("importOption1"));
            //connect
            connect(a, &QAction::triggered, this, &OccDemoMainWindow::OnLoadDocument);
        }
        {
            QAction* a = nullptr;
            a = menu->addAction(QIcon(":/image/resource/open-32.png"), tr("导入STL文件"));
            a->setObjectName(QStringLiteral("importOption2"));
            //connect
            connect(a, &QAction::triggered, this, &OccDemoMainWindow::OnLoadSTL);
        }
        {
            QAction* a = nullptr;
            a = menu->addAction(QIcon(":/image/resource/open-32.png"), tr("导入STEP文件"));
            a->setObjectName(QStringLiteral("importOption3"));
            //connect
            connect(a, &QAction::triggered, this, &OccDemoMainWindow::OnLoadSTEP);
        }
    }
    pAction = new QAction(this);
    pAction->setText("读取");
    pAction->setIcon(QIcon(":/image/resource/open-32.png"));
    pAction->setMenu(menu);
    pAction->setObjectName("actLoad");
    panel_files->addLargeAction(pAction, QToolButton::MenuButtonPopup);


    panel_feature2D = m_categoryMain->addPannel(("2D Features"));
    //草图
    pAction = new QAction(this);
    pAction->setText("Sketch");
    pAction->setIcon(QIcon(":/image/resource/draft.png"));
    pAction->setObjectName("actOpenDlgSketch");
    panel_feature2D->addLargeAction(pAction);
    pAction = new QAction(this);
    //圆
    pAction->setText("Circle");
    pAction->setIcon(QIcon(":/image/resource/circle.png"));
    pAction->setObjectName("actOpenDlgCircle");
    panel_feature2D->addLargeAction(pAction);
    connect(pAction, &QAction::triggered, this, &OccDemoMainWindow::OnOpenSphereDialog);
    //矩形
    pAction = new QAction(this);
    pAction->setText("Rectangle");
    pAction->setIcon(QIcon(":/image/resource/rectangle.png"));
    pAction->setObjectName("actOpenDlgRect");
    panel_feature2D->addLargeAction(pAction);


    panel_feature3D = m_categoryMain->addPannel(("3D Features"));
    //球体
    pAction = new QAction(this);
    pAction->setText("Sphere");
    pAction->setIcon(QIcon(":/image/resource/sphere.png"));
    pAction->setObjectName("actOpenDlgSphere");
    panel_feature3D->addLargeAction(pAction);
    connect(pAction, &QAction::triggered, this, &OccDemoMainWindow::OnOpenSphereDialog);
    //立方体
    pAction = new QAction(this);
    pAction->setText("Cube");
    pAction->setIcon(QIcon(":/image/resource/cube.png"));
    pAction->setObjectName("actOpenDlgCube");
    panel_feature3D->addLargeAction(pAction);
    connect(pAction, &QAction::triggered, this, &OccDemoMainWindow::OnOpenCubeDialog);
    //圆柱
    pAction = new QAction(this);
    pAction->setText("Cylinder");
    pAction->setIcon(QIcon(":/image/resource/cylinder.png"));
    pAction->setObjectName("actOpenDlgCyl");
    panel_feature3D->addLargeAction(pAction);
    connect(pAction, &QAction::triggered, this, &OccDemoMainWindow::OnOpenCylinderDialog);


    panel_basic = m_categoryMain->addPannel(("Basic"));
    pAction = new QAction(this);
    pAction->setText("Extrusion");
    pAction->setIcon(QIcon(":/image/resource/extrusion.png"));
    pAction->setObjectName("actOpenDlgExtrusion");
    panel_basic->addLargeAction(pAction);

    pAction = new QAction(this);
    pAction->setText("Sweep");
    pAction->setIcon(QIcon(":/image/resource/sweep.png"));
    pAction->setObjectName("actOpenDlgSweep");
    panel_basic->addLargeAction(pAction);

    pAction = new QAction(this);
    pAction->setText("Chamfer");
    pAction->setIcon(QIcon(":/image/resource/chamfer.png"));
    pAction->setObjectName("actOpenDlgChamfer");
    panel_basic->addLargeAction(pAction);
    connect(pAction, &QAction::triggered, this, &OccDemoMainWindow::OnOpenChamferDialog);


    //QuickAccessBar
    pAction = new QAction(this);
    pAction->setIcon(QIcon(":/image/resource/add-file-32.png"));
    pAction->setObjectName("actNewDoc");
    connect(pAction, &QAction::triggered, this, &OccDemoMainWindow::OnNewMDIWindow);
    m_ribbonBar->quickAccessBar()->addAction(pAction);

    //初始化时，功能性按钮不可用。
    for (auto item: panel_feature2D->ribbonToolButtons()) {
        item->setEnabled(false);
    }
    for (auto item: panel_feature3D->ribbonToolButtons()) {
        item->setEnabled(false);
    }
    for (auto item: panel_basic->ribbonToolButtons()) {
        item->setEnabled(false);
    }
}

void OccDemoMainWindow::OnOpenSphereDialog() {
    auto dialog = new DialogFeatureSphere(this);
    m_dialogManager->OpenDialog(dialog);
}

void OccDemoMainWindow::OnOpenCubeDialog() {
    auto dialog = new DialogFeatureCube(this);
    m_dialogManager->OpenDialog(dialog);
}

void OccDemoMainWindow::OnOpenCylinderDialog() {
    auto dialog = new DialogFeatureCylinder(this);
    m_dialogManager->OpenDialog(dialog);
}

void OccDemoMainWindow::OnOpenChamferDialog() {
    auto dialog = new DialogFeatureChamfer(this);
    m_dialogManager->OpenDialog(dialog);
}

QMdiArea* OccDemoMainWindow::getMdiArea() const {
    return m_mdiArea;
}

//新建MDI窗口
bool OccDemoMainWindow::OnNewMDIWindow() {
    auto win = new CentralViewWidget();

    // 创建MDI窗口
    auto subwindow = m_mdiArea->addSubWindow(win);
    //此时会触发subWindowActivated信号,
    win->setFocus();
    //创建Doc文档
    emit signalAddNewDocument(false, QString());
    connect(QDocumentManager::getInstance(), &QDocumentManager::signalUpdateView, win, &CentralViewWidget::UpdateView,
            Qt::DirectConnection);
    //创建View

    return true;
}

void OccDemoMainWindow::ConnectSignalAndSlots() {
    //添加/加载Document
    connect(this, &OccDemoMainWindow::signalAddNewDocument, QDocumentManager::getInstance(),
            &QDocumentManager::OnNewDocument);
    //保存Document
    connect(this, &OccDemoMainWindow::signalSaveDocument, QDocumentManager::getInstance(),
            &QDocumentManager::SaveDocument);
    connect(this, &OccDemoMainWindow::signalLoadGeometry, QDocumentManager::getInstance(),
            &QDocumentManager::LoadGeometry);

    //切换SubWindow/Document
    connect(m_mdiArea, &QMdiArea::subWindowActivated, this, &OccDemoMainWindow::OnChangeSubWindow);
    connect(this, &OccDemoMainWindow::signalChangeCurrDocument, QDocumentManager::getInstance(),
            &QDocumentManager::OnChangeCurDocument);
}

bool OccDemoMainWindow::OnSaveDocument() {
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save As"), "", tr("New Document Files (*.cbf)"));
    if (!filePath.isEmpty()) {
        //处理Path
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        // filePath.chop(4);
        //然后，判断当前View对应的Document，向该Document发送指令
        emit signalSaveDocument(filePath);
        return true;
    }

    return false;
}

bool OccDemoMainWindow::OnLoadDocument() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Load"), ".", tr("STereoLithography Files (*.cbf)"));
    if (!filePath.isEmpty()) {
        emit signalAddNewDocument(true, filePath);
        return true;
    }

    return false;
}

bool OccDemoMainWindow::OnLoadSTL() {
    QString filePath = _OpenFileDialog(STL);
    if (!filePath.isEmpty()) {
        auto result = QMessageBox::information(this, "提示", "在新窗口中导入？", QMessageBox::Yes | QMessageBox::No);
        if (result == QMessageBox::StandardButton::Yes) {
            OnNewMDIWindow();
        } else { ;
        }

        emit signalLoadGeometry(filePath, STL);
        return true;
    }

    return false;
}

bool OccDemoMainWindow::OnLoadSTEP() {
    QString filePath = _OpenFileDialog(STEP);
    if (!filePath.isEmpty()) {
        auto result = QMessageBox::information(
                this, "提示", "在新窗口中导入？", QMessageBox::Yes | QMessageBox::No);
        if (m_lastActiveSubWindow == nullptr | result == QMessageBox::StandardButton::Yes) {
            OnNewMDIWindow();
        } else { ;
        }

        emit signalLoadGeometry(filePath, STEP);
        return true;
    }

    return false;
}

QString OccDemoMainWindow::_OpenFileDialog(FileFormat f) {
    QString filter;
    switch (f) {
        case CBF: {
            filter = "STereoLithography Files (*.cbf)";
            break;
        }
        case STL: {
            filter = "STereoLithography Files (*.stl)";
            break;
        }
        case STEP: {
            filter = "STEP Files (*.stp) ;; STEP Files (*.step)";
            break;
        }
        default: {
            filter = " ALL files (*)";
            break;
        }
    }
    return QFileDialog::getOpenFileName(this, tr("Import Geometry"), ".", filter);
}

void OccDemoMainWindow::_initializeTreeDockWindow() {
    m_treeDock = new QDockWidget(this);
    m_treeViewWidget = new LeftTreeViewWidget();
    m_treeDock->setWindowTitle("模型树");
    m_treeDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea); // 允许停靠在左右两侧
    m_treeDock->setWidget(m_treeViewWidget);
    addDockWidget(Qt::LeftDockWidgetArea, m_treeDock);
}

void OccDemoMainWindow::OnChangeSubWindow(QMdiSubWindow* subWin) {
    //类型转换需要确定取到的widget是否是CentralViewWidget。

    if (m_mdiArea->activeSubWindow() &&
        m_mdiArea->activeSubWindow()->widget() &&
        _viewDocMap.contains(static_cast<CentralViewWidget*>(m_mdiArea->activeSubWindow()->widget())) &&
        subWin != m_lastActiveSubWindow) {
        signalChangeCurrDocument(_viewDocMap[static_cast<CentralViewWidget*>(subWin->widget())]);
        m_lastActiveSubWindow = subWin;
        //不管如何，都需要关闭当前对话框。
        QDialogManager::getInstance()->closeCurrDialog();
        m_treeViewWidget->Update();
        m_treeViewWidget->load();
    }

    if (!subWin) {
        for (auto item: panel_feature2D->ribbonToolButtons()) {
            item->setEnabled(false);
        }
        for (auto item: panel_feature3D->ribbonToolButtons()) {
            item->setEnabled(false);
        }
        for (auto item: panel_basic->ribbonToolButtons()) {
            item->setEnabled(false);
        }
    }else{
        for (auto item: panel_feature2D->ribbonToolButtons()) {
            item->setEnabled(true);
        }
        for (auto item: panel_feature3D->ribbonToolButtons()) {
            item->setEnabled(true);
        }
        for (auto item: panel_basic->ribbonToolButtons()) {
            item->setEnabled(true);
        }
    }
}

CentralViewWidget* OccDemoMainWindow::GetActiveViewWidget() {
    return static_cast<CentralViewWidget*>(m_mdiArea->activeSubWindow()->widget());
}

bool OccDemoMainWindow::AddViewDocItem(std::pair<CentralViewWidget*, QOccDocument*> item) {
    if (_viewDocMap.find(item.first) != _viewDocMap.end()) {
        return false;
    }
    _viewDocMap.insert(item);
    _docViewMap.insert({item.second, item.first});
    return true;
}

void OccDemoMainWindow::UpdateView() {
    // emit 
}


void OccDemoMainWindow::UpdateTreeView() {
    m_treeViewWidget->Update();
    m_treeViewWidget->load();
}

CentralViewWidget* OccDemoMainWindow::getCentralWidgetByDocument(QOccDocument* doc) {

    if (_docViewMap.contains(doc)) return _docViewMap[doc];
    return nullptr;
}

QOccDocument* OccDemoMainWindow::getDocumentByCentralWidget(CentralViewWidget* view) {
    if (_viewDocMap.contains(view)) return _viewDocMap[view];
    return nullptr;
}
