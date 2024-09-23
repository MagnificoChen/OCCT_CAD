#pragma once

#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <TDF_IDList.hxx>

#include "src/CentralViewWidget.h"

class LeftTreeViewWidget : public QWidget
{
    Q_OBJECT

public:
    LeftTreeViewWidget(QWidget *parent = nullptr);
    ~LeftTreeViewWidget();
    void load();
    void load(const TDF_Label& label, QTreeWidgetItem* item, const QString& s);

public:
    std::string toString(const TCollection_ExtendedString& extstr) const
    {
        char* str = new char[extstr.LengthOfCString() + 1];
        extstr.ToUTF8CString(str);
        std::string text(str);
        delete[] str;
        return text;
    }
public slots:
    void Update();
    

private:
    Handle(TDocStd_Document) currDoc;

    QVBoxLayout* m_layout = nullptr;
    QTreeWidget* m_treeWidget = nullptr;
    QIcon myGroupIcon;
    TDF_IDList myList;

};
