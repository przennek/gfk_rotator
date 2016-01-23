//---------------------------------------------------------------------------
//
// Name:        ShapeRotatorDlg.h
// Author:      Janusz Malinowski
// Created:     2008-10-02 16:16:34
// Description: ShapeRotatorDlg class declaration
//
//---------------------------------------------------------------------------

#ifndef __ShapeRotatorDLG_h__
#define __ShapeRotatorDLG_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/dialog.h>
        #include<vector>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/filedlg.h>
#include <wx/button.h>
#include <wx/scrolbar.h>
#include <wx/stattext.h>
#include <wx/panel.h>
#include <wx/sizer.h>
//#include "vecmat.h"

#include "Drawer3D.h"
////Header Include End
class Vector4;
class Matrix4;
////Dialog Style Start
#undef ShapeRotatorDlg_STYLE
#define ShapeRotatorDlg_STYLE wxCAPTION | wxRESIZE_BORDER | wxSYSTEM_MENU | wxDIALOG_NO_PARENT | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

enum drawMode {
                Line = 0,
                Curve = 1
            };
class Vector4;
class Matrix4;
//class Drawer3D;

class ShapeRotatorDlg : public wxDialog
{
	private:
            bool cleared;
            bool drawOn;
            bool firstPointDrawn;
            int drawX, drawY;
            int mouseMovePosX, mouseMovePosY;
            drawMode usingDrawMode;
            Drawer3D drawer3D;
            Vector4 *rotationVector;
            std::vector <double> daneY, daneX;
		DECLARE_EVENT_TABLE();
		
	public:
		ShapeRotatorDlg(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("ShapeRotator"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = ShapeRotatorDlg_STYLE);
		virtual ~ShapeRotatorDlg();
		void WxButton1Click(wxCommandEvent& event);
		void ShapeRotatorDlgPaint(wxPaintEvent& event);
                void OnKeyDown(wxKeyEvent& event);
		void WxSB_RotateXScroll(wxScrollEvent& event);
		void WxSB_RotateYScroll(wxScrollEvent& event);
		void WxSB_RotateZScroll(wxScrollEvent& event);
		void WxPanel1UpdateUI(wxUpdateUIEvent& event);
                void clear2DData();
                void redraw2D();
		void WxButton2Click(wxCommandEvent& event);
                void WxButton3Click(wxCommandEvent& event);
                void mouseLeftClick(wxMouseEvent& event);
                void mouseRightClick(wxMouseEvent& event);
                void mouseMotion(wxMouseEvent& event);
                void drawLine(wxMouseEvent& event);
                void drawRoteted(wxCommandEvent& event);
                void drawFloatingLine();
                void updateMouseMovePos(wxMouseEvent& event); 
                void searchNearVertex(wxMouseEvent& event);
                void clearAll();
                void drawCurve(wxMouseEvent& event);
                void OnScroll();
                void connectKeyDownEvent(wxWindow* pclComponent);
	
	private:
		//Do not add custom control declarations between 
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxFileDialog *WxSaveFileDialog1;
		wxButton *WxButton3;
		wxButton *WxButton2;
		wxButton *WxButton1;
		wxStaticText *WxST_RotateZ;
		wxScrollBar *WxSB_RotateZ;
		wxStaticText *WxStaticText3;
		wxBoxSizer *WxBoxSizer5;
		wxStaticText *WxST_RotateY;
		wxScrollBar *WxSB_RotateY;
		wxStaticText *WxStaticText2;
		wxBoxSizer *WxBoxSizer4;
		wxStaticText *WxST_RotateX;
		wxScrollBar *WxSB_RotateX;
		wxStaticText *WxStaticText1;
		wxBoxSizer *WxBoxSizer3;
		wxBoxSizer *WxBoxSizer2;
		wxPanel *WxPanel2;
		wxPanel *WxPanel1;
		wxBoxSizer *WxBoxSizer1;
		////GUI Control Declaration End
                wxBufferedDC WxPanel2Buff;
		
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_WXBUTTON3 = 1052,
			ID_WXBUTTON2 = 1051,
			ID_WXBUTTON1 = 1050,
			ID_WXST_ROTATEZ = 1032,
			ID_WXSB_ROTATEZ = 1015,
			ID_WXSTATICTEXT3 = 1013,
			ID_WXST_ROTATEY = 1031,
			ID_WXSB_ROTATEY = 1014,
			ID_WXSTATICTEXT2 = 1012,
			ID_WXST_ROTATEX = 1030,
			ID_WXSB_ROTATEX = 1009,
			ID_WXSTATICTEXT1 = 1008,
			ID_WXPANEL2 = 1053,
			ID_WXPANEL1 = 1049,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
	
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
