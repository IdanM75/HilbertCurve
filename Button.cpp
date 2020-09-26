#include "pch.h"
#include "Button.h"


Button::Button(Point startPos, double width, double height, LPTSTR str, ButtonsType btnType) :
	startPos{ startPos }, width{ width }, height{ height }, str{ str }, btnType{ btnType } {
	Line upLine(Point(getStartPos().getX(), getStartPos().getY()),
		Point(getStartPos().getX() + getWidth(), getStartPos().getY()));
	Line rightLine(Point(getStartPos().getX() + getWidth(), getStartPos().getY()),
		Point(getStartPos().getX() + getWidth(), getStartPos().getY() + getHeight()));
	Line downLine(Point(getStartPos().getX(), getStartPos().getY() + getHeight()),
		Point(getStartPos().getX() + getWidth(), getStartPos().getY() + getHeight()));
	Line leftLine(Point(getStartPos().getX(), getStartPos().getY()),
		Point(getStartPos().getX(), getStartPos().getY() + getHeight()));
	lines.push_back(upLine);
	lines.push_back(rightLine);
	lines.push_back(downLine);
	lines.push_back(leftLine);
}

Point Button::getStartPos() const { return startPos; }

double Button::getWidth() const { return width; }

double Button::getHeight() const { return height; }

LPTSTR Button::getStr() const { return str; }

ButtonsType Button::getButtonType() const { return btnType; }

void Button::setStartPos(const Point& startPos) { this->startPos = startPos; }

void Button::setWidth(double width) { this->width = width; }

void Button::setHeight(double height) { this->height = height; }

void Button::setStr(const LPTSTR& str) { this->str = str; }

void Button::setButtonType(ButtonsType btnType) { this->btnType = btnType; }

bool Button::isInside(const Point& p) const {
	if ((p.getX() >= getStartPos().getX() && p.getX() <= getStartPos().getX() + getWidth()) &&
		(p.getY() >= getStartPos().getY() && p.getY() <= getStartPos().getY() + getHeight())) return true;
	return false;
}

void Button::drawGuiButton(CDC* pDC) {
	for (unsigned int i = 0; i < lines.size(); i++) {
		lines[i].drawGuiLine(pDC);
	}

	pDC->TextOut((int)(getStartPos().getX() + 5), (int)(getStartPos().getY() + (getHeight() / 4)), str);
}