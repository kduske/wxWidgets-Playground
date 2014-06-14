/*
 Copyright (C) 2010-2014 Kristian Duske
 
 This file is part of Playground.
 
 Playground is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 Playground is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with Playground. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __Playground__MousePanel__
#define __Playground__MousePanel__

#include <wx/panel.h>

class wxTimer;
class wxTimerEvent;

namespace Playground {
    class MousePanel : public wxPanel {
    private:
        wxPoint m_originalPoint;
        wxPoint m_rectOrigin;
        wxPoint m_lastMousePoint;
        bool m_dragging;
        bool m_ignoreMotion;
        wxTimer* m_timer;
    public:
        MousePanel(wxWindow* parent);
        ~MousePanel();
        
        void OnMouseLeftDown(wxMouseEvent& event);
        void OnMouseLeftUp(wxMouseEvent& event);
        void OnMouseMotion(wxMouseEvent& event);
        void OnPaint(wxPaintEvent& event);
    private:
        void captureCursor();
        void updateCursor();
        void releaseCursor();
        wxPoint getCursorDelta(const wxMouseEvent& event);
        
        wxPoint getCenter() const;
    };
}

#endif /* defined(__Playground__MousePanel__) */
