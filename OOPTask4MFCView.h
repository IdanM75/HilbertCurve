
// OOPTask4MFCView.h : interface of the COOPTask4MFCView class
//

#pragma once

#include "HilbertCurve.h"
#include "HilbertCurveColorLine.h"
#include "HilbertCurveColorPoints.h"
#include "TriangleHilbertCurve.h"
#include "Button.h"
#include <vector>
using namespace std;

class COOPTask4MFCView : public CView
{
protected: // create from serialization only
	COOPTask4MFCView() noexcept;
	DECLARE_DYNCREATE(COOPTask4MFCView)

// Attributes
public:
	COOPTask4MFCDoc* GetDocument() const;
	vector<HilbertCurve> hc;
	vector<HilbertCurveColorLine> hccl;
	vector<HilbertCurveColorPoints> hccp;
	vector<TriangleHilbertCurve> thc;
	vector<Button> buttons;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~COOPTask4MFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in OOPTask4MFCView.cpp
inline COOPTask4MFCDoc* COOPTask4MFCView::GetDocument() const
   { return reinterpret_cast<COOPTask4MFCDoc*>(m_pDocument); }
#endif

