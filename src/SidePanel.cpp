#include "SidePanel.h"

SidePanel::SidePanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(250, -1))
{
    SetBackgroundColour(*wxLIGHT_GREY);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    // Scale slider
    m_slider = new wxSlider(this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL | wxSL_LABELS);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Scale"), 0, wxTOP | wxLEFT, 5);
    sizer->Add(m_slider, 0, wxEXPAND | wxALL, 5);


    // Rendering mode checkbox
    m_renderModeCheckbox = new wxCheckBox(this, wxID_ANY, "Filled");
    m_renderModeCheckbox->SetValue(true);
    sizer->Add(m_renderModeCheckbox, 0, wxALL, 5);

    SetSizer(sizer);


    m_slider->Bind(wxEVT_SLIDER, &SidePanel::sliderChanged, this);
    m_renderModeCheckbox->Bind(wxEVT_CHECKBOX, &SidePanel::renderModeToggled, this);
}

void SidePanel::setOnSliderChanged(std::function<void(float scale)> onSliderChanged)
{
    m_onSliderChanged = onSliderChanged;
}

void SidePanel::setOnRenderModeToggled(std::function<void(bool wireframe)> onRenderModeToggled)
{
    m_onRenderModeToggled = onRenderModeToggled;
}

void SidePanel::sliderChanged(wxCommandEvent& event)
{
    if(m_onSliderChanged)
        m_onSliderChanged(m_slider->GetValue() / 50.0f);
}

void SidePanel::renderModeToggled(wxCommandEvent& event)
{
    if(m_onRenderModeToggled)
        m_onRenderModeToggled(!m_renderModeCheckbox->IsChecked());
}
