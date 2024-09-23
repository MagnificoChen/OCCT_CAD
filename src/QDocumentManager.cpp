#include "QDocumentManager.h"

#include <BinDrivers.hxx>
#include <filesystem>
#include <QMessageBox>
#include <vtkLogger.h>


QDocumentManager* QDocumentManager::instance = nullptr;

QDocumentManager* QDocumentManager::getInstance()
{
    if (!instance)
    {
        instance = new QDocumentManager();
    }
    return instance;
}

int QDocumentManager::DocumentCount() const
{
    return m_app->NbDocuments();
}

opencascade::handle<XCAFApp_Application> QDocumentManager::getApplicationHandle()
{
    return m_app;
}

QOccDocument* QDocumentManager::getCurrentDocument()
{
    return m_currDocument;
}

QDocumentManager::QDocumentManager()
{
    instance = this;
    m_app = XCAFApp_Application::GetApplication();
    // m_app->get_type_descriptor()

    BinDrivers::DefineFormat(m_app);
}

QDocumentManager::~QDocumentManager()
{
    m_app.Nullify();
}


bool QDocumentManager::OnNewDocument(bool isLoad, const QString& filePath)
{
    if (isLoad)
    {
        qDebug() << "Loading New Document...";
        Handle(TDocStd_Document) stdDoc;
        const PCDM_ReaderStatus readStatus = m_app->Open(filePath.toStdWString().c_str(), stdDoc);

        if (stdDoc->IsValid()) AddDocument(stdDoc);
        qDebug() << readStatus;
    }
    else
    {
        qDebug() << "Creating New Document...";
        Handle(TDocStd_Document) stdDoc;
        m_app->NewDocument("BinOcaf", stdDoc);
        if (stdDoc.IsNull())
        {
            QMessageBox::warning(OccDemoMainWindow::getInstance(), "warning", "failed to create document.");
            return false;
        }
        AddDocument(stdDoc);
    }


    return true;
}

bool QDocumentManager::SaveDocument(const QString& filePath)
{
    PCDM_StoreStatus sStatus = m_app->SaveAs(m_currDocument->getDocumentHandle(), filePath.toStdWString().c_str());
    if (sStatus == PCDM_SS_Failure)
    {
        qDebug() << "Save Action Failed!";
    }
    return true;
}

bool QDocumentManager::LoadGeometry(const QString& filePath, FileFormat format)
{
    TopoDS_Shape shape_Stl;
    Standard_Boolean result = Standard_False;
    auto stdFilePath = filePath.toStdString();

    switch (format)
    {
    case STL:
        {
            StlAPI_Reader aReader_Stl;
            result = aReader_Stl.Read(shape_Stl, filePath.toStdString().c_str());
            Handle(XCAFDoc_ShapeTool) shapeTool = XCAFDoc_ShapeTool::Set(m_currDocument->getDocumentHandle()->Main());
            TDF_Label shapeLabel = shapeTool->AddShape(shape_Stl, false);
            qDebug() << "Newly added shape Tag :" << shapeLabel.Tag();

            break;
        }
    case STEP:
        {
            STEPCAFControl_Reader aReader_step;
            // Reading colors mode
            aReader_step.SetColorMode(true);
            // Reading layers information mode
            aReader_step.SetLayerMode(true);
            // Reading names from step file mode
            aReader_step.SetNameMode(true);

            //check path validity
            if (!std::filesystem::exists(stdFilePath))
            {
                auto message = "File " + stdFilePath + " can not be found.";
                vtkLogF(ERROR, message.c_str());
                auto errorCode = std::make_error_code(std::errc::no_such_file_or_directory);
                throw std::filesystem::filesystem_error(message, errorCode);
            }
            auto baseName = std::filesystem::path{stdFilePath}.stem().generic_string();
            vtkLogF(INFO, "Geometry file path: \"%s\"", stdFilePath.c_str());

            IFSelect_ReturnStatus result = aReader_step.ReadFile(stdFilePath.c_str());
            if (result != IFSelect_RetDone)
            {
                auto message = "Error while reading file:" + stdFilePath;
                vtkLogF(ERROR, message.c_str());
                auto errorCode = std::make_error_code(std::errc::device_or_resource_busy);
                throw std::filesystem::filesystem_error(message, errorCode);
            }

            // 获取Document的工具类
            Handle(XCAFDoc_DocumentTool) tool = XCAFDoc_DocumentTool::Set(m_currDocument->getDocumentHandle()->Main());

            if (!aReader_step.Transfer(m_currDocument->getDocumentHandle()))
            {
                auto message = "Error while reading file:" + stdFilePath;
                vtkLogF(ERROR, message.c_str());
                auto errorCode = std::make_error_code(std::errc::device_or_resource_busy);
                throw std::filesystem::filesystem_error(message, errorCode);
            }

            auto& reader = aReader_step.Reader();
            auto shapeTool = XCAFDoc_DocumentTool::ShapeTool(this->m_currDocument->getDocumentHandle()->Main());

            Standard_Integer numberOfShapes = reader.NbShapes();
            if (numberOfShapes == 0)
            {
                auto message = "No shapes found in given STEP file.";
                vtkLogF(ERROR, message);
                auto errorCode = std::make_error_code(std::errc::device_or_resource_busy);
                throw std::filesystem::filesystem_error(message, errorCode);
            }
            else
            {
                //newShape add
                this->m_currDocument->newly_imported_shape_map().clear();

                for (auto i = 1; i <= numberOfShapes; i++)
                {
                    auto shape = reader.Shape(i);
                    std::string uniqueName = _getUniqueObjectName("Shape", m_currDocument->shape_map());
                    this->m_currDocument->shape_map()[QString::fromStdString(uniqueName)] = shape;
                    this->m_currDocument->newly_imported_shape_map()[QString::fromStdString(uniqueName)] = shape;
                }
            }

            QString message = "STEP file loaded successfully.";
            vtkLogF(INFO, message.toStdString().c_str());
            break;
        }
    case UNKNOWN:
        {
            return false;
        }
    }

    emit signalUpdateView();
    return result;
}


//!important 在调用Load或New之后，需要用AddDocument将QOccDocument加 入到DocumentManager中。
bool QDocumentManager::AddDocument(opencascade::handle<TDocStd_Document> doc)
{
    //TODO: add document to DocManager, UpdateVTKView, UpdateQtView.
    QOccDocument* occDoc = new QOccDocument(nullptr, doc);
    //get last tag, put this doc to the end of the array.
    auto lastTag = m_docPtrArray.empty() ? 0 : m_docPtrArray.back()->GetTag();
    occDoc->SetTag(++lastTag);
    m_docPtrArray.push_back(occDoc);

    //将ViewDoc对应关系添加到OccDemo类中存储
    OccDemoMainWindow::getInstance()->AddViewDocItem({
        OccDemoMainWindow::getInstance()->GetActiveViewWidget(), occDoc->GetTag()
    });
    OccDemoMainWindow::getInstance()->GetActiveViewWidget()->SetDocument(occDoc);
    occDoc->_setCentralWidget();
    //将当前Doc设置为CurrentDocument
    m_currDocument = occDoc;
    return true;
}


bool QDocumentManager::OnChangeDocument(int tag)
{
    qDebug() << "From QDocumentManager: OnChangeDocument Triggered...";
    if (tag == m_currDocument->GetTag())
    {
        return true;
    }
    auto itF = std::find_if(m_docPtrArray.begin(), m_docPtrArray.end(), [tag](QOccDocument* doc)
    {
        return tag == doc->GetTag();
    });
    if (itF != m_docPtrArray.end())
    {
        m_currDocument = *itF;
    }
    else
    {
        qDebug() << "Maybe some error here, Doc/View relationship not found...";
        return false;
    }


    return true;
}


std::string QDocumentManager::_getUniqueObjectName(const std::string& prefix, const std::map<QString, TopoDS_Shape>& objectMap)
{
    int i = 1;
    std::string uniqueName;
    while (true)
    {
        std::stringstream stringStream;
        stringStream << prefix << std::setfill('0') << std::setw(3) << i;
        uniqueName = stringStream.str();
        auto s = QString::fromStdString( uniqueName );
        if (!objectMap.contains(s))
        {
            break;
        }
        i++;
    }
    return uniqueName;
};