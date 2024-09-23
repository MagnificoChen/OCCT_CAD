#include "DialogFeatureCylinder.h"

#include "DialogInputPosition.h"
#include "src/Feature/FeatureCube.h"
#include "src/Feature/FeatureCylinder.h"
#include "src/QDocumentManager.h"
#include "src/QOccGeoSelector.h"

DialogFeatureCylinder::DialogFeatureCylinder(QWidget* parent)
    : DialogFeatureBase(parent)
{
    m_cubeRadiusLabel = new QLabel("输入X长度");
    m_cubeRadiusSpinbox = new QDoubleSpinBox();
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m_cubeRadiusLabel, 1);
    layout->addWidget(m_cubeRadiusSpinbox, 2);
    m_vLayout->addLayout(layout);


    m_cubeHeightLabel = new QLabel("输入Y长度");
    m_cubeHeightSpinbox = new QDoubleSpinBox();
    layout = new QHBoxLayout();
    layout->addWidget(m_cubeHeightLabel, 1);
    layout->addWidget(m_cubeHeightSpinbox, 2);
    m_vLayout->addLayout(layout);


    m_buttonOpenPosDialog = new QPushButton("点击打开位置对话框");
    m_vLayout->addWidget(m_buttonOpenPosDialog);

    GetMainLayout()->insertLayout(0, layout);


    //connect signals and slots
    connect(m_buttonOpenPosDialog, &QPushButton::pressed, this, &DialogFeatureCylinder::OnOpenPosDialog);
}

DialogFeatureCylinder::~DialogFeatureCylinder()
{

}



void DialogFeatureCylinder::OnApply()
{

}

void DialogFeatureCylinder::OnCancel()
{
    done(QDialog::Rejected);

}

void DialogFeatureCylinder::OnOK()
{
    auto currDocHandle = QDocumentManager::getInstance()->getCurrentDocument()->getDocumentHandle();
    FeatureCylinder cyl;
    cyl.addFeature();
    qDebug() << "ok pressed";
    done(QDialog::Accepted);
}

void DialogFeatureCylinder::DisableAllGeoSelector()
{
}

void DialogFeatureCylinder::OnOpenPosDialog()
{
    DialogInputPosition* dialog = new DialogInputPosition();
    connect(dialog, &QDialog::accepted, this, &DialogFeatureCylinder::OnPosReceived);

    dialog->setWindowTitle(tr("Input"));
    dialog->exec();
}

void DialogFeatureCylinder::OnPosReceived()
{
    QMessageBox::information(this, "1", "1");
}
