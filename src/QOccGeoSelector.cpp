#include "QOccGeoSelector.h"

#include <QComboBox>
#include <qaction.h>

#include "CentralViewWidget.h"
#include "src/Dialog/DialogFeatureSphere.h"
#include "QDocumentManager.h"
QOccGeoSelector::QOccGeoSelector(IVtk_SelectionMode mode, QWidget* parent)
    : QWidget(parent)
{
    //init components
    m_layout = new QHBoxLayout(this);
    m_toolbutton_sel = new QToolButton();
    m_toolbutton_sel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    m_toolbutton_sel->setText("未选择");
    m_toolbutton_sel->setIcon(QIcon(":/image/resource/cube.png"));
    m_toolbutton_sel->setCheckable(true);
    connect(m_toolbutton_sel, &QToolButton::toggled, this, &QOccGeoSelector::OnSelectButtonToggled);

    m_toolbutton_delete = new QToolButton();
    m_toolbutton_delete->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_toolbutton_delete->setIcon(QIcon(":/image/resource/deSelect.png"));
    connect(m_toolbutton_delete, &QToolButton::toggled, this, &QOccGeoSelector::OnDeleteButtonToggled);


    m_toolbutton_selMode = new QToolButton();
    m_toolbutton_selMode->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_toolbutton_selMode->setIcon(QIcon(":/image/resource/sphere.png"));
    m_toolbutton_selMode->setPopupMode(QToolButton::InstantPopup);

    {
        QAction* pAction = new QAction("顶点");
        m_toolbutton_selMode->addAction(pAction);
        connect(pAction, &QAction::triggered, this, &QOccGeoSelector::OnChangeSelectMode);
        pAction = new QAction("边");
        m_toolbutton_selMode->addAction(pAction);
        connect(pAction, &QAction::triggered, this, &QOccGeoSelector::OnChangeSelectMode);

        pAction = new QAction("面");
        m_toolbutton_selMode->addAction(pAction);
        connect(pAction, &QAction::triggered, this, &QOccGeoSelector::OnChangeSelectMode);

        pAction = new QAction("体");
        m_toolbutton_selMode->addAction(pAction);
        connect(pAction, &QAction::triggered, this, &QOccGeoSelector::OnChangeSelectMode);

        pAction = new QAction("无");
        m_toolbutton_selMode->addAction(pAction);
        connect(pAction, &QAction::triggered, this, &QOccGeoSelector::OnChangeSelectMode);
    }


    m_layout->addWidget(m_toolbutton_sel, 4);
    m_layout->addWidget(m_toolbutton_selMode, 1);
    m_layout->addWidget(m_toolbutton_delete, 1);
    m_toolbutton_sel->setMinimumSize({120,40});
    m_toolbutton_sel->setMaximumWidth(1000);
    m_toolbutton_selMode->setMinimumSize({40,40});
    m_toolbutton_delete->setMinimumSize({40,40});


    ownerWidget = QDocumentManager::getInstance()->getCurrentDocument()->getCentralWidget();
    connect(this, &QOccGeoSelector::SelectModeChanged, ownerWidget, &CentralViewWidget::OnSetSelectionMode);
    if (QDocumentManager::getInstance()->getCurrentDocument() != nullptr)
    {
        connect(this, &QOccGeoSelector::SelectModeChanged, ownerWidget, &CentralViewWidget::OnSetSelectionMode);
    }
    else
    {
        m_toolbutton_sel->setEnabled(false);
        m_toolbutton_selMode->setEnabled(false);
    }
}


QOccGeoSelector::~QOccGeoSelector()
{
    emit SelectModeChanged(SM_None);
}


void QOccGeoSelector::setLabelText(QString text)
{
    m_toolbutton_sel->setText(text);
}

void QOccGeoSelector::setSelectModeChangeable(bool isChangeable)
{
    _isSelectModeChangeable = isChangeable;
}

void QOccGeoSelector::setCapacity(int n)
{
    if (n < 1 || n>5) return;
    m_capacity = n;
}


//TODO:补充其他弹起按钮功能。
void QOccGeoSelector::Disable()
{
    m_toolbutton_sel->setChecked(false);
}

bool QOccGeoSelector::addSelectedShape(const TopoDS_Shape& shape)
{
    if (m_capacity <= m_selectedShapes.size()) return false;
    auto it = std::find_if(m_selectedShapes.begin(), m_selectedShapes.end(),
                           [&shape](const std::reference_wrapper<const TopoDS_Shape>& ref)
                           {
                               return std::equal_to{}(ref.get(), shape);
                           });
    if (it != m_selectedShapes.end())
    {
        return false;
    }
    m_selectedShapes.push_back(shape);
    OnGeoSelected();

    return true;
}

bool QOccGeoSelector::deleteSelectedShape(const TopoDS_Shape& shape)
{
    // 查找 shape 是否存在于 m_selectedShapes 中
    auto it = std::find_if(m_selectedShapes.begin(), m_selectedShapes.end(),
                           [&shape](const std::reference_wrapper<const TopoDS_Shape>& ref)
                           {
                               return std::equal_to{}(ref.get(), shape);
                           });
    // 如果找到了 shape
    if (it != m_selectedShapes.end())
    {
        // 从向量中删除 shape
        m_selectedShapes.erase(it);
        OnGeoSelected();
        return true; // 表示成功删除
    }

    return true;
}

void QOccGeoSelector::clearSelectedShape()
{
    m_selectedShapes.clear();
}


void QOccGeoSelector::OnChangeSelectMode()
{
    QAction* action = qobject_cast<QAction*>(QObject::sender());
    if (!m_toolbutton_sel->isChecked()) return;
    if (action->text() == "点")
    {
        SelectModeChanged(SM_Vertex);
        currSelMode = SM_Vertex;
        m_toolbutton_sel->setText("选择顶点");
    }
    if (action->text() == "边")
    {
        SelectModeChanged(SM_Edge);
        currSelMode = SM_Edge;
        m_toolbutton_sel->setText("选择边");
    }
    if (action->text() == "面")
    {
        SelectModeChanged(SM_Face);
        currSelMode = SM_Face;
        m_toolbutton_sel->setText("选择面");
    }
    if (action->text() == "体")
    {
        SelectModeChanged(SM_Shape);
        currSelMode = SM_Shape;
        m_toolbutton_sel->setText("选择体");
    }
    if (action->text() == "无")
    {
        SelectModeChanged(SM_None);
        currSelMode = SM_None;
        m_toolbutton_sel->setText("已禁用");
    }
}

void QOccGeoSelector::OnGeoSelected()
{
    if (!m_toolbutton_sel->isChecked()) return;
    if (m_selectedShapes.empty())
    {
        m_toolbutton_sel->setText("未选中");
    }
    else
    {
        auto str = QString("已选中 %1 个对象").arg(m_selectedShapes.size());
        qDebug() << str;
        m_toolbutton_sel->setText(str);
    }
}

void QOccGeoSelector::OnSelectButtonToggled()
{
    if (!m_toolbutton_sel->isChecked())
    {
        emit SelectModeChanged(SM_None);
        m_toolbutton_sel->setText("已禁用");
    }
    else
    {
        //通知InteractorStyle，记录选择内容和当前选择器
        emit SelectModeChanged(currSelMode);
        //通知对话框，禁用其他选择器
        QMetaObject::invokeMethod(parent(), "DisableAllGeoSelector", Qt::DirectConnection);
        switch (currSelMode)
        {
        case SM_Vertex:
            {
                m_toolbutton_sel->setText("选择点");
                break;
            }
        case SM_Edge:
            {
                m_toolbutton_sel->setText("选择点");
                break;
            }
        case SM_Face:
            {
                m_toolbutton_sel->setText("选择点");
                break;
            }
        case SM_Shape:
            {
                m_toolbutton_sel->setText("选择点");
                break;
            }
        default: break;
        }
    }
}

void QOccGeoSelector::OnDeleteButtonToggled()
{
    //仅在激活时有效 
    if (!m_toolbutton_sel->isChecked()) return;

    emit DeSelected();
    m_selectedShapes.clear();
}
