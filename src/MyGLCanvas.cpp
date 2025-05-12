// MyGLCanvas.cpp
#include "MyGLCanvas.h"

wxBEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
    EVT_PAINT(MyGLCanvas::OnPaint)
    EVT_SIZE(MyGLCanvas::OnResize)
    EVT_MOTION(MyGLCanvas::OnMouseMove)
    EVT_LEFT_DOWN(MyGLCanvas::OnMouseLeftDown)
wxEND_EVENT_TABLE()

int gl_attribs[] = {
    WX_GL_RGBA,
    WX_GL_DOUBLEBUFFER,
    WX_GL_DEPTH_SIZE, 16,
    0, 0
};

MyGLCanvas::MyGLCanvas(wxWindow* parent, std::function<void()> onOverlayButtonClicked)
    : wxGLCanvas(parent, wxID_ANY, gl_attribs, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
      m_context(new wxGLContext(this)),
    m_onOverlayButtonClicked(onOverlayButtonClicked)
{
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
    SetCurrent(*m_context);
    m_button = std::make_unique<OverlayButton>(0,0);  // Create the overlay button
}

MyGLCanvas::~MyGLCanvas() {
    m_button.reset(); // clear item before an invalid context.
    if (m_context) delete m_context;
}

void MyGLCanvas::SetSceneScale(float scale)
{
    m_scale = scale;
}

void MyGLCanvas::SetWireframeMode(bool enabled)
{
    m_wireframeEnabaled = enabled;
}

void MyGLCanvas::OnPaint(wxPaintEvent&) {
    wxPaintDC dc(this);
    SetCurrent(*m_context);
    Render();
    SwapBuffers();
}

void MyGLCanvas::OnResize(wxSizeEvent& evt) {
    if (!IsShown()) return;
    wxSize size = GetClientSize();
    SetCurrent(*m_context);
    glViewport(0, 0, size.x, size.y);
    Refresh(false);
    evt.Skip();
}

void MyGLCanvas::OnMouseMove(wxMouseEvent& evt) {
    m_mousePos = evt.GetPosition();
    bool wasHovering = m_hovering;
    m_hovering = IsMouseOverRectangle(m_mousePos);

    bool buttonWasHovering = m_button->isHovering();
    bool buttonHovering = m_button->HitTest(m_mousePos.x, m_mousePos.y);
    m_button->setHovering(buttonHovering);

    if (m_hovering != wasHovering || buttonHovering != buttonWasHovering) {
        Refresh(false);  // Trigger repaint on hover state change
    }
    evt.Skip();
}

void MyGLCanvas::OnMouseLeftDown(wxMouseEvent& evt)
{
    int mouseX = evt.GetX();
    int mouseY = evt.GetY();

    if (m_button && m_button->HitTest(mouseX, mouseY)) {
        if(m_onOverlayButtonClicked)
            m_onOverlayButtonClicked();
        m_button->toggleTexture();
        Refresh(false);
    }

    evt.Skip(); // Allow other handlers to process if needed
}

void MyGLCanvas::Render() {
    wxSize size = GetClientSize();

    glClearColor(0.9f, 0.9f, 0.9f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, size.x, size.y, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawRectangle();

    m_button->Render();
}

void MyGLCanvas::DrawRectangle() {

    int x = 100, y = 150, w = 200 * m_scale, h = 150 * m_scale;

    if(m_wireframeEnabaled)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else 
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (m_hovering)
        glColor3f(1.0f, 0.5f, 0.2f);  // Orange on hover
    else
        glColor3f(0.0f, 0.7f, 1.0f);  // Blue

    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + w, y);
    glVertex2i(x + w, y + h);
    glVertex2i(x, y + h);
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

bool MyGLCanvas::IsMouseOverRectangle(const wxPoint& pt) {
    int x = 100, y = 150, w = 200 * m_scale, h = 150 * m_scale;
    return pt.x >= x && pt.x <= x + w && pt.y >= y && pt.y <= y + h;
}
