#include "MainFrame.h"

#include <wx/wx.h>

// A basic wxWidgets application class
class MyApp : public wxApp {
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    wxInitAllImageHandlers();
    MainFrame* frame = new MainFrame();
    frame->Show();
    return true;
}
