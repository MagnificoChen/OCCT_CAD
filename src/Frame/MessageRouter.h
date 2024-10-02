//
// Created by 85147 on 9/23/2024.
//

#ifndef OCCT_CAD_MESSAGEROUTER_H
#define OCCT_CAD_MESSAGEROUTER_H


#include <QObject>
#include "src/CentralViewWidget.h"

enum VIEW_MSG{

};

enum GRIDBASE_MSG{
    G_FOCUS,
    G_UNFOCUS,
    G_BTN1_SEL_CHANGED,
    G_BTN2_SEL_CHANGED,
};

class MessageRouter : public QObject{
    Q_OBJECT
public:
explicit MessageRouter(CentralViewWidget* view);
void registerWidget(QWidget*);

private:
    CentralViewWidget* m_view;
    QOccDocument* m_doc;

    std::list<QWidget*> _widgetList;
};


#endif //OCCT_CAD_MESSAGEROUTER_H
