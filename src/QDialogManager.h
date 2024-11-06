#pragma once
#include "CentralViewWidget.h"
#include "QObject"
#include "QDialog"
#include "QDebug"
class QDialogManager : public QObject
{
    Q_OBJECT
public:
    static QDialogManager* getInstance();
    void OpenDialog(QDialog* dialog);
    void onDialogClosed();
    void closeCurrDialog();
    QDialogManager();
    ~QDialogManager();


private:
    QDialog* currDialog = nullptr;
    static QDialogManager* instance;
};

