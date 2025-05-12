#pragma once

#include <wx/wx.h>

class MyGLCanvas;
class SidePanel;

class MainFrame : public wxFrame {
public:
    MainFrame();

private:
    MyGLCanvas* m_canvas;
    SidePanel* m_sidePanel;
};
