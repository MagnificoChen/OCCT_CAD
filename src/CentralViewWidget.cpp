﻿#include "CentralViewWidget.h"

#include <BRepPrimAPI_MakeBox.hxx>
#include <vtkAutoInit.h>
#include <XCAFDoc_DocumentTool.hxx>
#include "QOccDocument.h"
#include "src/Render/QOccVtkSelPipeline.h"
#include <vtkArrowSource.h>
#include <vtkPlaneSource.h>

#include "src/Render/vtkSelectableCoordinate.h"

VTK_MODULE_INIT(vtkRenderingOpenGL2);

VTK_MODULE_INIT(vtkInteractionStyle);

VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

VTK_MODULE_INIT(vtkRenderingFreeType);


CentralViewWidget::CentralViewWidget(QWidget* parent)
    : QWidget(parent)
      , _widget(parent)
      , m_renderWindow(vtkGenericOpenGLRenderWindow::New())
      , m_renderer(vtkSmartPointer<vtkRenderer>::New())
      , m_vtkWidget(new QVTKOpenGLNativeWidget())
      , m_shapePicker(vtkSmartPointer<IVtkTools_ShapePicker>::New())
      , m_interactorStyle(vtkSmartPointer<QOccVtkInteractorStyle>::New())
      , m_camera(vtkCamera::New())
{
    m_vtkWidget->setRenderWindow(m_renderWindow);
    m_interactor = m_vtkWidget->interactor();

    vtkNew<vtkNamedColors> colors;

    m_renderer->SetBackground(colors->GetColor3d("White").GetData());
    m_renderer->SetBackground2(0.5, 0.6, 0.8);
    m_renderer->SetGradientBackground(true);

    m_renderWindow->AddRenderer(m_renderer);

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_vtkWidget);

    //set camera
    m_renderer->SetActiveCamera(m_camera);
    m_camera->ParallelProjectionOn();

    _initializeAxis();
    _initInteractor();

    //for test
    vtkSmartPointer<vtkSelectableCoordinate> coord = vtkSelectableCoordinate::New();
    coord->SetRenderer(m_renderer);
    coord->AddToRenderer();


}

CentralViewWidget::~CentralViewWidget()
{
}

void CentralViewWidget::SetDocument(QOccDocument* doc)
{
    m_document = doc;
}


void CentralViewWidget::_initInteractor()
{
    // Setup IVtk Shape picker
    m_shapePicker->SetRenderer(m_renderer);
    m_shapePicker->SetTolerance(0.025);

    // Setup interactor style
    // m_interactorStyle->setRenderer(m_renderer);
    m_interactorStyle->setOwnerWidget(this);
    m_interactorStyle->setVTKRenderWindow(m_renderWindow);
    m_interactorStyle->setOcctPicker(m_shapePicker);
    m_interactorStyle->setSelectionMode(SM_None);

    m_interactor->SetInteractorStyle(m_interactorStyle);

    _fitView();
}

void CentralViewWidget::_coordSystemSelectable(bool isSelectable)
{
}

void CentralViewWidget::_initializeCoordSystem(bool hasPlanes)
{
}




void CentralViewWidget::_initializeAxis()
{
    // init MarkerAxis actor
    vtkSmartPointer<vtkAxesActor> axes_actor = vtkSmartPointer<vtkAxesActor>::New();
    axes_actor->SetPosition(0, 0, 0);
    axes_actor->SetTotalLength(2, 2, 2);
    axes_actor->SetShaftType(0);
    axes_actor->SetCylinderRadius(0.03);
    axes_actor->SetAxisLabels(1);
    axes_actor->SetTipType(0);
    axes_actor->SetXAxisLabelText("x");
    axes_actor->GetXAxisShaftProperty()->SetColor(1, 1, 1);
    axes_actor->GetYAxisTipProperty()->SetColor(1, 1, 1);

    // init marker Widget; set interactor to widget.
    m_markerWidget = vtkSmartPointer<vtkCameraOrientationWidget>::New();
    m_markerWidget->SetParentRenderer(m_renderer);
    m_markerWidget->AnimateOn();
    m_markerWidget->On();
}

// void CentralViewWidget::UpdateShapeToRenderer(const TopoDS_Shape& shape)
// {
//     //Standard_Integer ShapeID = m_document->getMaxShapeID();
//
//     
//     Handle(QOccVtkSelPipeline) pipeline = new QOccVtkSelPipeline(shape, ShapeID);
//     pipeline->AddToRenderer(m_renderer);
//
//     m_interactorStyle->addPipeline(pipeline, ShapeID);
//
//     _fitView();
// }

void CentralViewWidget::addShapeToRenderer(const TopoDS_Shape& shape)
{
    Standard_Integer ShapeID = m_document->getMaxShapeID();

    Handle(QOccVtkSelPipeline) pipeline = new QOccVtkSelPipeline(shape, ShapeID);
    pipeline->AddToRenderer(m_renderer);

    m_interactorStyle->addPipeline(pipeline, ShapeID);

    _fitView();
}


void CentralViewWidget::OnSetSelectionMode(IVtk_SelectionMode mode)
{
    if (mode == SM_None)
    {
        m_interactorStyle->clearCurrSelector();
    }
    else
    {
        m_interactorStyle->setCurrSelector(dynamic_cast<QOccGeoSelector*>(QObject::sender()));
    }
    m_interactorStyle->setSelectionMode(mode);
}

void CentralViewWidget::UpdateView()
{
    for( auto item: m_interactorStyle->getShapePipelinesMap())
    {
        item->RemoveFromRenderer(m_renderer);
    }
    // 删除map内容
    m_interactorStyle->getShapePipelinesMap().Clear();
    
    // 获取根标签
    TDF_Label shapeRootLabel = m_document->GetShapeRoot();
    Handle(XCAFDoc_ShapeTool) shapeTool = XCAFDoc_ShapeTool::Set(shapeRootLabel);
    
    
    // 创建一个迭代器来遍历产品结构
    TDF_ChildIterator iter(shapeRootLabel, Standard_True); // Standard_True 表示我们也想要遍历到子标签
    for (; iter.More(); iter.Next())
    {
        TopoDS_Shape shape;
        if (shapeTool->GetShape(iter.Value(), shape))
        {
            auto l1 = shape.Location();
            auto t = l1.Transformation();
            addShapeToRenderer(shape);
        }
    }

    _fitView();
}

void CentralViewWidget::_traverseShapesRender(const Handle(XCAFDoc_ShapeTool)& shapeTool, const TDF_Label& label)
{
}

void CentralViewWidget::_fitView()
{
    m_renderer->ResetCamera();
    m_renderWindow->Render();
}