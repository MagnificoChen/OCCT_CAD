#pragma once

#include "GlobalDefines.h"
#include <QObject>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include "OccDemoMainWindow.h"
#include "QOccDocument.h"
#include <TDocStd_Application.hxx>
#include <XCAFApp_Application.hxx>
#include <StlAPI_Writer.hxx>
#include <StlAPI_Reader.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <TDataStd_Integer.hxx>
#include <BinLDrivers.hxx>
#include <BinXCAFDrivers.hxx>
#include <BinDrivers_DocumentRetrievalDriver.hxx>
#include <BinDrivers_DocumentStorageDriver.hxx>

class QDocumentManager : public QObject
{
    Q_OBJECT
public:
    QDocumentManager();
    ~QDocumentManager();
    static QDocumentManager* getInstance();
    int DocumentCount() const;
    Handle(XCAFApp_Application) getApplicationHandle();
    QOccDocument* getCurrentDocument();
    bool AddDocument(Handle(TDocStd_Document) doc);


public slots:
    //handle signal: signalAddNewDocument
    //including New/Load Document.
    bool OnNewDocument(bool isLoad, const QString& filePath);

    //Support Qt Save/Load Module
    bool SaveDocument(const QString& filePath);

    bool LoadGeometry(const QString& filePath, FileFormat format);
    //Support QtMDIWindow 
    bool OnChangeDocument(int tag);

    //generate a unique name for all imported shapes
    static std::string _getUniqueObjectName(const std::string& prefix, const std::map<QString, TopoDS_Shape>& objectMap);

signals:
    // To CentralViewWidget
    void signalUpdateView();
private:
    static QDocumentManager* instance;
    Handle(XCAFApp_Application) m_app;
    QOccDocument* m_currDocument = nullptr;
    std::vector<std::pair<Handle(TDocStd_Document), TDF_Label>> m_documents;
    std::vector<QOccDocument*> m_docPtrArray;
};
