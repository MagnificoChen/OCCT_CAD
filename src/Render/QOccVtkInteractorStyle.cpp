#include "QOccVtkInteractorStyle.h"
#include <QMessageBox>
#include <QMenu>

#include "src/CentralViewWidget.h"
#include "QOccVtkSelPipeline.h"

#include "TopoDS_Edge.hxx"
#include "TopoDS.hxx"



// macro: a vtkNew method to all member functions
vtkStandardNewMacro(QOccVtkInteractorStyle)


QOccVtkInteractorStyle::QOccVtkInteractorStyle() {
    LastPickedActor = nullptr;
    LastPickedProperty->Delete();
}


///
/// \param pipelinesMap 清除 ID-Pipeline Map 中的数据
/// \param doHighlighting 清除触碰高亮
/// \param doSelection 清除选择高亮
static void ClearHighlightAndSelection(NCollection_DataMap<IVtk_IdType, Handle(QOccVtkSelPipeline) > pipelinesMap,
                                       const Standard_Boolean doHighlighting,
                                       const Standard_Boolean doSelection) {
    if (!doHighlighting && !doSelection) {
        return;
    }

    NCollection_DataMap<IVtk_IdType, Handle(QOccVtkSelPipeline) >::Iterator pIt(pipelinesMap);
    for (; pIt.More(); pIt.Next()) {
        const Handle(QOccVtkSelPipeline) &pipeline = pIt.Value();

        if (doHighlighting) {
            pipeline->ClearHighlightFilters();
        }

        if (doSelection) {
            pipeline->ClearSelectionFilters();
        }
    }
}

QOccVtkInteractorStyle::~QOccVtkInteractorStyle() {
}

void QOccVtkInteractorStyle::setOwnerWidget(CentralViewWidget* widget) {
    ownerWidget = widget;
}

void QOccVtkInteractorStyle::setCurrSelector(QOccGeoSelector* selector) {
    m_currSelector = selector;
}

void QOccVtkInteractorStyle::clearCurrSelector() {
    m_currSelector = nullptr;
}

//----------------------------------------------------------------------------
void QOccVtkInteractorStyle::addPipeline(
        const Handle(QOccVtkSelPipeline) pipeline, IVtk_IdType shapeID) {
    _shapePipelinesMap.Bind(shapeID, pipeline);
    _selectedSubShapeIdsMap.Bind(shapeID, new IVtk_ShapeIdList());
}


void QOccVtkInteractorStyle::setSelectionMode(IVtk_SelectionMode mode) {
    if (_shapePipelinesMap.IsEmpty())
        return;

    // 清空已选择的shape
    NCollection_DataMap<IVtk_IdType, IVtk_ShapeIdList*>::Iterator sIt(_selectedSubShapeIdsMap);
    for (; sIt.More(); sIt.Next()) {
        IVtk_ShapeIdList* selectedSubShapeIds = sIt.Value();
        selectedSubShapeIds->Clear();
    }

    ClearHighlightAndSelection(
            _shapePipelinesMap, Standard_True, Standard_True);

    //清空所有的选择模式
    NCollection_DataMap<IVtk_IdType, Handle(QOccVtkSelPipeline) >::Iterator pIt(_shapePipelinesMap);
    for (; pIt.More(); pIt.Next()) {
        const Handle(QOccVtkSelPipeline) &pipeline = pIt.Value();

        // Deactivate all current selection modes
        IVtk_SelectionModeList modeList
                = _occtpicker->GetSelectionModes(pipeline->Actor());

        for (IVtk_SelectionMode selMode: modeList) {
            _occtpicker->SetSelectionMode(selMode, false);
        }
    }
    // Set given selection mode
    if (mode == SM_None) {
        _occtpicker->SetSelectionMode(mode, false);
        _occtPickerEnabled = false;
    } else {
        _occtpicker->SetSelectionMode(mode, true);
        _occtPickerEnabled = true;

    }
    _currentSelectionMode = mode;
}

void QOccVtkInteractorStyle::OnSelection(const Standard_Boolean appendId) {
    vtkSmartPointer<vtkActorCollection> anActorCollection
            = _occtpicker->GetPickedActors();

    if (anActorCollection) {
        auto res = anActorCollection->GetNumberOfItems();
        if (anActorCollection->GetNumberOfItems() != 0) {
            // Clear previous selection.
            ClearHighlightAndSelection(
                    _shapePipelinesMap, Standard_False, Standard_True);
        }

        anActorCollection->InitTraversal();
        while (vtkActor* anActor = anActorCollection->GetNextActor()) {
            IVtkTools_ShapeDataSource* aDataSource
                    = IVtkTools_ShapeObject::GetShapeSource(anActor);
            if (!aDataSource) {
                continue;
            }

            IVtkOCC_Shape::Handle anOccShape = aDataSource->GetShape();

            if (anOccShape.IsNull()) {
                continue;
            }

            IVtk_IdType aShapeID = anOccShape->GetId();

            Handle(Message_Messenger) anOutput = Message::DefaultMessenger();

            if (!_shapePipelinesMap.IsBound(aShapeID)) {
                anOutput->SendWarning()
                        << "Warning: there is no VTK pipeline registered for picked shape"
                        << std::endl;
                continue;
            }

            const Handle(QOccVtkSelPipeline) &pipeline = _shapePipelinesMap.Find(aShapeID);
            IVtk_ShapeIdList* selectedSubShapeIds = _selectedSubShapeIdsMap.Find(aShapeID);
            if (m_currSelector) {
                m_currSelector->SetTag(pipeline->GetShapeID());
            }


            IVtkTools_SubPolyDataFilter* aFilter = pipeline->GetSelectionFilter();

            // Set the selected sub-shapes ids to subpolydata filter.
            IVtk_ShapeIdList aSubShapeIds;
            if (_currentSelectionMode == IVtk_SelectionMode::SM_Shape) {
                aSubShapeIds = _occtpicker->GetPickedShapesIds(Standard_False);
            } else {
                aSubShapeIds = _occtpicker->GetPickedSubShapesIds(aShapeID);
            }

            if (!appendId) {
                if (m_currSelector) {
                    m_currSelector->clearSelectedShape();
                }
                _selectedShapes.clear();
                selectedSubShapeIds->Clear();
            }

            for (auto shapeID: aSubShapeIds) {
                if (!selectedSubShapeIds->Contains(shapeID)) {
                    // If selected Ids list does not contain shape then append it.
                    selectedSubShapeIds->Append(aSubShapeIds);
                    if (m_currSelector) {
                        auto aSubShape = anOccShape->GetSubShape(shapeID);

                        auto result = m_currSelector->addSelectedShape(aSubShape);
                        if (!result) return;
                    }
                } else {
                    // Selecting the shape again causes deselecting it.
                    selectedSubShapeIds->Remove(shapeID);
                    if(m_currSelector){
                        const TopoDS_Shape &aSubShape = anOccShape->GetSubShape(shapeID);
                        auto result = m_currSelector->deleteSelectedShape(aSubShape);
                        if (!result) return;
                    }
                }
            }

            // If selected Ids list is empty then any selection will not be made
            if (selectedSubShapeIds->IsEmpty()) {
                if(_currentSelectionMode == SM_Solid){
                    if (m_currSelector) {
                        auto aShape = anOccShape->GetShape();
                        auto result = m_currSelector->addSelectedShape(aShape);
                        if (!result) return;
                    }
                }
                else{
                    return;
                }
            }

            // Get ids of cells for picked subshapes
            IVtk_ShapeIdList aSubIds;
            IVtk_ShapeIdList::Iterator aMetaIds(*selectedSubShapeIds);
            _selectedShapes.clear();
            for (; aMetaIds.More(); aMetaIds.Next()) {
                IVtk_ShapeIdList aSubSubIds = anOccShape->GetSubIds(aMetaIds.Value());
                const TopoDS_Shape &aSubShape = anOccShape->GetSubShape(aMetaIds.Value());
                _selectedShapes.push_back(aSubShape);
                aSubIds.Append(aSubSubIds);
            }

            aFilter->SetDoFiltering(!aSubIds.IsEmpty());
            aFilter->SetData(aSubIds);
            if (!aFilter->GetInput()) {
                aFilter->SetInputConnection(aDataSource->GetOutputPort());
            }
            aFilter->Modified();

            if (!pipeline.IsNull())
                pipeline->Mapper()->Update();
        }
    }
}

void QOccVtkInteractorStyle::MoveTo(Standard_Integer theX, Standard_Integer theY) {
    if (!_occtPickerEnabled) return;

    _occtpicker->Pick(theX, theY, 0, getRenderer());

    // Traversing results
    vtkSmartPointer<vtkActorCollection> anActorCollection = _occtpicker->GetPickedActors();

    if (anActorCollection) {
        // Highlight picked subshapes
        if (_shapePipelinesMap.IsEmpty())
            return;

        ClearHighlightAndSelection(_shapePipelinesMap, Standard_True, Standard_False);

        anActorCollection->InitTraversal();

        while (vtkActor* anActor = anActorCollection->GetNextActor()) {
            IVtkTools_ShapeDataSource* aDataSource = IVtkTools_ShapeObject::GetShapeSource(anActor);
            if (!aDataSource) {
                continue;
            }

            IVtkOCC_Shape::Handle anOccShape = aDataSource->GetShape();
            if (anOccShape.IsNull()) {
                continue;
            }

            IVtk_IdType aShapeID = anOccShape->GetId();

            Handle(Message_Messenger) anOutput = Message::DefaultMessenger();
            if (!_shapePipelinesMap.IsBound(aShapeID)) {
                anOutput->SendWarning()
                        << "Warning: there is no VTK pipeline registered for picked shape"
                        << std::endl;
                continue;
            }

            const Handle(QOccVtkSelPipeline) &pipeline
                    = _shapePipelinesMap.Find(aShapeID);
            IVtk_ShapeIdList* selectedSubShapeIds
                    = _selectedSubShapeIdsMap.Find(aShapeID);

            IVtkTools_SubPolyDataFilter* aFilter = pipeline->GetHighlightFilter();

            // Set the selected sub-shapes ids to subpolydata filter.
            IVtk_ShapeIdList aSubShapeIds = _occtpicker->GetPickedSubShapesIds(aShapeID);

            // If picked shape is in selected shapes then do not highlight it
            for (auto shapeID: aSubShapeIds) {
                if (selectedSubShapeIds->Contains(shapeID)) {
                    return;
                }
            }

            // Get ids of cells for picked subshapes.
            IVtk_ShapeIdList aSubIds;
            IVtk_ShapeIdList::Iterator aMetaIds(aSubShapeIds);
            for (; aMetaIds.More(); aMetaIds.Next()) {
                IVtk_ShapeIdList aSubSubIds = anOccShape->GetSubIds(aMetaIds.Value());
                aSubIds.Append(aSubSubIds);
                // const TopoDS_Shape& aSubShape = anOccShape->GetSubShape(aMetaIds.Value());
                // cout << "--------------------------------------------------------------" << endl;
                // cout << "Sub-shape ID: " << aMetaIds.Value() << endl;
                // cout << "Sub-shape type: " << aSubShape.TShape()->DynamicType()->Name() << endl;
            }
            aFilter->SetDoFiltering(!aSubIds.IsEmpty());
            aFilter->SetData(aSubIds);
            if (!aFilter->GetInput()) {
                aFilter->SetInputConnection(aDataSource->GetOutputPort());
            }
            aFilter->Modified();

            pipeline->Mapper()->Update();
        }
    }
}

//----------------------------------------------------------------------------
void QOccVtkInteractorStyle::setVTKRenderWindow(
        vtkRenderWindow* vtkRenderWindow) {
    _qvtkRenderWindow = vtkRenderWindow;
}

void QOccVtkInteractorStyle::setRenderer(
        const vtkSmartPointer<vtkRenderer> &theRenderer) {
    _renderer = theRenderer;
}

void QOccVtkInteractorStyle::setOcctPicker(
        const vtkSmartPointer<IVtkTools_ShapePicker> &thePicker) {
    _occtpicker = thePicker;
}

void QOccVtkInteractorStyle::createContextMenu() {
    if (!_contextMenu) {
        _contextMenu = new QMenu;

        // Set font size
        QFont font;
        font.setPointSize(10);
        _contextMenu->setFont(font);

        _fitViewAction = new QAction("Fit view", _contextMenu);
        QObject::connect(_fitViewAction, &QAction::triggered,
                         [this]() {
                             // _renderWindow->FitView();
                         });

        _addSizingAction = new QAction("Add sizing", _contextMenu);
        // QObject::connect(_addSizingAction, &QAction::triggered,
        //                  [this]()
        //                  {
        //                      _renderWindow->model->addSizing(this->_selectedShapes);
        //                  });

        _contextMenu->addAction(_fitViewAction);
        _contextMenu->addAction(_addSizingAction);
    }
}

void QOccVtkInteractorStyle::OnRightButtonDown() {
    this->createContextMenu();
    _contextMenu->exec(QCursor::pos());

    vtkInteractorStyleTrackballCamera::OnRightButtonDown();
}

void QOccVtkInteractorStyle::OnLeftButtonDown() {
    lastPos[0] = this->GetInteractor()->GetEventPosition()[0];
    lastPos[1] = this->GetInteractor()->GetEventPosition()[1];


    // Invoke base class event
    //vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}


void QOccVtkInteractorStyle::OnLeftButtonUp() {
    qDebug() << "Picking...";
    int* clickPos = this->GetInteractor()->GetEventPosition();


    //if mouse moved, is a DragEvent.
    if (clickPos[0] == lastPos[0] && clickPos[1] == lastPos[1]) {
        if (this->Interactor->GetShiftKey()) {
            // Append new selection to the current one
            this->OnSelection(Standard_True);
        } else {
            // Clear previous selection
            this->OnSelection(Standard_False);
        }
    }
    _qvtkRenderWindow->Render();
}

void QOccVtkInteractorStyle::OnMouseMove() {
    Standard_Integer aPos[2] = {
            this->Interactor->GetEventPosition()[0],
            this->Interactor->GetEventPosition()[1]
    };
    this->MoveTo(aPos[0], aPos[1]);
    vtkInteractorStyleTrackballCamera::OnMouseMove();
}

void QOccVtkInteractorStyle::OnKeyPress() {
    vtkInteractorStyleTrackballCamera::OnKeyPress();
}

void QOccVtkInteractorStyle::OnKeyRelease() {
    vtkInteractorStyleTrackballCamera::OnKeyRelease();
}

void QOccVtkInteractorStyle::OnMiddleButtonDown() {
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void QOccVtkInteractorStyle::OnMiddleButtonUp() {
    vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

void QOccVtkInteractorStyle::clearShapeMaps() {
    _shapePipelinesMap.Clear();
    _selectedSubShapeIdsMap.Clear();
}

