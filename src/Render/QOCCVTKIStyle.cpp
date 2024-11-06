#include "QOCCVTKIStyle.h"
#include <QMessageBox>
#include <QMenu>

#include "src/CentralViewWidget.h"
#include "QOccVtkSelPipeline.h"
#include "vtkCollectionIterator.h"

#include "TopoDS_Edge.hxx"
#include "TopoDS.hxx"

#include "map"


// macro: a vtkNew method to all member functions
vtkStandardNewMacro(QOCCVTKIStyle)


QOCCVTKIStyle::QOCCVTKIStyle() {
    LastPickedActor = nullptr;
    LastPickedProperty->Delete();
}

QOCCVTKIStyle::~QOCCVTKIStyle() {
}

///
/// \param pipelinesMap 清除 ID-Pipeline Map 中的数据
/// \param doHighlighting 清除触碰高亮
/// \param doSelection 清除选择高亮
static void ClearHighlightAndSelection(const std::vector<Handle(QOccVtkSelPipeline) > &pipelines,
                                       const Standard_Boolean doHighlighting,
                                       const Standard_Boolean doSelection) {
    if (!doHighlighting && !doSelection) {
        return;
    }

    for (const auto &pipeline: pipelines) {
        if (doHighlighting) {
            pipeline->ClearHighlightFilters();
        }

        if (doSelection) {
            pipeline->ClearSelectionFilters();
        }
    }
}

void QOCCVTKIStyle::ClearHiliAndSel() {
    ClearHighlightAndSelection(_pipelines,Standard_True,Standard_True);
}

void QOCCVTKIStyle::setOwnerWidget(CentralViewWidget* widget) {
    ownerWidget = widget;
}

void QOCCVTKIStyle::setCurrSelector(QOccGeoSelector* selector) {
    m_currSelector = selector;
}

void QOCCVTKIStyle::clearCurrSelector() {
    m_currSelector = nullptr;
}

//----------------------------------------------------------------------------
void QOCCVTKIStyle::addPipeline(
    const Handle(QOccVtkSelPipeline) &pipeline) {
    _pipelines.push_back(pipeline);
}


void QOCCVTKIStyle::setSelectionMode(IVtk_SelectionMode mode) {
    if (_pipelines.empty())
        return;

    // 清空已选择的shape
    //    NCollection_DataMap<IVtk_IdType, IVtk_ShapeIdList*>::Iterator sIt(_selectedSubShapeIdsMap);
    //    for (; sIt.More(); sIt.Next()) {
    //        IVtk_ShapeIdList* selectedSubShapeIds = sIt.Value();
    //        selectedSubShapeIds->Clear();
    //    }
    //    curSelectedSubShapeIds->Clear();

    //清除高亮
    ClearHighlightAndSelection(_pipelines, Standard_True, Standard_True);

    //清空所有的选择模式
    for (const auto &pipeline: _pipelines) {
        // Deactivate all current selection modes
        IVtk_SelectionModeList modeList = _occtpicker->GetSelectionModes(pipeline->Actor());

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

// void QOCCVTKIStyle::OnSelection() {
//     //获取选中的VTK对象，有选中
//     if (const vtkSmartPointer<vtkActorCollection> pickedActors = _occtpicker->GetPickedActors()) {
//         if (pickedActors->GetNumberOfItems() != 0) {
//             // 清理选择高亮
//             ClearHighlightAndSelection(_pipelines, Standard_False, Standard_True);
//         }
//
//         //遍历所有选中的VTK对象
//         pickedActors->InitTraversal();
//         while (vtkActor* anActor = pickedActors->GetNextActor()) {
//             //获取DataSource
//             IVtkTools_ShapeDataSource* aDataSource = IVtkTools_ShapeObject::GetShapeSource(anActor);
//             if (!aDataSource) continue;
//
//             IVtkOCC_Shape::Handle anOccShape = aDataSource->GetShape();
//
//             if (anOccShape.IsNull()) continue;
//
//             //获取ShapeID
//             IVtk_IdType aShapeID = anOccShape->GetId();
//             //此段用于存储fullShape，但一般来说，Selector不允许设置SelectMode为SM_Shape。
//             {
//                 _curSelectedShape = anOccShape->GetShape();
//                 if (m_currSelector) {
//                     m_currSelector->setFullShape(_curSelectedShape);
//                 }
//             }
//
//             Handle(Message_Messenger) anOutput = Message::DefaultMessenger();
//
//             auto it = std::find_if(_pipelines.begin(), _pipelines.end(),
//                                    [&](Handle(QOccVtkSelPipeline) &handle)-> bool {
//                                        return handle->getShape() == anOccShape->GetShape();
//                                    });
// #ifndef _DEBUG
//             if (it == _pipelines.end()) {
//                 anOutput->SendWarning()
//                         << "Warning: there is no VTK pipeline registered for picked shape"
//                         << std::endl;
//                 continue;
//             }
// #endif
//
//             //一般来说，pipeline不会无法找到。
//             const Handle(QOccVtkSelPipeline) pipeline = *it;
//             IVtk_ShapeIdList* selectedSubShapeIds = new IVtk_ShapeIdList;
//             if (m_currSelector) {
//                 m_currSelector->SetTag(pipeline->GetTag());
//             }
//
//
//             // Set the selected sub-shapes ids to subPolyData filter.
//             IVtk_ShapeIdList pickedSubShapeIDs;
//             pickedSubShapeIDs = _occtpicker->GetPickedSubShapesIds(aShapeID);
//
//             //清空所有的
//             if (m_currSelector) {
//                 m_currSelector->clearSelectedShape();
//             }
//
//             //获取pipeline的Filter
//             IVtkTools_SubPolyDataFilter* aFilter = pipeline->GetSelectionFilter();
//             IVtk_ShapeIdList aSubIds;
//             //不需要选取子项目，直接添加shape
//             if (pickedSubShapeIDs.IsEmpty()) {
//                 if (aShapeID == _curSelectedSubShapeID) {
//                     //取消选中
//                     _curSelectedSubShapeID = LLONG_MIN;
//                     auto shape = anOccShape->GetShape();
//                     auto result = m_currSelector->deleteSelectedShape(shape);
//                 } else {
//                     //选中当前
//                     _curSelectedSubShapeID = aShapeID;
//                     auto shape = anOccShape->GetShape();
//                     auto result = m_currSelector->addSelectedShape(shape);
//                     aSubIds.Append(_curHoveredSubShapeID);
//                 }
//
//             } else {
//                 for (auto shapeID: pickedSubShapeIDs) {
//                     if (shapeID == _curSelectedSubShapeID) {
//                         //如果不是
//                         _curSelectedSubShapeID = LLONG_MIN;
//                         auto aSubShape = anOccShape->GetSubShape(shapeID);
//                         auto result = m_currSelector->deleteSelectedShape(aSubShape);
//                     } else {
//                         //如果不是
//                         _curSelectedSubShapeID = shapeID;
//                         auto aSubShape = anOccShape->GetSubShape(shapeID);
//                         auto result = m_currSelector->addSelectedShape(aSubShape);
//                     }
//                 }
//
//                 if (_curSelectedSubShapeID == LLONG_MIN) {
//                     continue;
//                 }
//                 IVtk_ShapeIdList aSubSubIds = anOccShape->GetSubIds(_curSelectedSubShapeID);
//                 const TopoDS_Shape &aSubShape = anOccShape->GetSubShape(_curSelectedSubShapeID);
//                 aSubIds.Append(aSubSubIds);
//             }
//             aFilter->SetDoFiltering(!aSubIds.IsEmpty());
//             aFilter->SetData(aSubIds);
//
//             if (!aFilter->GetInput()) {
//                 aFilter->SetInputConnection(aDataSource->GetOutputPort());
//             }
//             aFilter->Modified();
//
//             if (!pipeline.IsNull())
//                 pipeline->Mapper()->Update();
//         }
//     }
// }


void QOCCVTKIStyle::OnSelection() {
    // 获取选中的VTK对象
    if (const vtkSmartPointer<vtkActorCollection> pickedActors = _occtpicker->GetPickedActors()) {
        if (pickedActors->GetNumberOfItems() != 0) {
            // 清理选择高亮
            ClearHighlightAndSelection(_pipelines, Standard_False, Standard_True);
        }

        // 遍历所有选中的VTK对象
        pickedActors->InitTraversal();
        while (vtkActor* anActor = pickedActors->GetNextActor()) {
            // 获取DataSource
            IVtkTools_ShapeDataSource* aDataSource = IVtkTools_ShapeObject::GetShapeSource(anActor);
            if (!aDataSource) continue;

            IVtkOCC_Shape::Handle anOccShape = aDataSource->GetShape();
            if (anOccShape.IsNull()) continue;

            // 获取ShapeID
            IVtk_IdType aShapeID = anOccShape->GetId();

            // 存储fullShape
            _curSelectedShape = anOccShape->GetShape();
            if (m_currSelector) {
                m_currSelector->setFullShape(_curSelectedShape);
            }

            Handle(Message_Messenger) anOutput = Message::DefaultMessenger();

            // 查找对应的pipeline
            auto it = std::ranges::find_if(_pipelines,
                                           [&](Handle(QOccVtkSelPipeline) &handle) -> bool {
                                               return handle->getShape() == anOccShape->GetShape();
                                           });

#ifndef _DEBUG
            if (it == _pipelines.end()) {
                anOutput->SendWarning()
                        << "Warning: there is no VTK pipeline registered for picked shape"
                        << std::endl;
                continue;
            }
#endif

            // 一般来说，pipeline不会无法找到
            const Handle(QOccVtkSelPipeline) pipeline = *it;
            IVtk_ShapeIdList* selectedSubShapeIds = new IVtk_ShapeIdList;
            if (m_currSelector) {
                m_currSelector->SetTag(pipeline->GetTag());
            }

            // 获取选中的子形状ID
            IVtk_ShapeIdList pickedSubShapeIDs = _occtpicker->GetPickedSubShapesIds(aShapeID);

            // 清空所有选中的形状
            if (m_currSelector) {
                m_currSelector->clearSelectedShape();
            }

            // 获取pipeline的Filter
            IVtkTools_SubPolyDataFilter* aFilter = pipeline->GetSelectionFilter();

            IVtk_ShapeIdList aSubIds;

            // 处理选中的子形状
            if (pickedSubShapeIDs.IsEmpty()) {
                if (aShapeID == _curSelectedSubShapeID) {
                    // 取消选中
                    _curSelectedSubShapeID = LLONG_MIN;
                    auto shape = anOccShape->GetShape();
                    m_currSelector->deleteSelectedShape(shape);
                    aSubIds.Append(_curHoveredSubShapeID);

                } else {
                    // 选中当前
                    _curSelectedSubShapeID = aShapeID;
                    auto shape = anOccShape->GetShape();
                    m_currSelector->addSelectedShape(shape);
                }
            } else {
                for (auto shapeID : pickedSubShapeIDs) {
                    if (shapeID == _curSelectedSubShapeID) {
                        // 取消选中
                        _curSelectedSubShapeID = LLONG_MIN;
                        auto aSubShape = anOccShape->GetSubShape(shapeID);
                        m_currSelector->deleteSelectedShape(aSubShape);
                    } else {
                        // 选中当前
                        _curSelectedSubShapeID = shapeID;
                        auto aSubShape = anOccShape->GetSubShape(shapeID);
                        m_currSelector->addSelectedShape(aSubShape);
                    }
                }

                if (_curSelectedSubShapeID != LLONG_MIN) {
                    IVtk_ShapeIdList aSubSubIds = anOccShape->GetSubIds(_curSelectedSubShapeID);
                    const TopoDS_Shape &aSubShape = anOccShape->GetSubShape(_curSelectedSubShapeID);
                    aSubIds.Append(aSubSubIds);
                }
            }

            aFilter->SetDoFiltering(!aSubIds.IsEmpty());
            aFilter->SetData(aSubIds);

            if (!aFilter->GetInput()) {
                aFilter->SetInputConnection(aDataSource->GetOutputPort());
            }
            aFilter->Modified();

            if (!pipeline.IsNull()) {
                pipeline->Mapper()->Update();
            }

            // 释放动态分配的资源
            delete selectedSubShapeIds;
        }
    }
}


void QOCCVTKIStyle::OnMultiSelection() {
    //     //获取选中的VTK对象，有选中
    //     if (const vtkSmartPointer<vtkActorCollection> pickedActors = _occtpicker->GetPickedActors()) {
    //         if (pickedActors->GetNumberOfItems() != 0) {
    //             // 清理选择高亮
    //             ClearHighlightAndSelection(_pipelines, Standard_False, Standard_True);
    //         }
    //
    //         //遍历所有选中的VTK对象
    //         pickedActors->InitTraversal();
    //         while (vtkActor* anActor = pickedActors->GetNextActor()) {
    //             //获取DataSource
    //             IVtkTools_ShapeDataSource* aDataSource = IVtkTools_ShapeObject::GetShapeSource(anActor);
    //             if (!aDataSource) continue;
    //
    //             IVtkOCC_Shape::Handle anOccShape = aDataSource->GetShape();
    //
    //             if (anOccShape.IsNull()) continue;
    //
    //             //获取ShapeID
    //             IVtk_IdType aShapeID = anOccShape->GetId();
    //             //此段用于存储fullShape，但一般来说，Selector不允许设置SelectMode为SM_Shape。
    //             {
    //                 _curSelectedShape = anOccShape->GetShape();
    //                 if (m_currSelector) {
    //                     m_currSelector->setFullShape(_curSelectedShape);
    //                 }
    //             }
    //
    //             Handle(Message_Messenger) anOutput = Message::DefaultMessenger();
    //
    //             auto it = std::find_if(_pipelines.begin(), _pipelines.end(),
    //                                    [&](Handle(QOccVtkSelPipeline) &handle)-> bool {
    //                                        return handle->getShape() == anOccShape->GetShape();
    //                                    });
    // #ifndef _DEBUG
    //             if (it == _pipelines.end()) {
    //                 anOutput->SendWarning()
    //                         << "Warning: there is no VTK pipeline registered for picked shape"
    //                         << std::endl;
    //                 continue;
    //             }
    // #endif
    //
    //             //一般来说，pipeline不会无法找到。
    //             const Handle(QOccVtkSelPipeline) pipeline = *it;
    //             //            IVtk_ShapeIdList* selectedSubShapeIds = new IVtk_ShapeIdList ;
    //             if (m_currSelector) {
    //                 m_currSelector->SetTag(pipeline->GetTag());
    //             }
    //
    //
    //             IVtkTools_SubPolyDataFilter* aFilter = pipeline->GetSelectionFilter();
    //
    //             // Set the selected sub-shapes ids to subPolyData filter.
    //             IVtk_ShapeIdList pickedSubShapeIDs;
    //             pickedSubShapeIDs = _occtpicker->GetPickedSubShapesIds(aShapeID);
    //
    //             //清空所有的
    //             if (m_currSelector) {
    //                 m_currSelector->clearSelectedShape();
    //             }
    //
    //
    //             for (auto subShapeId: pickedSubShapeIDs) {
    //                 //                if (!_selectedSubShapeIdsMap->Contains(subShapeId)) {
    //                 // If selected Ids list does not contain shape then append it.
    //                 //                    _selectedSubShapeIdsMap->Append(aSubShapeIds);
    //                 if (m_currSelector) {
    //                     auto aSubShape = anOccShape->GetSubShape(subShapeId);
    //                     auto result = m_currSelector->addSelectedShape(aSubShape);
    //                     if (!result) return;
    //                 }
    //                 //                } else {
    //                 // Selecting the shape again causes deselecting it.
    //                 //                    curSelectedSubShapeIds->Remove(subShapeId);
    //                 if (m_currSelector) {
    //                     const TopoDS_Shape &aSubShape = anOccShape->GetSubShape(subShapeId);
    //                     auto result = m_currSelector->deleteSelectedShape(aSubShape);
    //                     if (!result) return;
    //                 }
    //                 //                }
    //             }
    //
    //             // If selected Ids list is empty then any selection will not be made
    //             //            if (curSelectedSubShapeIds->IsEmpty()) {
    //             if (_currentSelectionMode == SM_Solid) {
    //                 if (m_currSelector) {
    //                     auto aShape = anOccShape->GetShape();
    //                     auto result = m_currSelector->addSelectedShape(aShape);
    //                     if (!result) return;
    //                 }
    //             } else {
    //                 return;
    //             }
    //             //            }
    //
    //
    //             // Get ids of cells for picked subshapes
    //             // IVtk_ShapeIdList aSubIds;
    //             // IVtk_ShapeIdList::Iterator aMetaIds(*curSelectedSubShapeIds);
    //             // for (; aMetaIds.More(); aMetaIds.Next()) {
    //             //     IVtk_ShapeIdList aSubSubIds = anOccShape->GetSubIds(aMetaIds.Value());
    //             //     const TopoDS_Shape &aSubShape = anOccShape->GetSubShape(aMetaIds.Value());
    //             //     aSubIds.Append(aSubSubIds);
    //             // }
    //             //
    //             // aFilter->SetDoFiltering(!aSubIds.IsEmpty());
    //             // aFilter->SetData(aSubIds);
    //             // if (!aFilter->GetInput()) {
    //             //     aFilter->SetInputConnection(aDataSource->GetOutputPort());
    //             // }
    //             // aFilter->Modified();
    //             //
    //             // if (!pipeline.IsNull())
    //             //     pipeline->Mapper()->Update();
    //         }
    //     }
}


void QOCCVTKIStyle::OnHover(Standard_Integer theX, Standard_Integer theY) {
    if (!_occtPickerEnabled) return;

    _occtpicker->Pick(theX, theY, 0, getRenderer());

    // 获取选中的VTK对象
    if (vtkSmartPointer<vtkActorCollection> anActorCollection = _occtpicker->GetPickedActors()) {
        // 高亮选中的子形状
        if (_pipelines.empty()) return;

        // 清理高亮和选择
        ClearHighlightAndSelection(_pipelines, Standard_True, Standard_False);

        // 遍历所有选中的VTK对象
        anActorCollection->InitTraversal();
        while (vtkActor* anActor = anActorCollection->GetNextActor()) {
            // 获取DataSource
            IVtkTools_ShapeDataSource* aDataSource = IVtkTools_ShapeObject::GetShapeSource(anActor);
            if (!aDataSource) continue;

            IVtkOCC_Shape::Handle anOccShape = aDataSource->GetShape();
            if (anOccShape.IsNull()) continue;

            IVtk_IdType aShapeID = anOccShape->GetId();

            Handle(Message_Messenger) anOutput = Message::DefaultMessenger();

            // 查找对应的pipeline
            auto it = std::find_if(_pipelines.begin(), _pipelines.end(),
                                   [&](Handle(QOccVtkSelPipeline) &handle) -> bool {
                                       return handle->getShape() == anOccShape->GetShape();
                                   });

            if (it == _pipelines.end()) {
                anOutput->SendWarning()
                        << "Warning: there is no VTK pipeline registered for picked shape"
                        << std::endl;
                continue;
            }

            const Handle(QOccVtkSelPipeline) pipeline = *it;

            // 获取pipeline的高亮过滤器
            IVtkTools_SubPolyDataFilter* aFilter = pipeline->GetHighlightFilter();

            // 获取选中的子形状ID
            IVtk_ShapeIdList pickedSubShapeIds = _occtpicker->GetPickedSubShapesIds(aShapeID);
            IVtk_ShapeIdList aSubIds;

            // 处理选中的子形状
            if (pickedSubShapeIds.IsEmpty()) {
                _curHoveredSubShapeID = aShapeID;
                //aSubIds.Append(_curHoveredSubShapeID);
            } else {
                for (auto shapeID : pickedSubShapeIds) {
                    _curHoveredSubShapeID = shapeID;

                }
                // 获取选中的子形状的子ID
                IVtk_ShapeIdList aSubSubIds = anOccShape->GetSubIds(_curHoveredSubShapeID);
                const TopoDS_Shape &aSubShape = anOccShape->GetSubShape(_curHoveredSubShapeID);
                aSubIds.Append(aSubSubIds);
            }


            // 设置高亮过滤器的数据
            aFilter->SetDoFiltering(!aSubIds.IsEmpty());
            aFilter->SetData(aSubIds);
            if (!aFilter->GetInput()) {
                aFilter->SetInputConnection(aDataSource->GetOutputPort());
            }
            aFilter->Modified();

            // 更新pipeline的映射器
            if (!pipeline.IsNull()) {
                pipeline->Mapper()->Update();
            }
        }
    }
}

//----------------------------------------------------------------------------
void QOCCVTKIStyle::setVTKRenderWindow(
    vtkRenderWindow* vtkRenderWindow) {
    _qvtkRenderWindow = vtkRenderWindow;
}

void QOCCVTKIStyle::setRenderer(
    const vtkSmartPointer<vtkRenderer> &theRenderer) {
    _renderer = theRenderer;
}

void QOCCVTKIStyle::setOcctPicker(
    const vtkSmartPointer<IVtkTools_ShapePicker> &thePicker) {
    _occtpicker = thePicker;
}

void QOCCVTKIStyle::createContextMenu() {
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

void QOCCVTKIStyle::OnRightButtonDown() {
    this->createContextMenu();
    _contextMenu->exec(QCursor::pos());

    vtkInteractorStyleTrackballCamera::OnRightButtonDown();
}

void QOCCVTKIStyle::OnLeftButtonDown() {
    lastPos[0] = this->GetInteractor()->GetEventPosition()[0];
    lastPos[1] = this->GetInteractor()->GetEventPosition()[1];


    // Invoke base class event
    //vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}


void QOCCVTKIStyle::OnLeftButtonUp() {
    qDebug() << "Picking...";
    int* clickPos = this->GetInteractor()->GetEventPosition();


    //if mouse moved, is a DragEvent.
    if (clickPos[0] == lastPos[0] && clickPos[1] == lastPos[1]) {
        if (this->Interactor->GetShiftKey()) {
            // Append new selection to the current one
            // this->OnSelection(Standard_True);
        } else {
            // Clear previous selection
            this->OnSelection();
        }
    }
    _qvtkRenderWindow->Render();
}

void QOCCVTKIStyle::OnMouseMove() {
    Standard_Integer aPos[2] = {
        this->Interactor->GetEventPosition()[0],
        this->Interactor->GetEventPosition()[1]
    };
    this->OnHover(aPos[0], aPos[1]);
    vtkInteractorStyleTrackballCamera::OnMouseMove();
}

void QOCCVTKIStyle::OnKeyPress() {
    vtkInteractorStyleTrackballCamera::OnKeyPress();
}

void QOCCVTKIStyle::OnKeyRelease() {
    vtkInteractorStyleTrackballCamera::OnKeyRelease();
}

void QOCCVTKIStyle::OnMiddleButtonDown() {
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void QOCCVTKIStyle::OnMiddleButtonUp() {
    vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

void QOCCVTKIStyle::clearShapeMaps() {
    //    _shapePipelinesMap.Clear(true);
    //    _selectedSubShapeIdsMap.Clear(true);
}
