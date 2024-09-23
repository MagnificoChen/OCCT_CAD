#include "DialogFeatureSphere.h"
#include "QDebug"
#include "src/Feature/FeatureSphere.h"
#include "src/QOccGeoSelector.h"

DialogFeatureSphere::DialogFeatureSphere(QWidget* parent)
    : DialogBase(parent, OkCancel)
{
    m_cubeRadiusLabel = new QLabel("输入Radius");
    m_cubeRadiusSpinbox = new QDoubleSpinBox();
    m_cubeRadiusSpinbox->setValue(0.5);

    m_cubeXLabel = new QLabel("输入X");
    m_cubeXSpinbox = new QDoubleSpinBox();
    m_cubeXSpinbox->setValue(0);

    m_cubeYLabel = new QLabel("输入Y");
    m_cubeYSpinbox = new QDoubleSpinBox();
    m_cubeYSpinbox->setValue(0);

    m_cubeZLabel = new QLabel("输入Z");
    m_cubeZSpinbox = new QDoubleSpinBox();
    m_cubeZSpinbox->setValue(0);

    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(m_cubeRadiusLabel, 1);
    layout->addWidget(m_cubeRadiusSpinbox, 2);
    GetMainLayout()->insertLayout(0, layout);

    GetMainLayout()->addSpacing(20);

    layout = new QHBoxLayout();
    layout->addWidget(m_cubeXLabel, 1);
    layout->addWidget(m_cubeXSpinbox, 2);
    GetMainLayout()->insertLayout(1, layout);

    layout = new QHBoxLayout();
    layout->addWidget(m_cubeYLabel, 1);
    layout->addWidget(m_cubeYSpinbox, 2);
    GetMainLayout()->insertLayout(2, layout);

    layout = new QHBoxLayout();
    layout->addWidget(m_cubeZLabel, 1);
    layout->addWidget(m_cubeZSpinbox, 2);
    GetMainLayout()->insertLayout(3, layout);

    m_selector = new QOccGeoSelector(SM_Vertex);
    m_selector->setSelectModeChangeable(true);
    m_selector->setCapacity(5);

    GetMainLayout()->insertWidget(0, m_selector);
}

DialogFeatureSphere::~DialogFeatureSphere()
{
}

void DialogFeatureSphere::OnApply()
{
}

void DialogFeatureSphere::OnCancel()
{
    done(QDialog::Rejected);
}

void DialogFeatureSphere::OnOK()
{
    auto currDocHandle = QDocumentManager::getInstance()->getCurrentDocument()->getDocumentHandle();

    FeatureSphere sphere(m_cubeRadiusSpinbox->value());
    sphere.addFeature();
    
    sphere.SetPosition({
        m_cubeXSpinbox->value(), m_cubeYSpinbox->value(), m_cubeZSpinbox->value()
    });

    qDebug() << "ok pressed";
    QDocumentManager::getInstance()->getCurrentDocument()->getCentralWidget()->UpdateView();
    done(QDialog::Accepted);
}

void DialogFeatureSphere::DisableAllGeoSelector()
{
    QMessageBox::information(this, "test", "test1");
}
