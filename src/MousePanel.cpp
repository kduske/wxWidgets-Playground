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

#include "MousePanel.h"

#include <wx/dcclient.h>
#include <wx/log.h>
#include <wx/timer.h>

#include <iostream>

#ifdef __APPLE__
#include "ApplicationServices/ApplicationServices.h"
#endif

namespace Playground {
    MousePanel::MousePanel(wxWindow* parent) :
    wxPanel(parent),
    m_dragging(false),
    m_ignoreMotion(false),
    m_timer(new wxTimer(this)) {
        Bind(wxEVT_LEFT_DOWN, &MousePanel::OnMouseLeftDown, this);
        Bind(wxEVT_LEFT_UP, &MousePanel::OnMouseLeftUp, this);
        Bind(wxEVT_MOTION, &MousePanel::OnMouseMotion, this);
        Bind(wxEVT_PAINT, &MousePanel::OnPaint, this);
    }
    
    MousePanel::~MousePanel() {
        delete m_timer;
        m_timer = NULL;
    }
    
    void MousePanel::OnMouseLeftDown(wxMouseEvent& event) {
        m_rectOrigin = event.GetPosition();

        captureCursor();
        CaptureMouse();
        m_dragging = true;

        Refresh();
    }
    
    void MousePanel::OnMouseLeftUp(wxMouseEvent& event) {
        m_dragging = false;

        ReleaseMouse();
        releaseCursor();
        
        Refresh();
    }
    
    void MousePanel::OnMouseMotion(wxMouseEvent& event) {
        if (!m_dragging || m_ignoreMotion)
            return;
     
        const wxPoint delta = getCursorDelta(event);
        m_rectOrigin += delta;
        
        updateCursor();

        std::cout << "Motion: " << delta.x << "," << delta.y << std::endl;
        wxLogDebug("Motion: %d,%d", delta.x, delta.y);
        Refresh();
    }
    
    void MousePanel::OnPaint(wxPaintEvent& event) {
        if (m_dragging) {
            wxPaintDC dc(this);
            const wxPoint origin = m_rectOrigin - wxPoint(5, 5);
            const wxSize size(10, 10);
            const wxRect rect(origin, size);
            
            dc.SetBrush(wxBrush(*wxRED));
            dc.DrawRectangle(rect);
        }
    }
    
    void MousePanel::captureCursor() {
        SetCursor(wxCursor(wxCURSOR_BLANK));
        
#ifdef __APPLE__
        CGAssociateMouseAndMouseCursorPosition(false);
        int32_t dx, dy;
        CGGetLastMouseDelta(&dx, &dy);
#else
        m_originalPoint = ScreenToClient(wxGetMousePosition());

        const wxPoint lockPos = getCenter();
        m_ignoreMotion = true;
        WarpPointer(lockPos.x, lockPos.y);
        m_ignoreMotion = false;
        m_lastMousePoint = lockPos;
#endif
    }
    
    void MousePanel::updateCursor() {
#ifndef __APPLE__
        const wxPoint lockPos = getCenter();
        m_ignoreMotion = true;
        WarpPointer(lockPos.x, lockPos.y);
        m_ignoreMotion = false;
#endif
    }
    
    void MousePanel::releaseCursor() {
#ifdef __APPLE__
        CGAssociateMouseAndMouseCursorPosition(true);
#else
        m_ignoreMotion = true;
        WarpPointer(m_originalPoint.x, m_originalPoint.y);
        m_ignoreMotion = false;
#endif
        SetCursor(wxNullCursor);
    }

    wxPoint MousePanel::getCursorDelta(const wxMouseEvent& event) {
#ifdef __APPLE__
        int32_t dx, dy;
        CGGetLastMouseDelta(&dx, &dy);
        return wxPoint(dx, dy);
#else
        return event.GetPosition() - m_lastMousePoint;
#endif
    }

    wxPoint MousePanel::getCenter() const {
        const wxSize size = GetSize();
        return wxPoint(size.x / 2, size.y / 2);
    }
}
