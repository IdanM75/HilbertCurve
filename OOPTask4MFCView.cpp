
// OOPTask4MFCView.cpp : implementation of the COOPTask4MFCView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OOPTask4MFC.h"
#endif
#include <vector>
using namespace std;

#include "OOPTask4MFCDoc.h"
#include "OOPTask4MFCView.h"
#include "Point.h"
#include "Line.h"
#include "Curve.h"
#include "HilbertCurve.h"
#include "HilbertCurveColorLine.h"
#include "HilbertCurveColorPoints.h"
#include "TriangleHilbertCurve.h"
#include "ButtonsType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COOPTask4MFCView

IMPLEMENT_DYNCREATE(COOPTask4MFCView, CView)

BEGIN_MESSAGE_MAP(COOPTask4MFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
//	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// COOPTask4MFCView construction/destruction

COOPTask4MFCView::COOPTask4MFCView() noexcept
{
	// TODO: add construction code here
	Button addHilbertCurve(Point(50, 10), 300, 40, L"Add Hilbert Curve", ButtonsType::addHilbertCurve);
	Button addHilbertCurveColorLine(Point(400, 10), 300, 40, L"Add Hilbert Curve With Color Lines", ButtonsType::addHilbertCurveColorLines);
	Button addHilbertCurveColorPoints(Point(750, 10), 300, 40, L"Add Hilbert Curve With Color Dots", ButtonsType::addHilbertCurveColorPoints);
	Button addTriangleHilbertCurve(Point(1100, 10), 300, 40, L"Add Triangle Hilbert Curve", ButtonsType::addTriangleHilbertCurve);
	buttons.push_back(addHilbertCurve);
	buttons.push_back(addHilbertCurveColorLine);
	buttons.push_back(addHilbertCurveColorPoints);
	buttons.push_back(addTriangleHilbertCurve);

	Button deleteHilbertCurve(Point(50, 60), 300, 40, L"Delete Hilbert Curve", ButtonsType::deleteHilbertCurve);
	Button deleteHilbertCurveColorLine(Point(400, 60), 300, 40, L"Delete Hilbert Curve With Color Lines", ButtonsType::deleteHilbertCurveColorLine);
	Button deleteHilbertCurveColorPoints(Point(750, 60), 300, 40, L"Delete Hilbert Curve With Color Dots", ButtonsType::deleteHilbertCurveColorPoints);
	Button deleteTriangleHilbertCurve(Point(1100, 60), 300, 40, L"Delete Triangle Hilbert Curve", ButtonsType::deleteTriangleHilbertCurve);
	buttons.push_back(deleteHilbertCurve);
	buttons.push_back(deleteHilbertCurveColorLine);
	buttons.push_back(deleteHilbertCurveColorPoints);
	buttons.push_back(deleteTriangleHilbertCurve);

	Button saveState(Point(50, 790), 650, 40, L"Save The Current State", ButtonsType::saveState);
	Button loadState(Point(750 , 790), 650, 40, L"Load The Last State", ButtonsType::loadState);
	buttons.push_back(saveState);
	buttons.push_back(loadState);
}

COOPTask4MFCView::~COOPTask4MFCView() {}

BOOL COOPTask4MFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COOPTask4MFCView drawing

void COOPTask4MFCView::OnDraw(CDC* pDC)
{
	COOPTask4MFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	for (unsigned int i = 0; i < hc.size(); i++) {
		hc[i].drawGuiCurve(pDC);
	}
	for (unsigned int i = 0; i < hccl.size(); i++) {
		hccl[i].drawGuiCurve(pDC);
	}
	for (unsigned int i = 0; i < hccp.size(); i++) {
		hccp[i].drawGuiCurve(pDC);
	}
	for (unsigned int i = 0; i < thc.size(); i++) {
		thc[i].drawGuiCurve(pDC);
	}

	for (unsigned int i = 0; i < buttons.size(); i++) {
		buttons[i].drawGuiButton(pDC);
	}
}


// COOPTask4MFCView printing

BOOL COOPTask4MFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COOPTask4MFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COOPTask4MFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COOPTask4MFCView diagnostics

#ifdef _DEBUG
void COOPTask4MFCView::AssertValid() const
{
	CView::AssertValid();
}

void COOPTask4MFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COOPTask4MFCDoc* COOPTask4MFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COOPTask4MFCDoc)));
	return (COOPTask4MFCDoc*)m_pDocument;
}
#endif //_DEBUG


// COOPTask4MFCView message handlers

void COOPTask4MFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	bool isScreenChanged = false;

	for (unsigned int i = 0; i < hc.size(); i++) {
		if (hc[i].isInside(Point(point.x, point.y)) && hc[i].getLevel() < hc[i].maxLevel) {
			isScreenChanged = true;
			hc[i].develop();
		}
	}
	for (unsigned int i = 0; i < hccl.size(); i++) {
		if (hccl[i].isInside(Point(point.x, point.y)) && hccl[i].getLevel() < hccl[i].maxLevel) {
			isScreenChanged = true;
			hccl[i].develop();
		}
	}
	for (unsigned int i = 0; i < hccp.size(); i++) {
		if (hccp[i].isInside(Point(point.x, point.y)) && hccp[i].getLevel() < hccp[i].maxLevel) {
			isScreenChanged = true;
			hccp[i].develop();
		}
	}
	for (unsigned int i = 0; i < thc.size(); i++) {
		if (thc[i].isInside(Point(point.x, point.y)) && thc[i].getLevel() < thc[i].maxLevel) {
			isScreenChanged = true;
			thc[i].develop();
		}
	}

	for (unsigned int i = 0; i < buttons.size(); i++) {
		if (buttons[i].isInside(Point(point.x, point.y))) {
			switch (buttons[i].getButtonType()) {
			case ButtonsType::addHilbertCurve: {
				if (hc.size() < 2) {
					HilbertCurve hcObj(Point(50, 130 + (330 * hc.size())), 300, Direction::down);
					hcObj.maxLevel = 5;
					hc.push_back(hcObj);
					isScreenChanged = true;
				}
				break;
			}
			case ButtonsType::addHilbertCurveColorLines: {
				if (hccl.size() < 2) {
					HilbertCurveColorLine hcclObj(Point(400, 130 + (330 * hccl.size())), 300, Direction::down);
					hcclObj.maxLevel = 4;
					hccl.push_back(hcclObj);
					isScreenChanged = true;
				}
				break;
			}
			case ButtonsType::addHilbertCurveColorPoints: {
				if (hccp.size() < 2) {
					HilbertCurveColorPoints hccpObj(Point(750, 130 + (330 * hccp.size())), 300, Direction::down);
					hccpObj.maxLevel = 4;
					hccp.push_back(hccpObj);
					isScreenChanged = true;
				}
				break;
			}
			case ButtonsType::addTriangleHilbertCurve: {
				if (thc.size() < 2) {
					TriangleHilbertCurve thcObj(Point(1100, 130 + (330 * thc.size())), 300, Direction::up, Direction::left);
					thcObj.maxLevel = 4;
					thc.push_back(thcObj);
					isScreenChanged = true;
				}
				break;
			}
			case ButtonsType::deleteHilbertCurve: {
				if (hc.size() > 0) {
					hc.pop_back();
					isScreenChanged = true;
				}
				break;
			}
			case ButtonsType::deleteHilbertCurveColorLine: {
				if (hccl.size() > 0) {
					hccl.pop_back();
					isScreenChanged = true;
				}
				break;
			}
			case ButtonsType::deleteHilbertCurveColorPoints: {
				if (hccp.size() > 0) {
					hccp.pop_back();
					isScreenChanged = true;
				}
				break;
			}
			case ButtonsType::deleteTriangleHilbertCurve: {
				if (thc.size() > 0) {
					thc.pop_back();
					isScreenChanged = true;
				}
				break;
			}
			case ButtonsType::saveState: {
				UpdateData(TRUE);
				CFile file;
				file.Open(L"HilberCurvesState.hse", CFile::modeCreate | CFile::modeWrite);
				CArchive ar(&file, CArchive::store);
				ar << hc.size();
				for (unsigned int i = 0; i < hc.size(); i++) {
					hc[i].Serialize(ar);
				}
				ar << hccl.size();
				for (unsigned int i = 0; i < hccl.size(); i++) {
					hccl[i].Serialize(ar);
				}
				ar << hccp.size();
				for (unsigned int i = 0; i < hccp.size(); i++) {
					hccp[i].Serialize(ar);
				}
				ar << thc.size();
				for (unsigned int i = 0; i < thc.size(); i++) {
					thc[i].Serialize(ar);
				}
				ar.Close();
				break;
			}
			case ButtonsType::loadState: {
				UpdateData(TRUE);
				CFile file;
				file.Open(L"HilberCurvesState.hse", CFile::modeRead);
				CArchive ar(&file, CArchive::load);
				hc.clear();
				hccl.clear();
				hccp.clear();
				thc.clear();
				unsigned int tempHcSize;
				ar >> tempHcSize;
				for (unsigned int i = 0; i < tempHcSize; i++) {
					HilbertCurve tempHc;
					tempHc.Serialize(ar);
					hc.push_back(tempHc);
				}
				unsigned int tempHcclSize;
				ar >> tempHcclSize;
				for (unsigned int i = 0; i < tempHcclSize; i++) {
					HilbertCurveColorLine tempHccl;
					tempHccl.Serialize(ar);
					hccl.push_back(tempHccl);
				}
				unsigned int tempHccpSize;
				ar >> tempHccpSize;
				for (unsigned int i = 0; i < tempHccpSize; i++) {
					HilbertCurveColorPoints tempHccp;
					tempHccp.Serialize(ar);
					hccp.push_back(tempHccp);
				}
				unsigned int tempThcSize;
				ar >> tempThcSize;
				for (unsigned int i = 0; i < tempThcSize; i++) {
					TriangleHilbertCurve tempThc;
					tempThc.Serialize(ar);
					thc.push_back(tempThc);
				}
				ar.Close();
				file.Close();
				UpdateData(FALSE);
				isScreenChanged = true;
				break;
			}
			}
		}
	}

	if (isScreenChanged) {
		RedrawWindow();
		CView::OnLButtonDown(nFlags, point);
	}
}