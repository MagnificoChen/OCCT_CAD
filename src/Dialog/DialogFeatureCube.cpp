#include "DialogFeatureCube.h"

#include "DialogInputPosition.h"
#include "src/Feature/FeatureCube.h"
#include "src/QDocumentManager.h"
#include "src/Dialog/Components/QOccGeoSelector.h"

DialogFeatureCube::DialogFeatureCube(QWidget* parent)
    : DialogFeatureBase(parent)
{
    m_cubeXLabel = new QLabel("输入X长度");
    m_cubeXSpinbox = new QDoubleSpinBox();
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m_cubeXLabel,1);
    layout->addWidget(m_cubeXSpinbox, 2);
    m_vLayout->addLayout(layout);


    m_cubeYLabel = new QLabel("输入Y长度");
    m_cubeYSpinbox = new QDoubleSpinBox();
    layout = new QHBoxLayout();
    layout->addWidget(m_cubeYLabel, 1);
    layout->addWidget(m_cubeYSpinbox, 2);
    m_vLayout->addLayout(layout);

    m_cubeZLabel = new QLabel("输入Z长度");
    m_cubeZSpinbox = new QDoubleSpinBox();
    layout = new QHBoxLayout();
    layout->addWidget(m_cubeZLabel, 1);
    layout->addWidget(m_cubeZSpinbox, 2);

    

    m_vLayout->addLayout(layout);

    m_buttonOpenPosDialog = new QPushButton("点击打开位置对话框");
    m_vLayout->addWidget(m_buttonOpenPosDialog);

    GetMainLayout()->insertLayout(0,layout);


    //connect signals and slots
    connect(m_buttonOpenPosDialog,&QPushButton::pressed,this,&DialogFeatureCube::OnOpenPosDialog);
}

DialogFeatureCube::~DialogFeatureCube()
{
    
}



void DialogFeatureCube::OnApply()
{

}

void DialogFeatureCube::OnCancel()
{
    done(QDialog::Rejected);

}

void DialogFeatureCube::OnOK()
{
    auto currDoc = QDocumentManager::getInstance()->getCurrentDocument();
    auto cube = std::make_shared<FeatureCube>(currDoc,1,1,1);
    cube->createRenderPipeline();
    qDebug() << "ok pressed";
    done(QDialog::Accepted);
}

void DialogFeatureCube::DisableAllGeoSelector()
{
}

void DialogFeatureCube::OnOpenPosDialog()
{
    DialogInputPosition* dialog = new DialogInputPosition();
    connect(dialog, &QDialog::accepted, this, &DialogFeatureCube::OnPosReceived);

    dialog->setWindowTitle(tr("Input"));
    dialog->exec();
}

void DialogFeatureCube::OnPosReceived()
{
    QMessageBox::information(this,"1", "1");
}
