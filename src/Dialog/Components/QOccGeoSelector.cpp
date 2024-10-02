#include "QOccGeoSelector.h"

#include <QComboBox>
#include <qaction.h>

#include "src/CentralViewWidget.h"
#include "src/Dialog/DialogFeatureSphere.h"
#include "src/QDocumentManager.h"
#include "QOccPointSelector.h"

QOccGeoSelector::QOccGeoSelector(CentralViewWidget* widget) {
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
//    connect(m_toolbutton_delete, &QToolButton::toggled, this, &QOccPointSelector::OnDeleteButtonToggled);


    m_toolbutton_selMode = new QToolButton();
    m_toolbutton_selMode->setToolButtonStyle(Qt::ToolButtonIconOnly);
    m_toolbutton_selMode->setIcon(QIcon(":/image/resource/sphere.png"));
    m_toolbutton_selMode->setPopupMode(QToolButton::InstantPopup);


    m_layout->addWidget(m_toolbutton_sel, 4);
    m_layout->addWidget(m_toolbutton_selMode, 1);
    m_layout->addWidget(m_toolbutton_delete, 1);
    m_toolbutton_sel->setMinimumSize({120, 40});
    m_toolbutton_sel->setMaximumWidth(1000);
    m_toolbutton_selMode->setMinimumSize({40, 40});
    m_toolbutton_delete->setMinimumSize({40, 40});


    ownerWidget = widget;

    connect(this, &QOccGeoSelector::SelectModeChanged, ownerWidget, &CentralViewWidget::OnSetSelectionMode);
    if (QDocumentManager::getInstance()->getCurrentDocument() != nullptr) {
//        connect(this, &QOccPointSelector::SelectModeChanged, ownerWidget, &CentralViewWidget::OnSetSelectionMode);
    } else {
        m_toolbutton_sel->setEnabled(false);
        m_toolbutton_selMode->setEnabled(false);
    }
}

QOccGeoSelector::~QOccGeoSelector() {
    emit SelectModeChanged(SM_None);

}


void QOccGeoSelector::setLabelText(QString text) {
    m_toolbutton_sel->setText(text);
}


void QOccGeoSelector::setCapacity(int n) {
    if (n < 1 || n > 5) return;
    m_capacity = n;
}



[[maybe_unused]] void QOccGeoSelector::Disable() {
    m_toolbutton_sel->setChecked(false);
}



bool QOccGeoSelector::isEnabled() {
    return m_toolbutton_sel->isEnabled();
}

void QOccGeoSelector::EnableItem(bool isEnable) {
    m_toolbutton_sel->setEnabled(isEnable);
    m_toolbutton_selMode->setEnabled(isEnable);
    m_toolbutton_delete->setEnabled(isEnable);
}

void QOccGeoSelector::OnSelectButtonToggled() {
    if (m_toolbutton_sel->isChecked()) {
        emit OnDisableOtherSelectors();
    }
}





