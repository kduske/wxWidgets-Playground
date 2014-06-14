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

#include "PlaygroundApp.h"

#include "TestFrame.h"

#include <clocale>

IMPLEMENT_APP(Playground::PlaygroundApp)

namespace Playground {
        bool PlaygroundApp::OnInit() {
            if (!wxApp::OnInit())
                return false;

            // always set this locale so that we can properly parse floats from text files regardless of the platforms locale
            std::setlocale(LC_NUMERIC, "C");

            SetAppName("Playground");
            SetAppDisplayName("Playground");
            SetVendorDisplayName("Kristian Duske");
            SetVendorName("Kristian Duske");

            // load image handlers
            wxImage::AddHandler(new wxPNGHandler());

#ifdef __APPLE__
            SetExitOnFrameDelete(true);
#endif

            TestFrame* frame = new TestFrame();
            frame->Show();
            frame->CentreOnScreen();
            
            return true;
        }

        int PlaygroundApp::OnExit() {
            wxImage::CleanUpHandlers();
            return wxApp::OnExit();
        }

        void PlaygroundApp::OnUnhandledException() {
            try {
                throw;
            } catch (std::exception& e) {
                wxLogError(e.what());
            } catch (...) {
                wxLogError("Unhandled exception");
            }
        }
}
