#pragma once
#include "Point.h"


class Line : public CObject {
private:
	Point a;
	Point b;
public:
	// Constructors
	Line(); // Empty constructor is necessary for the serialization
	Line(Point a, Point b);
	Line(const Line& l);

	// Getters
	Point getPointA() const;
	Point getPointB() const;

	// Setters
	void setPointA(Point a);
	void setPointB(Point b);

	// Overloaded
	const Line& operator=(const Line& l);

	// Others
	void drawGuiLine(CDC* pDC);
	void drawGuiLine(CDC* pDC, COLORREF lineColor, int thickness);

	// Serialization
	DECLARE_SERIAL(Line);
	void Serialize(CArchive& ar);
};