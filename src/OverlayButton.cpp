#include "OverlayButton.h"
#include <wx/bitmap.h>
#include <wx/image.h>
#include <GL/gl.h>

OverlayButton::OverlayButton(int x, int y)
    : m_x(x), m_y(y)
{
    m_width = 50;
    m_height = 50;
    LoadTexture("resources/left_arrow.png", &m_textureID[0]);
    LoadTexture("resources/right_arrow.png", &m_textureID[1]);
}

OverlayButton::~OverlayButton() {
    if (glIsTexture(m_textureID[0]) || glIsTexture(m_textureID[1])) {
        glDeleteTextures(2, m_textureID); // Clean up texture
    }
}

void OverlayButton::LoadTexture(const wxString& imagePath, GLuint *textureID) {

    wxImage image(imagePath, wxBITMAP_TYPE_PNG);
    if (!image.IsOk()) {
        wxLogError("Failed to load PNG image.");
        return;
    }

    if (!image.HasAlpha()) {
        image.InitAlpha();  // Create a full-opacity alpha channel if none exists
    }

    int width = image.GetWidth();
    int height = image.GetHeight();
    unsigned char* rgb = image.GetData();
    unsigned char* alpha = image.GetAlpha();

    std::vector<unsigned char> rgba(width * height * 4);
    if (image.HasMask()) {
        // For indexed images (8-bit grayscale or palette), assume the image is grayscale and convert
        for (int i = 0; i < width * height; ++i) {
            unsigned char gray = rgb[i]; // Read grayscale value
            rgba[4 * i + 0] = gray;     // Set R
            rgba[4 * i + 1] = gray;     // Set G
            rgba[4 * i + 2] = gray;     // Set B
            rgba[4 * i + 3] = 255;      // Set Alpha (fully opaque)
        }
    }
    else {
        // If it's not indexed (full color image), process RGBA correctly
        for (int i = 0; i < width * height; ++i) {
            rgba[4 * i + 0] = rgb[3 * i + 0]; // R
            rgba[4 * i + 1] = rgb[3 * i + 1]; // G
            rgba[4 * i + 2] = rgb[3 * i + 2]; // B
            rgba[4 * i + 3] = alpha ? alpha[i] : 255; // Alpha (either from image or set to 255)
        }
    }

    // Create OpenGL texture
    glGenTextures(1, textureID);
    glBindTexture(GL_TEXTURE_2D, *textureID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Avoid padding issues
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba.data());
    GLenum err = glGetError();
    if (err != GL_NO_ERROR) {
        wxLogError("OpenGL error: %d", err);
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OverlayButton::Render() {

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_textureID[m_textureIndex]);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if (m_hovering) {
        glColor4f(0, 0, 0, 0.5f);
    }

    // Draw the textured rectangle for the button
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(m_x, m_y);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(m_x + m_width, m_y);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(m_x + m_width, m_y + m_height);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(m_x, m_y + m_height);
    glEnd();

    glColor3f(1, 1, 1);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

bool OverlayButton::HitTest(int x, int y) {
    // Check if the mouse click is inside the button bounds
    return x >= m_x && x <= m_x + m_width && y >= m_y && y <= m_y + m_height;
}

void OverlayButton::setHovering(bool hovering)
{
    m_hovering = hovering;
}

bool OverlayButton::isHovering()
{
    return m_hovering;
}

void OverlayButton::toggleTexture()
{
    m_textureIndex++;
    m_textureIndex %= 2;
}
