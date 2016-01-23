#include "ShapeRotatorDlg.h"
#include "vecmat.h"
#include "GenerateRotation.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <wx/dcbuffer.h>
//#include <dcbuffer.h>
using namespace std;
std::vector <double> x_start, x_end, y_start, y_end, z_start, z_end;
std::vector <int> R, G, B;
double d = -2.0;

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
    initializeVectors();
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

    ////GUI Items Creation End
    //WxOpenFileDialog->SetWildcard("Geometry file (*.geo)|*.geo");
    /*
WxSB_TranslationX->SetScrollbar(50, 1, 101, 1,true);
    WxSB_TranslationX->Enable(true);
    WxSB_TranslationY->SetScrollbar(50, 1, 101, 1,true);
    WxSB_TranslationY->Enable(true);
    WxSB_TranslationZ->SetScrollbar(50, 1, 101, 1,true);
    WxSB_TranslationZ->Enable(true);
     */
    WxSB_RotateX->SetScrollbar(0, 1, 361, 1, true);
    WxSB_RotateX->Enable(true);
    WxSB_RotateY->SetScrollbar(0, 1, 361, 1, true);
    WxSB_RotateY->Enable(true);
    WxSB_RotateZ->SetScrollbar(0, 1, 361, 1, true);
    WxSB_RotateZ->Enable(true);

    /*
    WxSB_ScaleX->SetScrollbar(99, 1, 200, 1,true);
        WxSB_ScaleX->Enable(true);
    WxSB_ScaleY->SetScrollbar(99, 1, 200, 1,true);
        WxSB_ScaleY->Enable(true);
    WxSB_ScaleZ->SetScrollbar(99, 1, 200, 1,true);
        WxSB_ScaleZ->Enable(true);	
     */
}

void ShapeRotatorDlg::OnClose(wxCloseEvent& /*event*/) {
    deleteVectors();
    Destroy();
}


/*
 * WxButtonLoadClick
 */
void ShapeRotatorDlg::WxButtonLoadClick(wxCommandEvent& event) {
    /*if (WxOpenFileDialog->ShowModal()==wxID_OK)
    {
     double x1,y1,z1,x2,y2,z2;
     int r,g,b;
  
     std::string line;
     std::ifstream in(WxOpenFileDialog->GetPath().ToAscii());
     if (in.is_open())
     {
      x_start.clear();y_start.clear();z_start.clear();
      x_end.clear();y_end.clear();z_end.clear();
      R.clear();G.clear();B.clear();
      while (!in.eof())
      {
       in>>x1>>y1>>z1>>x2>>y2>>z2>>r>>g>>b;
       x_start.push_back(x1);x_end.push_back(x2);
       y_start.push_back(y1);y_end.push_back(y2);
       z_start.push_back(z1);z_end.push_back(z2);
       R.push_back(r);G.push_back(g);B.push_back(b);
      }
      in.close();
     }
    }*/
}

//MY CODE START

void ShapeRotatorDlg::initializeVectors() {
    rotAngleV = new Vector4();
    scaleV = new Vector4();
    translationV = new Vector4();
    rotationMatrixComplete = new Matrix4();
    rotationMatrixX = new Matrix4();
    rotationMatrixY = new Matrix4();
    rotationMatrixZ = new Matrix4();
    translationMatrix = new Matrix4();
    scaleMatrix = new Matrix4();
    perspectiveMatrix = new Matrix4();
}

void ShapeRotatorDlg::deleteVectors() {
    delete rotAngleV;
    delete scaleV;
    delete translationV;
    delete rotationMatrixComplete;
    delete rotationMatrixX;
    delete rotationMatrixY;
    delete rotationMatrixZ;
    delete translationMatrix;
    delete scaleMatrix;
    delete perspectiveMatrix;
}

Matrix4 ShapeRotatorDlg::getRotationMatrix(Vector4 *rotAngle) {
    rotationMatrixX->data[0][0] = 1;
    rotationMatrixX->data[1][1] = cos(rotAngle->GetX());
    rotationMatrixX->data[1][2] = -sin(rotAngle->GetX());
    rotationMatrixX->data[2][1] = sin(rotAngle->GetX());
    rotationMatrixX->data[2][2] = cos(rotAngle->GetX());

    rotationMatrixY->data[0][0] = cos(rotAngle->GetY());
    rotationMatrixY->data[0][2] = sin(rotAngle->GetY());
    rotationMatrixY->data[1][1] = 1;
    rotationMatrixY->data[2][0] = -sin(rotAngle->GetY());
    rotationMatrixY->data[2][2] = cos(rotAngle->GetY());

    rotationMatrixZ->data[0][0] = cos(rotAngle->GetZ());
    rotationMatrixZ->data[0][1] = -sin(rotAngle->GetZ());
    rotationMatrixZ->data[1][0] = sin(rotAngle->GetZ());
    rotationMatrixZ->data[1][1] = cos(rotAngle->GetZ());
    rotationMatrixZ->data[2][2] = 1;

    *rotationMatrixComplete = (*rotationMatrixX) * (*rotationMatrixY) * (*rotationMatrixZ);
    return *rotationMatrixComplete;

}

Matrix4 ShapeRotatorDlg::getTranslateMatrix(Vector4 *trans) {
    for (int i = 0; i <= 3; ++i) {
        translationMatrix->data[i][i] = 1;
    }
    translationMatrix->data[0][3] = trans->GetX();
    translationMatrix->data[1][3] = trans->GetY();
    translationMatrix->data[2][3] = trans->GetZ();
    return *translationMatrix;
}

Matrix4 ShapeRotatorDlg::getScaleMatrix(Vector4 *scale) {
    scaleMatrix->data[0][0] = scale->GetX();
    scaleMatrix->data[1][1] = scale->GetY();
    scaleMatrix->data[2][2] = scale->GetZ();
    return *scaleMatrix;
}

void ShapeRotatorDlg::setPerspective(Vector4 *point3D, double d) {
    /*perspectiveMatrix->data[0][0] = 1;
    perspectiveMatrix->data[1][1] = 1;
    perspectiveMatrix->data[2][3] = 1/d;
     *point3D = *perspectiveMatrix * (*point3D);
    point3D->Set(point3D->GetX()/point3D->GetZ(), point3D->GetY()/point3D->GetZ(), point3D->GetZ());*/
    point3D->Set(point3D->GetX() / (1 + point3D->GetZ() / d), point3D->GetY() / (1 + point3D->GetZ() / d), point3D->GetZ());
}

void ShapeRotatorDlg::Repaint() {
    wxClientDC dcOld(WxPanel2);

    wxBufferedDC dc(&dcOld);
    //wxBufferedDC dc2(&dcOld2);
    int w, h, w2, h2;
    double d = 8;
    Matrix4 finalTransformationMatrix;
    Vector4 startVect, endVect;


    WxPanel2->GetSize(&w, &h);

    //dc2.SetBackground(wxBrush(RGB(255,255,255)));
    //dc2.Clear();
    //dc2.SetDeviceOrigin(w2/2, h2/2);

    //dc.SetBackground(wxBrush(RGB(255,255,255)));
    dc.Clear();
    dc.SetDeviceOrigin(w / 2, h / 2);



    rotAngleV->Set((M_PI * WxSB_RotateX->GetThumbPosition()) / 180.0, (M_PI * WxSB_RotateY->GetThumbPosition()) / 180.0, (M_PI * WxSB_RotateZ->GetThumbPosition()) / -180.0);
    //translationV->Set((WxSB_TranslationX->GetThumbPosition() -50 )/25.0, (WxSB_TranslationY->GetThumbPosition() -50 )/25.0, (WxSB_TranslationZ->GetThumbPosition() -50 )/25.0);
    //    scaleV->Set(((WxSB_ScaleX->GetThumbPosition() +1) )/120.0, ((WxSB_ScaleY->GetThumbPosition() +1) )/120.0, ((WxSB_ScaleZ->GetThumbPosition() +1) )/120.0);

    finalTransformationMatrix =  getRotationMatrix(rotAngleV);

    int x_start_size = x_start.size();

    for (int i = 0; i < x_start_size; ++i) {
        startVect.Set(x_start[i], y_start[i], -z_start[i]);
        endVect.Set(x_end[i], y_end[i], -z_end[i]);
        startVect = finalTransformationMatrix * startVect;
        endVect = finalTransformationMatrix * endVect;
        if (startVect.GetZ() > -d && endVect.GetZ() > -d) {
            setPerspective(&startVect, d);
            setPerspective(&endVect, d);
            dc.SetPen(wxPen(wxColour(R.at(i), G.at(i), B.at(i))));
            startVect.Set(startVect.GetX() * w / 2, startVect.GetY() * h / 2, startVect.GetZ());
            endVect.Set(endVect.GetX() * w / 2, endVect.GetY() * h / 2, endVect.GetY());
            dc.DrawLine(startVect.GetX(), -startVect.GetY(), endVect.GetX(), -endVect.GetY());
        }
    }

}
//MY CODE END

/*
 * WxPanelUpdateUI
 */

void ShapeRotatorDlg::WxPanelUpdateUI(wxUpdateUIEvent& event) {
    // Repaint();
}

/*
 * WxSB_TranslacjaXScroll
 */
/*void ShapeRotatorDlg::WxSB_TranslationXScroll(wxScrollEvent& event)
{
 wxString str;
// str<<(WxSB_TranslationX->GetThumbPosition()-50)/20.0;
 WxST_TranslationX->SetLabel(str);
 Repaint();
}
 */
/*
 * WxSB_TranslationYScroll
 */
/*
void ShapeRotatorDlg::WxSB_TranslationYScroll(wxScrollEvent& event)
{
 wxString str;
 str<<(WxSB_TranslationY->GetThumbPosition()-50)/20.0;
 WxST_TranslationY->SetLabel(str);
 Repaint();
}
 */
/*
 * WxSB_TranslationZScroll
 */

/*void ShapeRotatorDlg::WxSB_TranslationZScroll(wxScrollEvent& event)
{
 wxString str;
 str<<(WxSB_TranslationZ->GetThumbPosition()-50)/20.0;
 WxST_TranslationZ->SetLabel(str);
 Repaint();
}
 */

void ShapeRotatorDlg::WxSB_RotateXScroll(wxScrollEvent& event) {
    wxString str;
    str << (WxSB_RotateX->GetThumbPosition());
    WxST_RotateX->SetLabel(str);
    Repaint();
}

void ShapeRotatorDlg::WxSB_RotateYScroll(wxScrollEvent& event) {
    wxString str;
    str << (WxSB_RotateY->GetThumbPosition());
    WxST_RotateY->SetLabel(str);
    Repaint();
}

void ShapeRotatorDlg::WxSB_RotateZScroll(wxScrollEvent& event) {
    wxString str;
    str << (WxSB_RotateZ->GetThumbPosition());
    WxST_RotateZ->SetLabel(str);
    Repaint();
}

/*
void ShapeRotatorDlg::WxSB_ScaleXScroll(wxScrollEvent& event)
{
 wxString str;
 str<<(WxSB_ScaleX->GetThumbPosition()+1.0)/100.0;
 WxST_ScaleX->SetLabel(str);
 Repaint();	
}


void ShapeRotatorDlg::WxSB_ScaleYScroll(wxScrollEvent& event)
{
 wxString str;
 str<<(WxSB_ScaleY->GetThumbPosition()+1.0)/100.0;
 WxST_ScaleY->SetLabel(str);
 Repaint();
}


void ShapeRotatorDlg::WxSB_ScaleZScroll(wxScrollEvent& event)
{
 wxString str;
 str<<(WxSB_ScaleZ->GetThumbPosition()+1.0)/100.0;
 WxST_ScaleZ->SetLabel(str);
 Repaint();
}
 */


void ShapeRotatorDlg::clear3DData() {
    x_start.clear();
    y_start.clear();
    z_start.clear();
    x_end.clear();
    y_end.clear();
    z_end.clear();
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

    clear3DData();
    
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
    
    Repaint();
    redraw2D();
    if(usingDrawMode == Line)
        drawFloatingLine();
        
    
}

/*
 * WxPanel1UpdateUI0
 */
void ShapeRotatorDlg::WxPanel1UpdateUI0(wxUpdateUIEvent& event) {
    // insert your code here
}
//void ShapeRotatorDlg::Resize(wxSizeEvent& event) {
//    Repaint();
//}
/*
 * WxButton3Click
 */
void ShapeRotatorDlg::WxButton3Click(wxCommandEvent& event) {
    // insert your code here
}
void ShapeRotatorDlg::WxButton2Click(wxCommandEvent& event) {
    clearAll();
}
void ShapeRotatorDlg::clearAll() {
    clear2DData();
    clear3DData();
    drawOn = false;
    cleared = false;
    firstPointDrawn = false;
}
void ShapeRotatorDlg::drawRoteted(wxCommandEvent& event) {
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
    clear3DData();R.clear();G.clear();B.clear();
    
    for(int i = 0; i < max; i++) {
        delete [] result[i];
    }
    
    delete [] result;
    
    for (int i = 0; i < (gr.get_vec_num()) * 3 * (360/gr.get_angle()) ; i++) {
 
        x_start.push_back(rotations[i][0]);
        y_start.push_back(rotations[i][1]);
        z_start.push_back(rotations[i][2]);
        
        x_end.push_back(rotations[i][3]);
        y_end.push_back(rotations[i][4]);
        z_end.push_back(rotations[i][5]);
        
        R.push_back(rotations[i][6]);
        G.push_back(rotations[i][7]);
        B.push_back(rotations[i][8]);
    }
    
    gr.free_2d_arr(rotations);
    Repaint();
}