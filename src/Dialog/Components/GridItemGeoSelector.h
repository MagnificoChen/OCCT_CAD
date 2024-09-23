#pragma once
#include "GridItemBase.h"

class GridItemGeoSelector : public GridItemBase
{
public:
    enum GRID_SELECTOR_MSG
    {
        MSG_SELECTOR_STN_CLICKED,
        MSG_SELECTOR_FOCUS_LOST,
        MSG_SELECTOR_VALUE_CHANGED,
        MSG_SELECTOR_TRACK_MENU,
        MSG_SELECTOR_TRACK_MENU_HOVERED,
        MSG_MBTN_DOWN_IN_VIEW,
        MSG_MOUSE_MOVE_IN_VIEW
    };

public:
    GridItemGeoSelector(QString mainButtonText = QString("DerivedGridItem"), CentralViewWidget* view = nullptr);
    CentralViewWidget* m_pView = nullptr;
private:



};
