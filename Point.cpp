#include "pch.h"
#include "Point.h"


Point::Point() : x{ 0 }, y{ 0 } {}

Point::Point(double px, double py) : x{ px }, y{ py } {}

Point::Point(const Point& p) : x{ p.getX() }, y{ p.getY() } {}

double Point::getX() const { return x; }

double Point::getY() const { return y; }

void Point::setX(double px) { x = px; }

void Point::setY(double py) { y = py; }

bool Point::closePoints(Point b, double epsilon) {
	if ((getX() - b.getX() <= epsilon && getX() - b.getX() >= -epsilon) &&
		(getY() - b.getY() <= epsilon && getY() - b.getY() >= -epsilon)) {
		return true;
	}
	return false;
}

void Point::drawGuiPoint(CDC* pDC) {
	COLORREF pointColor = RGB(0, 0, 0);
	CPen pointPen(PS_SOLID, 3, pointColor);
	pDC->SelectObject(&pointPen);
	pDC->Ellipse((int)(getX() - 1), (int)(getY() - 1), (int)(getX() + 1), (int)(getY() + 1));
}

void Point::drawGuiPoint(CDC* pDC, COLORREF pointColor, int thickness, double size) {
	CPen pointPen(PS_SOLID, thickness, pointColor);
	pDC->SelectObject(&pointPen);
	pDC->Ellipse((int)(getX() - (size /2)), (int)(getY() - (size / 2)), (int)(getX() + (size / 2)), (int)(getY() + (size / 2)));
}

const Point& Point::operator=(const Point& p) {
	x = p.getX();
	y = p.getY();
	return *this;
}

ostream& operator<<(ostream& os, const Point& p) {
	os << "Point(" << p.getX() << ", " << p.getY() << ")";
	return os;
}

bool operator==(const Point& a, const Point& b) {
	if (a.getX() == b.getX() && a.getY() == b.getY()) { return true; }
	return false;	
}

IMPLEMENT_SERIAL(Point, CObject, VERSIONABLE_SCHEMA | 1)
void Point::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		ar << x << y;
	}
	else {
		ar >> x >> y;
	}
}
