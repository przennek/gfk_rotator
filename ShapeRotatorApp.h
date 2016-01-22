//---------------------------------------------------------------------------
//
// Name:        ShapeRotatorApp.h
// Author:      Laptop_Admin
// Created:     2012-11-14 21:53:51
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __ShapeRotatorDLGApp_h__
#define __ShapeRotatorDLGApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class ShapeRotatorDlgApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
