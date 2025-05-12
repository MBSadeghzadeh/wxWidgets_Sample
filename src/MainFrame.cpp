#include "MainFrame.h"
#include "MyGLCanvas.h"
#include "SidePanel.h"

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "wxWidgets + OpenGL Layout", wxDefaultPosition, wxSize(900, 600))
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);


    m_sidePanel = new SidePanel(this);

    m_canvas = new MyGLCanvas(this, 
        [this]() {
            if (m_sidePanel->IsShown()) {
                m_sidePanel->Hide();
            }
            else {
                m_sidePanel->Show();
            }
            this->Layout(); 
        });

    m_sidePanel->setOnSliderChanged([this](float scale) {
        
        m_canvas->SetSceneScale(scale);
        m_canvas->Refresh(); // Trigger redraw

        });;

    m_sidePanel->setOnRenderModeToggled([this](bool wireframe) {
        m_canvas->SetWireframeMode(wireframe);
        m_canvas->Refresh();
        });

    mainSizer->Add(m_canvas, 1, wxEXPAND | wxALL, 5);

    mainSizer->Add(m_sidePanel, 0, wxEXPAND | wxALL, 5);

    SetSizer(mainSizer);
}
