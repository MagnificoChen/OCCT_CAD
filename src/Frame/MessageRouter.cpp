//
// Created by 85147 on 9/23/2024.
//

#include "MessageRouter.h"
#include "../QDocumentManager.h"

MessageRouter::MessageRouter(CentralViewWidget *view) {
    m_view = view;
//    m_doc = QDocumentManager::getInstance()->get
//            OccDemoMainWindow::getInstance()->getViewDocMap()

}

void MessageRouter::registerWidget(QWidget*) {

}
