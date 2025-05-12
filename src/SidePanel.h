#pragma once

#include <wx/wx.h>

class SidePanel : public wxPanel {
public:
    SidePanel(wxWindow* parent);

    void setOnSliderChanged(std::function<void(float scale)> onSliderChanged);
    void setOnRenderModeToggled(std::function<void(bool wireframe)> onRenderModeToggled);
private:
    wxSlider* m_slider;
    wxCheckBox* m_renderModeCheckbox;

    std::function<void(float scale)> m_onSliderChanged;
    std::function<void(bool wireframe)> m_onRenderModeToggled;

    void sliderChanged(wxCommandEvent& event);
    void renderModeToggled(wxCommandEvent& event);
};
