#pragma once
#include <vtkArrowSource.h>
#include <vtkObject.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkVector.h>
#include <vtkAssembly.h>


class vtkSelectableCoordinate :
    public vtkObject
{
public:
    vtkTypeMacro(vtkSelectableCoordinate, vtkObject);
    static vtkSelectableCoordinate* New();

    vtkSelectableCoordinate();
    void SetRenderer(vtkSmartPointer<vtkRenderer> renderer);
    void AddToRenderer();
    virtual ~vtkSelectableCoordinate();

    /**
     * 
     * @param isSelectable set selectable
     * @param AxisOrPlane 0:Axis, 1:Plane 2:All
     */
    void SetSelectable(bool isSelectable, int AxisOrPlane);

private:
    vtkSmartPointer<vtkRenderer> m_renderer;

    vtkSmartPointer<vtkAssembly> m_coordAsm;

    vtkSmartPointer<vtkActor> arrowActorX;
    vtkSmartPointer<vtkActor> arrowActorY;
    vtkSmartPointer<vtkActor> arrowActorZ;
    vtkSmartPointer<vtkActor> planeActorX;
    vtkSmartPointer<vtkActor> planeActorY;
    vtkSmartPointer<vtkActor> planeActorZ;

    vtkVector3d position{0, 0, 0};
};

