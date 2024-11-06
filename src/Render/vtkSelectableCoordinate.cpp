#include "vtkSelectableCoordinate.h"

#include <vtkNamedColors.h>
#include <vtkPlaneSource.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
// 宏的实现
vtkStandardNewMacro(vtkSelectableCoordinate);

vtkSelectableCoordinate::~vtkSelectableCoordinate()
{
}

void vtkSelectableCoordinate::SetSelectable(bool isSelectable, int AxisOrPlane)
{
    switch (AxisOrPlane)
    {
    case 0:
        {
            
            break;
        }
    case 1:
        {
            break;
        }
    case 2:
        {
            break;
        }
    default: break;
    }
}


vtkSelectableCoordinate::vtkSelectableCoordinate()
{
    // 创建三个箭头
    vtkSmartPointer<vtkArrowSource> arrowSourceX = vtkSmartPointer<vtkArrowSource>::New();
    arrowSourceX->SetArrowOriginToDefault();
    arrowSourceX->SetTipResolution(12);
    arrowSourceX->SetTipLength(0.1);
    arrowSourceX->SetTipRadius(0.03);
    arrowSourceX->SetShaftRadius(0.01);
    arrowSourceX->SetShaftResolution(12);
    arrowSourceX->Update();

    vtkSmartPointer<vtkPolyDataMapper> arrowMapperX = vtkSmartPointer<vtkPolyDataMapper>::New();
    arrowMapperX->SetInputConnection(arrowSourceX->GetOutputPort());

    arrowActorX = vtkSmartPointer<vtkActor>::New();
    arrowActorX->SetMapper(arrowMapperX);
    arrowActorX->GetProperty()->SetColor(1, 0, 0); // 红色

    vtkSmartPointer<vtkArrowSource> arrowSourceY = vtkSmartPointer<vtkArrowSource>::New();
    arrowSourceY->SetArrowOriginToDefault();
    arrowSourceY->SetTipResolution(12);
    arrowSourceY->SetTipLength(0.1);
    arrowSourceY->SetTipRadius(0.03);
    arrowSourceY->SetShaftRadius(0.01);
    arrowSourceY->SetShaftResolution(12);
    arrowSourceY->Update();

    vtkSmartPointer<vtkPolyDataMapper> arrowMapperY = vtkSmartPointer<vtkPolyDataMapper>::New();
    arrowMapperY->SetInputConnection(arrowSourceY->GetOutputPort());

    arrowActorY = vtkSmartPointer<vtkActor>::New();
    arrowActorY->SetMapper(arrowMapperY);
    arrowActorY->GetProperty()->SetColor(0, 1, 0); // 绿色

    vtkSmartPointer<vtkArrowSource> arrowSourceZ = vtkSmartPointer<vtkArrowSource>::New();
    arrowSourceZ->SetArrowOriginToDefault();
    arrowSourceZ->SetTipResolution(12);
    arrowSourceZ->SetTipLength(0.1);
    arrowSourceZ->SetTipRadius(0.03);
    arrowSourceZ->SetShaftRadius(0.01);
    arrowSourceZ->SetShaftResolution(12);
    arrowSourceZ->Update();

    vtkSmartPointer<vtkPolyDataMapper> arrowMapperZ = vtkSmartPointer<vtkPolyDataMapper>::New();
    arrowMapperZ->SetInputConnection(arrowSourceZ->GetOutputPort());

    arrowActorZ = vtkSmartPointer<vtkActor>::New();
    arrowActorZ->SetMapper(arrowMapperZ);
    arrowActorZ->GetProperty()->SetColor(0, 0, 1); // 蓝色

    // 创建一个表示平面的网格: YOZ方向
    vtkSmartPointer<vtkPlaneSource> planeSourceX = vtkSmartPointer<vtkPlaneSource>::New();
    planeSourceX->SetOrigin(0, 0, 0);
    planeSourceX->SetPoint1(0, 0, 0.5);
    planeSourceX->SetPoint2(0, 0.5, 0);
    planeSourceX->Update();

    vtkPolyData* planeDataX = planeSourceX->GetOutput();

    // Create a mapper and actor
    vtkNew<vtkPolyDataMapper> planeMapperX;
    planeMapperX->SetInputData(planeDataX);

    planeActorX = vtkSmartPointer<vtkActor>::New();
    planeActorX->SetMapper(planeMapperX);
    vtkNew<vtkNamedColors> colors;
    planeActorX->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
    planeActorX->GetProperty()->SetOpacity(0.2);

    // 创建一个表示平面的网格: XOZ方向
    vtkSmartPointer<vtkPlaneSource> planeSourceY = vtkSmartPointer<vtkPlaneSource>::New();
    planeSourceY->SetOrigin(0, 0, 0);
    planeSourceY->SetPoint1(0, 0, 0.5);
    planeSourceY->SetPoint2(0.5, 0, 0);
    planeSourceY->Update();

    vtkPolyData* planeDataY = planeSourceY->GetOutput();

    // Create a mapper and actor
    vtkNew<vtkPolyDataMapper> planeMapperY;
    planeMapperY->SetInputData(planeDataY);

    planeActorY = vtkSmartPointer<vtkActor>::New();
    planeActorY->SetMapper(planeMapperY);
    planeActorY->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
    planeActorY->GetProperty()->SetOpacity(0.2);

    // 创建一个表示平面的网格: XOY方向
    vtkSmartPointer<vtkPlaneSource> planeSourceZ = vtkSmartPointer<vtkPlaneSource>::New();
    planeSourceZ->SetOrigin(0, 0, 0);
    planeSourceZ->SetPoint1(0.5, 0, 0);
    planeSourceZ->SetPoint2(0, 0.5, 0);
    planeSourceZ->Update();

    vtkPolyData* planeDataZ = planeSourceZ->GetOutput();

    // Create a mapper and actor
    vtkNew<vtkPolyDataMapper> planeMapperZ;
    planeMapperZ->SetInputData(planeDataZ);

    planeActorZ = vtkSmartPointer<vtkActor>::New();
    planeActorZ->SetMapper(planeMapperZ);
    planeActorZ->GetProperty()->SetColor(colors->GetColor3d("Banana").GetData());
    planeActorZ->GetProperty()->SetOpacity(0.2);

    arrowActorX->SetOrientation(90, 0, 0);
    arrowActorX->SetPosition(0, 0, 0);
    arrowActorY->SetOrientation(0, 0, 90);
    arrowActorY->SetPosition(0, 0, 0);
    arrowActorZ->SetOrientation(0, -90, 0);
    arrowActorZ->SetPosition(0, 0, 0);

    m_coordAsm = vtkAssembly::New();
}

void vtkSelectableCoordinate::SetRenderer(vtkSmartPointer<vtkRenderer> renderer)
{
    m_renderer = renderer;
}

void vtkSelectableCoordinate::AddToRenderer()
{
    if (!m_renderer) return;
    m_coordAsm->AddPart(arrowActorX);
    m_coordAsm->AddPart(arrowActorY);
    m_coordAsm->AddPart(arrowActorZ);
    m_coordAsm->AddPart(planeActorX);
    m_coordAsm->AddPart(planeActorY);
    m_coordAsm->AddPart(planeActorZ);

    m_renderer->AddActor(m_coordAsm);
}
