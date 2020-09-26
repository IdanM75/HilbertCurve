#pragma once
#include <iostream>
using namespace std;


class Point : public CObject {
private:
	double x;
	double y;
public:
	// Constructors
	Point(void); // Empty constructor is necessary for the serialization
	Point(double x, double y);
	Point(const Point& p);

	// Getters
	double getX() const;
	double getY() const;

	// Setters
	void setX(double x);
	void setY(double y);

	// Other
	bool closePoints(Point b, double epsilon);
	void drawGuiPoint(CDC* pDC);
	void drawGuiPoint(CDC* pDC, COLORREF pointColor, int thickness, double size);

	// Overloaded
	const Point& operator=(const Point& p);
	friend ostream& operator<<(ostream& os, const Point& p);
	friend bool operator==(const Point& a, const Point& b);

	// Serialization
	DECLARE_SERIAL(Point);
	void Serialize(CArchive& ar);
};
