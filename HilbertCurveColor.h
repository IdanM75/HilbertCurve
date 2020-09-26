#pragma once
#include "pch.h"
#include "HilbertCurve.h"
#include "ColorsGradient.h"


class HilbertCurveColor : public HilbertCurve {
protected:
	ColorsGradient colors;
public:
	// Constructors and Destructor
	HilbertCurveColor(); // Empty constructor is necessary for the serialization
	HilbertCurveColor(Point startPos, double length, Direction dir, Color firstColor);
	~HilbertCurveColor();

	// Getters
	ColorsGradient getColors() const;
	COLORREF getCurveColor() const;

	// Other
	virtual void drawGuiCurve(CDC* pDC) = 0;
	void progradeColors(int amount = 255);
	void addColor(Color c);
};