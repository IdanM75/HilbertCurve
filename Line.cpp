#include "pch.h"
#include "Line.h"


Line::Line() {}

Line::Line(Point pa, Point pb) : a{ pa }, b{ pb } {}	

Line::Line(const Line& l) : a{ l.getPointA() }, b{ l.getPointB() } {}

Point Line::getPointA() const { return a; }

Point Line::getPointB() const { return b; }

void Line::setPointA(Point pa) { a = pa; }

void Line::setPointB(Point pb) { b = pb; }

void Line::drawGuiLine(CDC* pDC) {
	COLORREF lineColor = RGB(0, 0, 0);
	CPen linePen(PS_SOLID, 2, lineColor);
	pDC->SelectObject(&linePen);
	pDC->MoveTo((int)(getPointA().getX()), (int)(getPointA().getY()));
	pDC->LineTo((int)(getPointB().getX()), (int)(getPointB().getY()));
}

void Line::drawGuiLine(CDC* pDC, COLORREF lineColor, int thickness) {
	CPen linePen(PS_SOLID, thickness, lineColor);
	pDC->SelectObject(&linePen);
	pDC->MoveTo((int)(getPointA().getX()), (int)(getPointA().getY()));
	pDC->LineTo((int)(getPointB().getX()), (int)(getPointB().getY()));
}

const Line& Line::operator=(const Line& l) {
	a = l.getPointA();
	b = l.getPointB();
	return *this;
}

IMPLEMENT_SERIAL(Line, CObject, VERSIONABLE_SCHEMA | 1)
void Line::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		a.Serialize(ar);
		b.Serialize(ar);
	}
	else {
		a.Serialize(ar);
		b.Serialize(ar);
	}
}
