#pragma once
#include "pch.h"
#include "HilbertCurveColor.h"
#include <math.h>

class HilbertCurveColorLine : public HilbertCurveColor{
public:
	// Constructors and Destructor
	HilbertCurveColorLine(); // Empty constructor is necessary for the serialization
	HilbertCurveColorLine(Point startPos, double length, Direction dir);
	~HilbertCurveColorLine();

	// Other
	void drawGuiCurve(CDC* pDC) override;

	// Serialization
	DECLARE_SERIAL(HilbertCurveColorLine);
	void Serialize(CArchive& ar);
};