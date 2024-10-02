#pragma once

#include <BinDrivers_DocumentRetrievalDriver.hxx>
#include <BinDrivers_DocumentStorageDriver.hxx>
#include <BinLDrivers.hxx>
#include "CentralViewWidget.h"
#include <QObject>
#include <TDataStd_Integer.hxx>
#include <TDF_Tool.hxx>
#include <TDocStd_Application.hxx>

#include "src/Render/QOccVtkSelPipeline.h"

class QOccDocument : public QObject
{
    Q_OBJECT

public:
    QOccDocument(QObject* parent = nullptr, Handle(TDocStd_Document) document = nullptr);
    QOccDocument() = delete;
    ~QOccDocument();

    /**
     * 
     * @return list of pipelines(handles) to be rendered.
     */
    NCollection_List<opencascade::handle<QOccVtkSelPipeline>> getPipelines();

    /**
     * 
     * @return Count of pipeline
     */
    Standard_Integer getPipelinesMapSize();

    Handle(TDocStd_Document) getDocumentHandle();
    CentralViewWidget* getCentralWidget();
    void _setCentralWidget();
    int GetTag();
    void SetTag(int tag);


    //init document in OpenCascade
    /**
     * 
     * @return TDF_label
     */
    Standard_Integer InitDocument();

    // Add Shape to OCAF tree.

private:
    //唯一标识该document
    Handle(TDocStd_Document) m_doc;
    //一个document对应一个viewWidget
    CentralViewWidget* m_widget = nullptr;

    std::map<QString, TopoDS_Shape> _shapeMap;
    std::map<QString, TopoDS_Shape> _newlyImportedShapeMap;

signals:


private:
    NCollection_DataMap<IVtk_IdType, Handle(QOccVtkSelPipeline)> _shapePipelinesMap;

    
public:
    //getter and setters
    [[nodiscard]] std::map<QString, TopoDS_Shape>& shape_map()
    {
        return _shapeMap;
    }

    [[nodiscard]] std::map<QString, TopoDS_Shape>& newly_imported_shape_map()
    {
        return _newlyImportedShapeMap;
    }

    [[nodiscard]] TDF_Label doc_data_root() const
    {
        return m_doc->Main();
    }

public:
    //tool functions
    TDF_Label GetShapeRoot() const;
    int GetShapeRootTag();
    void InitShapeRoot();
    //针对 Main Label
    int GetRootTag();



    [[nodiscard]] int getMaxShapeID()
    {
        return m_maxShapeID++;
    }

private:
    int m_maxShapeID = 0;

    //document间的唯一标识符，递增
    int m_tag = 0;

    int m_root_tag = INT_MIN;
    int m_shape_root_tag = INT_MIN;

private:
    Handle(TDF_Label) m_shapeRootHandle;
};
