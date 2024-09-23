
#include "QDialogManager.h"

QDialogManager* QDialogManager::instance = nullptr;
QDialogManager* QDialogManager::getInstance()
{
    if (!instance)
    {
        instance = new QDialogManager(); 
    }
    return instance;
}

QDialogManager::QDialogManager()
{
    instance = this;
}

QDialogManager::~QDialogManager()
{
    if (currDialog)
    {
        currDialog->deleteLater();
    }
}
void QDialogManager::OpenDialog(QDialog* dialog)
{
    if(!dialog)
    {
        qDebug()<<"dialog is null";
        return;
    }
    if (currDialog)
    {
        // 如果当前有对话框打开，先关闭它
        currDialog->close(); 
    }

    // 连接新的对话框的finished信号，以便在对话框关闭时得到通知
    connect(dialog, &QDialog::finished, this, &QDialogManager::onDialogClosed);

    // 显示新对话框并记录为当前对话框
    dialog->show();
    currDialog = dialog;
}

void QDialogManager::onDialogClosed()
{
    // 在对话框关闭时调用 deleteLater
    if (currDialog)
    {
        currDialog->deleteLater();
        currDialog = nullptr;
    }
}

void QDialogManager::closeCurrDialog()
{
    if(currDialog)
    {
        currDialog->close();
    }
}
