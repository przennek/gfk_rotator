//---------------------------------------------------------------------------
//
// Name:        ShapeRotatorApp.cpp
// Author:      Laptop_Admin
// Created:     2012-11-14 21:53:51
// Description: 
//
//---------------------------------------------------------------------------

#include "ShapeRotatorApp.h"
#include "ShapeRotatorDlg.h"
#include "GenerateRotationTest.h"



IMPLEMENT_APP(ShapeRotatorDlgApp)

bool ShapeRotatorDlgApp::OnInit()
{

	ShapeRotatorDlg* dialog = new ShapeRotatorDlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);		
	return true;

}
 
int ShapeRotatorDlgApp::OnExit()
{
	return 0;
}
