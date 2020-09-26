#include "pch.h"
#include "HilbertCurveColor.h"
#include <algorithm>
using namespace std;


HilbertCurveColor::HilbertCurveColor() : HilbertCurve() {}

HilbertCurveColor::HilbertCurveColor(Point startPos, double length, Direction dir, Color firstColor)
	: HilbertCurve(startPos, length, dir), colors(firstColor) {}

HilbertCurveColor::~HilbertCurveColor() {}

ColorsGradient HilbertCurveColor::getColors() const { return colors; }

COLORREF HilbertCurveColor::getCurveColor() const { 
	return RGB(colors.getColor().getRed(), colors.getColor().getGreen(), colors.getColor().getBlue());
}

void HilbertCurveColor::progradeColors(int amount) { colors.prograde(amount); }

void HilbertCurveColor::addColor(Color c) { colors.addColor(c); }
