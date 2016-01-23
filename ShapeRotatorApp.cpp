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

//#define RUN_TESTS

IMPLEMENT_APP(ShapeRotatorDlgApp)

bool ShapeRotatorDlgApp::OnInit()
{
#ifndef RUN_TESTS
	ShapeRotatorDlg* dialog = new ShapeRotatorDlg(NULL);
	SetTopWindow(dialog);
	dialog->Show(true);		
	return true;
#else
        // tutaj dodawajcie swoje testy do wywoływania
        GenerateRotationTest::instance->runTest();
        
        std::cout << "Test run finished. Press eny key to continue...\n";
#endif
}
 
int ShapeRotatorDlgApp::OnExit()
{
	return 0;
}
