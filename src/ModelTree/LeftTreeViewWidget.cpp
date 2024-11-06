#include "LeftTreeViewWidget.h"
#include <qapplication.h>
#include <TDataStd.hxx>
#include <TDataStd_Integer.hxx>
#include <TDataStd_TreeNode.hxx>
#include <TDataStd_Name.hxx>
#include <TDocStd_Owner.hxx>
#include <TNaming_NamedShape.hxx>
#include <TNaming_UsedShapes.hxx>
#include <XCAFDoc_Color.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFDoc_LayerTool.hxx>
#include <XCAFDoc_ShapeMapTool.hxx>
#include <XCAFDoc_Location.hxx>

#include "src/Dialog/DialogFeatureBase.h"
#include "src/QDocumentManager.h"

LeftTreeViewWidget::LeftTreeViewWidget(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);
    m_treeWidget = new QTreeWidget();
    m_layout->addWidget(m_treeWidget);
    m_treeWidget->setHeaderLabel("Labels & Attributes");
}

LeftTreeViewWidget::~LeftTreeViewWidget()
{
    
}

void LeftTreeViewWidget::Update()
{
    currDoc = QDocumentManager::getInstance()->getCurrentDocument()->getDocumentHandle();
    myList.Clear();

    myGroupIcon = QApplication::style()->standardIcon(QStyle::SP_DirIcon);

    TDataStd::IDList(myList);
    myList.Append(TDataStd_TreeNode::GetDefaultTreeID());
    myList.Append(TDataStd_Integer::GetID());
    myList.Append(TDocStd_Owner::GetID());
    myList.Append(TNaming_NamedShape::GetID());
    myList.Append(TNaming_UsedShapes::GetID());
    myList.Append(XCAFDoc_Color::GetID());
    myList.Append(XCAFDoc_ColorTool::GetID());
    myList.Append(XCAFDoc_LayerTool::GetID());
    myList.Append(XCAFDoc_ShapeTool::GetID());
    myList.Append(XCAFDoc_ShapeMapTool::GetID());
    myList.Append(XCAFDoc_Location::GetID());

}


void LeftTreeViewWidget::load()
{
    m_treeWidget->clear();

    QTreeWidgetItem* root = new QTreeWidgetItem();
    root->setText(0, QLatin1String("0"));
    root->setIcon(0, myGroupIcon);
    m_treeWidget->addTopLevelItem(root);

    load(currDoc->GetData()->Root(), root, QString::fromLatin1("0"));
}

void LeftTreeViewWidget::load(const TDF_Label& label, QTreeWidgetItem* item, const QString& s)
{

    Handle(TDataStd_Name) name;
    if (label.FindAttribute(TDataStd_Name::GetID(), name))
    {
        QString text = QString::fromLatin1("%1 %2").arg(s).arg(QString::fromUtf8(toString(name->Get()).c_str()));
        item->setText(0, text);
    }

    for (TDF_ListIteratorOfIDList it(myList); it.More(); it.Next())
    {
        Handle(TDF_Attribute) attr;
        if (label.FindAttribute(it.Value(), attr))
        {
            QTreeWidgetItem* child = new QTreeWidgetItem();
            if (it.Value() == TDataStd_Name::GetID())
            {
                QString text;
                QTextStream str(&text);
                str << attr->DynamicType()->Name();
                str << " = " << toString(Handle(TDataStd_Name)::DownCast(attr)->Get()).c_str();
                child->setText(0, text);
                item->addChild(child);
            }
            else if (it.Value() == TDF_TagSource::GetID())
            {
                QString text;
                QTextStream str(&text);
                str << attr->DynamicType()->Name();
                str << " = " << Handle(TDF_TagSource)::DownCast(attr)->Get();
                child->setText(0, text);
                item->addChild(child);
            }
            else if (it.Value() == TDataStd_Integer::GetID())
            {
                QString text;
                QTextStream str(&text);
                str << attr->DynamicType()->Name();
                str << " = " << Handle(TDataStd_Integer)::DownCast(attr)->Get();
                child->setText(0, text);
                item->addChild(child);
            }
            else if (it.Value() == TNaming_NamedShape::GetID())
            {
                TopoDS_Shape shape = Handle(TNaming_NamedShape)::DownCast(attr)->Get();
                QString text;
                QTextStream str(&text);
                str << attr->DynamicType()->Name() << " = ";
                if (!shape.IsNull())
                {
                    switch (shape.ShapeType())
                    {
                    case TopAbs_COMPOUND:
                        str << "COMPOUND PRIMITIVE";
                        break;
                    case TopAbs_COMPSOLID:
                        str << "COMPSOLID PRIMITIVE";
                        break;
                    case TopAbs_SOLID:
                        str << "SOLID PRIMITIVE";
                        break;
                    case TopAbs_SHELL:
                        str << "SHELL PRIMITIVE";
                        break;
                    case TopAbs_FACE:
                        str << "FACE PRIMITIVE";
                        break;
                    case TopAbs_WIRE:
                        str << "WIRE PRIMITIVE";
                        break;
                    case TopAbs_EDGE:
                        str << "EDGE PRIMITIVE";
                        break;
                    case TopAbs_VERTEX:
                        str << "VERTEX PRIMITIVE";
                        break;
                    case TopAbs_SHAPE:
                        str << "SHAPE PRIMITIVE";
                        break;
                    }
                }
                child->setText(0, text);
                item->addChild(child);
            }
            else
            {
                child->setText(0, QLatin1String(attr->DynamicType()->Name()));
                item->addChild(child);
            }
        }
    }

    int i = 1;
    for (TDF_ChildIterator it(label); it.More(); it.Next(), i++)
    {
        QString text = QString::fromLatin1("%1:%2").arg(s).arg(i);
        QTreeWidgetItem* child = new QTreeWidgetItem();
        child->setText(0, text);
        child->setIcon(0, myGroupIcon);
        item->addChild(child);
        load(it.Value(), child, text);
    }
}

