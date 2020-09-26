#pragma once
#include "pch.h"
#include "HilbertCurveColor.h"
#include <math.h>

class HilbertCurveColorPoints : public HilbertCurveColor {
public:
	// Constructors and Destructor
	HilbertCurveColorPoints(); // Empty constructor is necessary for the serialization
	HilbertCurveColorPoints(Point startPos, double length, Direction dir);
	~HilbertCurveColorPoints();

	// Other
	void drawGuiCurve(CDC* pDC) override;

	// Serialization
	DECLARE_SERIAL(HilbertCurveColorPoints);
	void Serialize(CArchive& ar);
};