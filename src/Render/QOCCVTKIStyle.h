#pragma once
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkTools_ShapeObject.hxx>
#include <IVtkTools_ShapePicker.hxx>
#include <vtkInteractorStyleTrackballCamera.h>

#include <qdebug.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkRendererCollection.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkProperty.h>

#include <vtkOrientationMarkerWidget.h>
#include <vtkPropPicker.h>
#include <vtkAssemblyPath.h>


//Qt includes
#include <QAction>
#include <QPointer>

// VIS includes
#include <IVtkOCC_Shape.hxx>
#include <IVtkTools_DisplayModeFilter.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkTools_ShapeObject.hxx>
#include <IVtkTools_ShapePicker.hxx>
#include <IVtkTools_SubPolyDataFilter.hxx>

#include "src/CentralViewWidget.h"
#include "src/Dialog/Components/QOccGeoSelector.h"
#include "QOccVtkSelPipeline.h"

class QOCCVTKIStyle : public vtkInteractorStyleTrackballCamera
{
public:
    
    static QOCCVTKIStyle* New();
    vtkTypeMacro(QOCCVTKIStyle, vtkInteractorStyleTrackballCamera)

/**
 * @brief Destructor for QVTKInteractorStyle.
 * Cleans up any resources used by the instance.
 */
~QOCCVTKIStyle() override;;

protected:
    /**
     * @brief Constructor for QVTKInteractorStyle.
     * Initializes a new instance of the QVTKInteractorStyle class.
     */
    QOCCVTKIStyle();


    //Class functions
public:

    void createContextMenu();
    void setSelectionMode(IVtk_SelectionMode mode);

    ///！important Single Selection Algorithm.
    void OnSelection();
    void OnMultiSelection();
    void OnHover(Standard_Integer theX, Standard_Integer theY);
    void setVTKRenderWindow(vtkRenderWindow* vtkRenderWindow);
    void setRenderer(const vtkSmartPointer<vtkRenderer>& theRenderer);
    void setOcctPicker(const vtkSmartPointer<IVtkTools_ShapePicker>& thePicker);

    void ClearHiliAndSel();

    void setOwnerWidget(CentralViewWidget* widget);
    void setCurrSelector(QOccGeoSelector* selector);
    void clearCurrSelector();
    void clearShapeMaps();
    /**
    * @brief Adds a selection pipeline to the interactor style.
    * @param pipeline A handle to the QIVtkSelectionPipeline.
    * @param id The ID associated with the pipeline.
    */
    void addPipeline(const Handle(QOccVtkSelPipeline)& pipeline);

    //Override functions
public:
    /**
     * @brief  Handle the right mouse button press event.
     */
    virtual void OnRightButtonDown() override;

    /**
     * @brief  Handle the left mouse button press event.
     */
    virtual void OnLeftButtonDown() override;

    /**
    * @brief  Handle the left mouse button up event.
    */
    virtual void OnLeftButtonUp() override;

    /**
     * @brief  Method for handling mouse moving event.
     */
    virtual void OnMouseMove() override;

    /**
     * @brief Handles the key press event.
     */
    virtual void OnKeyPress() override;

    /**
     * @brief Handles the key release event.
     */
    virtual void OnKeyRelease() override;

    /**
     * @brief Handles the original left button down event.
     */
    virtual void OnMiddleButtonDown() override;
    /**
     * @brief Handles the original left button up event.
     */
    virtual void OnMiddleButtonUp() override;


public:
    /*
     *functions to set multiPickers.
     */


private:
    vtkActor* LastPickedActor = nullptr;
    vtkSmartPointer<vtkActor> edgesActor;
    vtkSmartPointer<vtkProperty> LastPickedProperty = vtkProperty::New();

private:
    bool _occtPickerEnabled = false;

private:
    // ! Pointer to the context menu
    QPointer<QMenu> _contextMenu;
    // ! Pointer to the "Fit View" action.
    QPointer<QAction> _fitViewAction;
    // ! Pointer to the "Add Sizing" action.
    QPointer<QAction> _addSizingAction;

    
public:
    // ! Getter and Setters
    [[nodiscard]] vtkSmartPointer<vtkRenderer> getRenderer() const
    {
        return _renderer;
    }

    [[nodiscard]] vtkSmartPointer<IVtkTools_ShapePicker> getOcctPicker() const
    {
        return _occtpicker;
    }


//    [[nodiscard]] NCollection_DataMap<IVtk_IdType, Handle(QOccVtkSelPipeline)> getShapePipelinesMap() const
//    {
//        return _shapePipelinesMap;
//    }
    [[nodiscard]] std::vector<Handle(QOccVtkSelPipeline)> getPipelines() const
    {
        return _pipelines;
    }

private:
    // 和单选有关的变量
    TopoDS_Shape _curSelectedShape;
    NCollection_DataMap<IVtk_IdType, IVtk_ShapeIdList*> _selectedSingleShapeSubIdMap;
    IVtk_IdType _curSelectedSubShapeID;
    IVtk_IdType _curHoveredSubShapeID;

private:
    // ! Smart pointer to the shape picker.
    vtkSmartPointer<IVtkTools_ShapePicker> _occtpicker;
    // ! Smart pointer to the VTK renderer.
    vtkSmartPointer<vtkRenderer> _renderer;

    // ! Pointer to the QVTK render window.
    vtkRenderWindow* _qvtkRenderWindow = nullptr;

    int lastPos[2]{0, 0};

    // ! Current selection mode.
    IVtk_SelectionMode _currentSelectionMode = SM_None;

    //存储要渲染的pipelines
//    NCollection_DataMap<IVtk_IdType, Handle(QOccVtkSelPipeline)> _shapePipelinesMap;


    std::vector<Handle(QOccVtkSelPipeline)> _pipelines;


    //存储当前的Selector，将选中的几何存入当前Selector中
    QOccGeoSelector* m_currSelector = nullptr;

    CentralViewWidget* ownerWidget = nullptr;
};
