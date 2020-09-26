
// OOPTask4MFC.h : main header file for the OOPTask4MFC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COOPTask4MFCApp:
// See OOPTask4MFC.cpp for the implementation of this class
//

class COOPTask4MFCApp : public CWinApp
{
public:
	COOPTask4MFCApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COOPTask4MFCApp theApp;
