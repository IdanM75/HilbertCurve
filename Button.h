#pragma once
#include "pch.h"
#include "Point.h"
#include "Line.h"
#include "ButtonsType.h"
#include <vector>
using namespace std;


class Button {
private:
	Point startPos; // Top left corner
	double width;
	double height;
	LPTSTR str;
	ButtonsType btnType;
	vector<Line> lines;
public:
	// Constructor
	Button(Point startPos, double width, double height, LPTSTR str, ButtonsType btnType);

	// Getters
	Point getStartPos() const;
	double getWidth() const;
	double getHeight() const;
	LPTSTR getStr() const;
	ButtonsType getButtonType() const;

	// Setters
	void setStartPos(const Point& startPos);
	void setWidth(double width);
	void setHeight(double height);
	void setStr(const LPTSTR& str);
	void setButtonType(ButtonsType btnType);

	// Others
	bool isInside(const Point& p) const;
	void drawGuiButton(CDC* pDC);
};