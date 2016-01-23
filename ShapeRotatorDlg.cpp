#include "ShapeRotatorDlg.h"
#include "GenerateRotation.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wx/dcbuffer.h>
#include "vecmat.h"
//#include "Drawer3D.h"

//#include <dcbuffer.h>
using namespace std;


//Do not add custom headers
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// ShapeRotatorDlg
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start

BEGIN_EVENT_TABLE(ShapeRotatorDlg, wxDialog)
////Manual Code Start
////Manual Code End

EVT_CLOSE(ShapeRotatorDlg::OnClose)
EVT_BUTTON(ID_WXBUTTON3, ShapeRotatorDlg::WxButton3Click)

EVT_BUTTON(ID_WXBUTTON2, ShapeRotatorDlg::WxButton2Click)

EVT_BUTTON(ID_WXBUTTON1, ShapeRotatorDlg::drawRoteted)

EVT_COMMAND_SCROLL(ID_WXSB_ROTATEZ, ShapeRotatorDlg::WxSB_RotateZScroll)

EVT_COMMAND_SCROLL(ID_WXSB_ROTATEY, ShapeRotatorDlg::WxSB_RotateYScroll)

EVT_COMMAND_SCROLL(ID_WXSB_ROTATEX, ShapeRotatorDlg::WxSB_RotateXScroll)

EVT_COMMAND_SCROLL(ID_WXSB_ROTATEX, ShapeRotatorDlg::WxSB_RotateXScroll)

EVT_COMMAND_SCROLL(ID_WXSB_ROTATEX, ShapeRotatorDlg::WxSB_RotateXScroll)

EVT_COMMAND_SCROLL(ID_WXSB_ROTATEX, ShapeRotatorDlg::WxSB_RotateXScroll)

//EVT_SIZE(ShapeRotatorDlg::Resize)


EVT_UPDATE_UI(ID_WXPANEL1, ShapeRotatorDlg::WxPanel1UpdateUI)
END_EVENT_TABLE()
////Event Table End

ShapeRotatorDlg::ShapeRotatorDlg(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxDialog(parent, id, title, position, size, style) {
    CreateGUIControls();
    //initializeVectors();
}

ShapeRotatorDlg::~ShapeRotatorDlg() {
}

void ShapeRotatorDlg::CreateGUIControls() {


    WxBoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    this->SetSizer(WxBoxSizer1);
    this->SetAutoLayout(true);
    drawOn = false;
    cleared = false;
    firstPointDrawn = false;
    usingDrawMode = Line;

    
//    wxPanel* keyPane = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxWANTS_CHARS);
//    keyPane->Bind(wxEVT_CHAR_HOOK, &ShapeRotatorDlg::OnKeyDown, this);
    WxPanel1 = new wxPanel(this, ID_WXPANEL1, wxPoint(5, 5), wxSize(330, 288));
    WxPanel1->SetForegroundColour(wxColour(_("WHITE")));
    WxPanel1->SetBackgroundColour(wxColour(_("WHITE")));
    WxPanel1->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(ShapeRotatorDlg::mouseLeftClick), NULL, this);
    WxPanel1->Connect(wxEVT_MOTION, wxMouseEventHandler(ShapeRotatorDlg::mouseMotion), NULL, this);
    WxPanel1->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(ShapeRotatorDlg::mouseRightClick), NULL, this);

    WxBoxSizer1->Add(WxPanel1, 1, wxEXPAND | wxALL, 5);

    WxPanel2 = new wxPanel(this, ID_WXPANEL2, wxPoint(345, 10), wxSize(348, 278));
    WxPanel2->SetBackgroundColour(wxColour(_("WHITE")));
    WxBoxSizer1->Add(WxPanel2, 1, wxEXPAND | wxALL, 5);

    WxBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    WxBoxSizer1->Add(WxBoxSizer2, 0, wxALIGN_CENTER | wxALL, 5);

    WxBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    WxBoxSizer2->Add(WxBoxSizer3, 0, wxALIGN_CENTER | wxALL, 5);

    WxStaticText1 = new wxStaticText(this, ID_WXSTATICTEXT1, _("Rotate X:"), wxPoint(5, 5), wxDefaultSize, 0, _("WxStaticText1"));
    WxBoxSizer3->Add(WxStaticText1, 0, wxALIGN_CENTER | wxALL, 5);

    WxSB_RotateX = new wxScrollBar(this, ID_WXSB_ROTATEX, wxPoint(63, 5), wxSize(140, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("WxSB_RotateX"));
    WxSB_RotateX->Enable(false);
    WxBoxSizer3->Add(WxSB_RotateX, 0, wxALIGN_CENTER | wxALL, 5);

    WxST_RotateX = new wxStaticText(this, ID_WXST_ROTATEX, _("0  "), wxPoint(213, 5), wxDefaultSize, 0, _("WxST_RotateX"));
    WxBoxSizer3->Add(WxST_RotateX, 0, wxALIGN_CENTER | wxALL, 5);

    WxBoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    WxBoxSizer2->Add(WxBoxSizer4, 0, wxALIGN_CENTER | wxALL, 5);

    WxStaticText2 = new wxStaticText(this, ID_WXSTATICTEXT2, _("Rotate Y:"), wxPoint(5, 5), wxDefaultSize, 0, _("WxStaticText2"));
    WxBoxSizer4->Add(WxStaticText2, 0, wxALIGN_CENTER | wxALL, 5);

    WxSB_RotateY = new wxScrollBar(this, ID_WXSB_ROTATEY, wxPoint(63, 5), wxSize(140, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("WxSB_RotateY"));
    WxSB_RotateY->Enable(false);
    WxBoxSizer4->Add(WxSB_RotateY, 0, wxALIGN_CENTER | wxALL, 5);

    WxST_RotateY = new wxStaticText(this, ID_WXST_ROTATEY, _("0  "), wxPoint(213, 5), wxDefaultSize, 0, _("WxST_RotateY"));
    WxBoxSizer4->Add(WxST_RotateY, 0, wxALIGN_CENTER | wxALL, 5);

    WxBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    WxBoxSizer2->Add(WxBoxSizer5, 0, wxALIGN_CENTER | wxALL, 5);

    WxStaticText3 = new wxStaticText(this, ID_WXSTATICTEXT3, _("Rotate Z:"), wxPoint(5, 5), wxDefaultSize, 0, _("WxStaticText3"));
    WxBoxSizer5->Add(WxStaticText3, 0, wxALIGN_CENTER | wxALL, 5);

    WxSB_RotateZ = new wxScrollBar(this, ID_WXSB_ROTATEZ, wxPoint(63, 5), wxSize(140, 18), wxSB_HORIZONTAL, wxDefaultValidator, _("WxSB_RotateZ"));
    WxSB_RotateZ->Enable(false);
    WxBoxSizer5->Add(WxSB_RotateZ, 0, wxALIGN_CENTER | wxALL, 5);

    WxST_RotateZ = new wxStaticText(this, ID_WXST_ROTATEZ, _("0  "), wxPoint(213, 5), wxDefaultSize, 0, _("WxST_RotateZ"));
    WxBoxSizer5->Add(WxST_RotateZ, 0, wxALIGN_CENTER | wxALL, 5);

    WxButton1 = new wxButton(this, ID_WXBUTTON1, _("Draw"), wxPoint(84, 122), wxSize(75, 25), 0, wxDefaultValidator, _("WxButton1"));
    WxBoxSizer2->Add(WxButton1, 0, wxALIGN_CENTER | wxALL, 5);

    WxButton2 = new wxButton(this, ID_WXBUTTON2, _("Clean"), wxPoint(84, 157), wxSize(75, 25), 0, wxDefaultValidator, _("WxButton2"));
    WxBoxSizer2->Add(WxButton2, 0, wxALIGN_CENTER | wxALL, 5);

    WxButton3 = new wxButton(this, ID_WXBUTTON3, _("Save image"), wxPoint(84, 192), wxSize(75, 25), 0, wxDefaultValidator, _("WxButton3"));
    WxBoxSizer2->Add(WxButton3, 0, wxALIGN_CENTER | wxALL, 5);

    WxSaveFileDialog1 = new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.*"), wxFD_SAVE);

    SetTitle(_("ShapeRotator"));
    SetIcon(wxNullIcon);

    Layout();
    GetSizer()->Fit(this);
    GetSizer()->SetSizeHints(this);
    Center();

    WxSB_RotateX->SetScrollbar(0, 1, 361, 1, true);
    WxSB_RotateX->Enable(true);
    WxSB_RotateY->SetScrollbar(0, 1, 361, 1, true);
    WxSB_RotateY->Enable(true);
    WxSB_RotateZ->SetScrollbar(0, 1, 361, 1, true);
    WxSB_RotateZ->Enable(true);
    
    this->connectKeyDownEvent(this);
    //Init other depends objects 
    drawer3D = Drawer3D(WxPanel2);
    rotationVector = new Vector4();
    //OnScroll();


}

void ShapeRotatorDlg::OnClose(wxCloseEvent& /*event*/) {
    //deleteVectors();
    delete rotationVector; 
    Destroy();
}

void ShapeRotatorDlg::WxSB_RotateXScroll(wxScrollEvent& event) {
    wxString str;
    str << (WxSB_RotateX->GetThumbPosition());
    WxST_RotateX->SetLabel(str);
    OnScroll();
}

void ShapeRotatorDlg::WxSB_RotateYScroll(wxScrollEvent& event) {
    wxString str;
    str << (WxSB_RotateY->GetThumbPosition());
    WxST_RotateY->SetLabel(str);
    OnScroll();
}

void ShapeRotatorDlg::WxSB_RotateZScroll(wxScrollEvent& event) {
    wxString str;
    str << (WxSB_RotateZ->GetThumbPosition());
    WxST_RotateZ->SetLabel(str);
    OnScroll();
}

void ShapeRotatorDlg::clear2DData() {
    wxClientDC dcx(WxPanel1);
    wxBufferedDC dca(&dcx);
    dca.Clear();
    daneX.clear();
    daneY.clear();
}
void ShapeRotatorDlg::redraw2D() {
    wxClientDC dcx(WxPanel1);
    wxBufferedDC dca(&dcx);
    dca.Clear();
    int sizeX, sizeY;
    WxPanel1->GetSize(&sizeX, &sizeY);
    int dataSize = daneX.size();
    
    for(int i = 0;i< dataSize-1;i++) {
        dca.DrawLine(daneX[i]*sizeX, daneY[i]*sizeY, daneX[i+1]*sizeX, daneY[i+1]*sizeY);
    }
}
void ShapeRotatorDlg::mouseLeftClick(wxMouseEvent& event) {
    if(usingDrawMode == Curve) {
        drawOn = !drawOn;
        drawX = event.GetX();
        drawY = event.GetY();
        
    }  
    drawLine(event);    
}
void ShapeRotatorDlg::mouseRightClick(wxMouseEvent& event) {
    drawOn = false;
}
void ShapeRotatorDlg::mouseMotion(wxMouseEvent& event) {
    updateMouseMovePos(event);
    searchNearVertex(event);
    if(usingDrawMode == Curve && drawOn)
        drawCurve(event);
}
void ShapeRotatorDlg::drawLine(wxMouseEvent& event) {
    wxClientDC dcx(WxPanel1);
    wxBufferedDC dca(&dcx);

    drawer3D.Clear();
    
    if (!cleared) {
        dca.Clear();
        cleared = true;
    }
    if (drawOn) {
       // int x = event.GetX();
       // int y = event.GetY();
        int x = mouseMovePosX;
        int y = mouseMovePosY;
        dca.DrawLine(drawX, drawY, mouseMovePosX, mouseMovePosY);
        //drawX = event.GetX();
        //drawY = event.GetY();
        int sizeX, sizeY;
        WxPanel1->GetSize(&sizeX, &sizeY);
        daneX.push_back((double) drawX / (double) sizeX);
        daneY.push_back((double) drawY / (double) sizeY);
        daneX.push_back((double) x / (double) sizeX);
        daneY.push_back((double) y / (double) sizeY);
        drawX = x;
        drawY = y;
        // daneX.push_back(drawX);
        //daneY.push_back(drawY);
        //cout << mouseMovePosX << " " << mouseMovePosY << endl;
        //drawOn = false;
    } else if(usingDrawMode == Line) {
        if (!firstPointDrawn) {
            drawX = event.GetX();
            drawY = event.GetY();
        }
        //int sizeX, sizeY;
        //WxPanel1->GetSize(&sizeX, &sizeY);
        //daneX.push_back((double) drawX / (double) sizeX);
        //daneY.push_back((double) drawY / (double) sizeY);
        // cout << drawX << " " << drawY << endl;
        //daneX.push_back(drawX);
        //daneY.push_back(drawY);
        drawOn = true;
        firstPointDrawn = true;
    }


}

void ShapeRotatorDlg::drawFloatingLine() {
     if (drawOn) {
        wxClientDC dcx(WxPanel1);
        wxBufferedDC dca(&dcx);
        dca.DrawLine(drawX, drawY, mouseMovePosX, mouseMovePosY);
     }
    
}
void ShapeRotatorDlg::searchNearVertex(wxMouseEvent& event) {
    int searchRadius = 10;
    int num_of_points =  daneX.size();
    int sizeX, sizeY;
    WxPanel1->GetSize(&sizeX, &sizeY);
    for(int i = 0;i < num_of_points; i++) {
        if(sqrt(pow((event.GetX() - daneX[i]*sizeX), 2) + pow((event.GetY() - daneY[i]*sizeY), 2)) <= searchRadius)
        {
            mouseMovePosX =  daneX[i]*sizeX;
            mouseMovePosY = daneY[i]*sizeY;
            break;
        }
    }
}
void ShapeRotatorDlg::drawCurve(wxMouseEvent& event) {
    int drawStep = 3;
    int sizeX, sizeY;
    WxPanel1->GetSize(&sizeX, &sizeY);
    if(daneX.size() > 0 && sqrt(pow((mouseMovePosX - daneX.back()*sizeX), 2) + pow((mouseMovePosY - daneY.back()*sizeY), 2)) >= drawStep) {
        drawLine(event);
    }

}
void ShapeRotatorDlg::updateMouseMovePos(wxMouseEvent& event) {
    mouseMovePosX = event.GetX();
    mouseMovePosY = event.GetY();
}
void ShapeRotatorDlg::WxPanel1UpdateUI(wxUpdateUIEvent& event) {
    
    drawer3D.Repaint();
    redraw2D();
    if(usingDrawMode == Line)
        drawFloatingLine(); 
}

void ShapeRotatorDlg::WxButton3Click(wxCommandEvent& event) {
    // insert your code here
}
void ShapeRotatorDlg::WxButton2Click(wxCommandEvent& event) {
    clearAll();
}
void ShapeRotatorDlg::clearAll() {
    clear2DData();
    drawer3D.Clear();
    drawOn = false;
    cleared = false; 
    firstPointDrawn = false;
}

void ShapeRotatorDlg::OnScroll() {
     rotationVector->Set(WxSB_RotateX->GetThumbPosition(), WxSB_RotateY->GetThumbPosition(), WxSB_RotateZ->GetThumbPosition());
     drawer3D.UpdateRotation(*rotationVector);
     drawer3D.Repaint();
}
void ShapeRotatorDlg::drawRoteted(wxCommandEvent& event) {
    if (daneX.size() > 1) {
    int max = daneX.size() - daneX.size() % 2 -1;
    double** result = new double*[max];

    for (int i = 0; i < max; i++) {
        result[i] = new double[4];
    }

    for (int i = 0; i < max; i++) {
        result[i][0] = daneX[i];
        result[i][1] = daneY[i];
        result[i][2] = daneX[i + 1];
        result[i][3] = daneY[i + 1];
    }
    
    GenerateRotation gr(result, max);
    double** rotations = gr.generate();
    drawer3D.Clear();
    
    for(int i = 0; i < max; i++) {
        delete [] result[i];
    }
    
    delete [] result;
    
    Vector4 startVector;
    Vector4 endVector; 
    Vector4 colorVector;
    for (int i = 0; i < (gr.get_vec_num()) * 3 * (360/gr.get_angle()) ; i++) {
        startVector.Set(rotations[i][0], rotations[i][1], rotations[i][2]);
        endVector.Set(rotations[i][3], rotations[i][4],rotations[i][5]);
        colorVector.Set(rotations[i][6], rotations[i][7],rotations[i][8]);
        drawer3D.AddVector(startVector, endVector, colorVector);

    }
    
    gr.free_2d_arr(rotations);
    drawer3D.Repaint();
    }
}

void ShapeRotatorDlg::OnKeyDown(wxKeyEvent& event) {
        if (((wxKeyEvent&)event).GetKeyCode() == 76)
        {
                usingDrawMode = Line;
                 std::cout << "line\n";
        }
        else if (((wxKeyEvent&)event).GetKeyCode() == 67)
        {
            std::cout << "curve\n";     
            usingDrawMode = Curve;
        }
    
}
void ShapeRotatorDlg::connectKeyDownEvent(wxWindow* pclComponent) {
  if(pclComponent)
  {
    pclComponent->Connect(wxID_ANY, 
                          wxEVT_KEY_DOWN, 
                          wxKeyEventHandler(ShapeRotatorDlg::OnKeyDown),
                          (wxObject*) NULL,
                          this);

    wxWindowListNode* pclNode = pclComponent->GetChildren().GetFirst();
    while(pclNode)
    {
      wxWindow* pclChild = pclNode->GetData();
      this->connectKeyDownEvent(pclChild);
      
      pclNode = pclNode->GetNext();
    }
  }
}