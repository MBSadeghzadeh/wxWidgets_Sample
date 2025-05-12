// MyGLCanvas.h
#pragma once

#include "OverlayButton.h"

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <memory>

class MyGLCanvas : public wxGLCanvas {
public:
    MyGLCanvas(wxWindow* parent, std::function<void()> onOverlayButtonClicked);
    ~MyGLCanvas();

    void SetSceneScale(float scale);
    void SetWireframeMode(bool enabled);

private:
    wxGLContext* m_context;
    std::unique_ptr<OverlayButton> m_button;  // The overlay button
    std::function<void()> m_onOverlayButtonClicked;
    wxPoint m_mousePos;
    bool m_hovering = false;
    float m_scale = 1.0f;
    bool m_wireframeEnabaled = false;

    void OnPaint(wxPaintEvent& evt);
    void OnResize(wxSizeEvent& evt);
    void OnMouseMove(wxMouseEvent& evt);
    void OnMouseLeftDown(wxMouseEvent& evt);
    

    void Render();
    void DrawRectangle();
    bool IsMouseOverRectangle(const wxPoint& pt);

    DECLARE_EVENT_TABLE()
};
