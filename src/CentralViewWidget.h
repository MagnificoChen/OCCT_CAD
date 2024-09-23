#pragma once

#include <QMainWindow>
#include "QHBoxLayout"
#include "QVTKOpenGLNativeWidget.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include <IVtkDraw_Interactor.hxx>
#include "vtkInteractorStyle.h"
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <TDF_ChildIterator.hxx>

#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkAxesActor.h>
#include <vtkAnnotatedCubeActor.h>
#include <vtkCameraOrientationWidget.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkInteractorStyleTrackball.h>
#include <vtkColor.h>
#include <vtkCamera.h>
#include <vtkLight.h>
#include <vtkDataSetMapper.h>

#include "CentralViewWidget.h"
#include "GlobalDefines.h"
#include "IVtkTools_ShapeObject.hxx"
#include "IVtkTools_ShapeDataSource.hxx"
#include <IVtkOCC_ShapePickerAlgo.hxx>
#include <unordered_set>

#include "src/Render/QOccVtkInteractorStyle.h"

class QOccDocument;
class QOccVtkInteractorStyle;
class CentralViewWidget : public QWidget
{
    Q_OBJECT
    friend class QOccVtkInteractorStyle;

public:

    CentralViewWidget(QWidget* parent = nullptr);
    ~CentralViewWidget();

    void SetDocument(QOccDocument* doc);
    void _initializeAxis();

    /**
     * 
     * @param shape wrap TopoDS_Shape to SelPipeline, then add it to renderer and document.
     */
    void addShapeToRenderer(const TopoDS_Shape& shape);

    void _traverseShapesRender(const Handle(XCAFDoc_ShapeTool)& shapeTool, const TDF_Label& label);
    void _fitView();
   
    void _initInteractor();
    /**
     * 
     * @param isSelectable 坐标系是否可拾取
     */
    void _coordSystemSelectable(bool isSelectable);
    /**
     * 创建坐标系统，默认不可拾取。
     * @param hasPlanes 是否显示坐标系平面
     */
    void _initializeCoordSystem(bool hasPlanes);
signals:
    /**
     * signal for coordinate system selected
     * @param xyz x:1, y:2, z:3
     * @param isPlane true if plane selected. for example: (1,true) means selected a plane with normal X.
     */
    void planeSelected(int xyz, bool isPlane);

    void selectItemChanged();

public slots:
    void OnSetSelectionMode(IVtk_SelectionMode mode);
    void UpdateView();

    // Getters and setters
public:
    [[nodiscard]] vtkSmartPointer<QOccVtkInteractorStyle> getInteractorStyle() const
    {
        return m_interactorStyle;
    }

    [[nodiscard]] vtkSmartPointer<vtkRenderWindowInteractor> getInteractor() const
    {
        return m_interactor;
    }


private:
    //Data
    QOccDocument* m_document = nullptr;

    //Components

    // ! Container widget
    QPointer<QWidget> _widget;

    QVBoxLayout* m_layout;

    // ! The Qt widget containing a VTK viewport
    QPointer<QVTKOpenGLNativeWidget> m_vtkWidget;

    // ! The VTK renderer window
    vtkGenericOpenGLRenderWindow* m_renderWindow;

    vtkSmartPointer<vtkRenderer> m_renderer;

    vtkSmartPointer<vtkCameraOrientationWidget> m_markerWidget = nullptr;

    vtkSmartPointer<vtkCamera> m_camera;


    // ! The VTK render window interactor
    vtkSmartPointer<vtkRenderWindowInteractor> m_interactor;

    // ! Custom interactor style
    vtkSmartPointer<QOccVtkInteractorStyle> m_interactorStyle;

    // ! IVtk_ShapePicker from OCC VIS
    vtkSmartPointer<IVtkTools_ShapePicker> m_shapePicker;

    NCollection_DataMap<IVtk_IdType, IVtk_ShapeIdList*> _selectedSubShapeIdsMap;

    IVtk_SelectionMode _currentSelectionMode = SM_None;

};
