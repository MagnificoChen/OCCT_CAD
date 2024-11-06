#pragma once

#include <QStandardItemModel>

class DocumentTreeItemModel  : public QStandardItemModel
{
    Q_OBJECT

public:
    DocumentTreeItemModel(QObject *parent);
    ~DocumentTreeItemModel();
};
