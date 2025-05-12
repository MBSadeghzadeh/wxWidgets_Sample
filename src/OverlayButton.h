#pragma once

#include <wx/wx.h>
#include <wx/glcanvas.h>

class OverlayButton {
public:
    OverlayButton(int x, int y);
    ~OverlayButton();

    void Render();  // Renders the button texture to the canvas
    bool HitTest(int x, int y);  // Check if the click is inside the button area

    void setHovering(bool hovering);

    bool isHovering();

    void toggleTexture();

private:
    GLuint m_textureID[2];  // OpenGL texture ID
    byte m_textureIndex = 1;
    int m_x, m_y;  // Button position
    int m_width, m_height;  // Button size
    bool m_hovering = false;

    void LoadTexture(const wxString& imagePath, GLuint *textureID);
};
