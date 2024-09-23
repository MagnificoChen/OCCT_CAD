#include "QOccDocument.h"

#include <QMessageBox>

#include "OccDemoMainWindow.h"
#include "QDocumentManager.h"

QOccDocument::QOccDocument(QObject* parent, Handle(TDocStd_Document) document)
    : QObject(parent)
{
    this->m_doc = document;
    TDF_TagSource::Set(m_doc->GetData()->Root());
    m_root_tag = doc_data_root().Tag();

    //init shape root,used for father label of shape labels.
    InitShapeRoot();
}


QOccDocument::~QOccDocument()
{
}

NCollection_List<Handle(QOccVtkSelPipeline)> QOccDocument::getPipelines()
{
    NCollection_List<Handle(QOccVtkSelPipeline)> pipelineList;
    for (NCollection_DataMap<IVtk_IdType, Handle(QOccVtkSelPipeline)>::Iterator
         it(_shapePipelinesMap); it.More(); it.Next())
    {
        const Handle(QOccVtkSelPipeline)& pipeline = it.Value();
        pipelineList.Append(pipeline);
    }

    return pipelineList;
}


Standard_Integer QOccDocument::getPipelinesMapSize()
{
    return _shapePipelinesMap.Size();
}

opencascade::handle<TDocStd_Document> QOccDocument::getDocumentHandle()
{
    return m_doc;
}

CentralViewWidget* QOccDocument::getCentralWidget()
{
    return m_widget;
}

void QOccDocument::_setCentralWidget()
{
    if (m_widget)
    {
        qDebug() << "warning: reassign m_widget";
    }
    m_widget = OccDemoMainWindow::getInstance()->getDocViewMap()[m_tag];
}

void QOccDocument::SetTag(int tag)
{
    m_tag = tag;
}

int QOccDocument::GetTag()
{
    return m_tag;
}


Standard_Integer QOccDocument::InitDocument()
{
    //TODO return label
    return 0;
}


//ShapeRoot 操作
TDF_Label QOccDocument::GetShapeRoot() const
{
    return doc_data_root().FindChild(m_shape_root_tag,Standard_True);
}

int QOccDocument::GetShapeRootTag()
{
    return m_shape_root_tag;
}

void QOccDocument::InitShapeRoot()
{
    if (m_shape_root_tag != INT_MIN) return;
    m_shape_root_tag = TDF_TagSource::NewChild(doc_data_root()).Tag();

}

int QOccDocument::GetRootTag()
{
    return m_root_tag;
}
