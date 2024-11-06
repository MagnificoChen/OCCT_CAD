#include "DialogBase.h"

#include "src/CentralViewWidget.h"
#include "src/OccDemoMainWindow.h"


DialogBase::DialogBase(QWidget* parent, ButtonType type) : QDialog(parent)
{
    m_mainLayout = new QVBoxLayout(this);
    setMinimumSize({ 200,200 });
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    initializeButtons(type);
    ownerWidget = OccDemoMainWindow::getInstance()->GetActiveViewWidget();

}

DialogBase::~DialogBase()
{
}

void DialogBase::initializeButtons(ButtonType type)
{
    buttonBox = new QDialogButtonBox();
    m_buttonsLayout = new QHBoxLayout();
    QSpacerItem* spacer = new QSpacerItem(50, 10);
    switch (type)
    {
    case Ok:
    {
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        m_buttonsLayout->addWidget(buttonBox);
        buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));
        connect(buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &DialogBase::OnOK);

        break;
    }
    case OkCancel:
    {
        buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
        m_buttonsLayout->addWidget(buttonBox);
        buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));
        buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);
        buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
        connect(buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &DialogBase::OnOK);
        connect(buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &DialogBase::OnCancel);

        break;
    }
    case All:
    {
        buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
        m_buttonsLayout->addWidget(buttonBox);
        buttonBox->button(QDialogButtonBox::Ok)->setText(tr("确定"));
        buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);
        buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("取消"));
        buttonBox->button(QDialogButtonBox::Apply)->setText(tr("应用"));
        connect(buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &DialogBase::OnOK);
        connect(buttonBox->button(QDialogButtonBox::Apply), &QPushButton::clicked, this, &DialogBase::OnApply);
        connect(buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &DialogBase::OnCancel);
        break;
    }
    case NoButton:
    {
        m_buttonsLayout->addSpacerItem(spacer);
        break;
    }
    }


    m_mainLayout->insertLayout(-1, m_buttonsLayout);
}

QVBoxLayout* DialogBase::GetMainLayout() const
{
    return m_mainLayout;
}

bool DialogBase::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            return true; // 阻止事件传播
        }
    }
    return QDialog::eventFilter(obj, event);
}





