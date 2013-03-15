// WhorldFF.h : main header file for the WhorldFF DLL
//

#if !defined(AFX_WHORLDFF_H__943632C4_9EA9_474D_907B_B46E3AB934BD__INCLUDED_)
#define AFX_WHORLDFF_H__943632C4_9EA9_474D_907B_B46E3AB934BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWhorldFF
// See WhorldFF.cpp for the implementation of this class
//

class CWhorldFF : public CWinApp
{
public:
	CWhorldFF();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWhorldFF)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CWhorldFF)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WHORLDFF_H__943632C4_9EA9_474D_907B_B46E3AB934BD__INCLUDED_)
