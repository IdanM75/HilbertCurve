#include "pch.h"
#include "HilbertCurveColorPoints.h"


HilbertCurveColorPoints::HilbertCurveColorPoints() : HilbertCurveColor() {}

HilbertCurveColorPoints::HilbertCurveColorPoints(Point startPos, double length, Direction dir)
	: HilbertCurveColor(startPos, length, dir, Color(255, 0, 0)) {
	addColor(Color(0, 0, 255));
}

HilbertCurveColorPoints::~HilbertCurveColorPoints() {}

void HilbertCurveColorPoints::drawGuiCurve(CDC* pDC) {
	vector<LineWithPos> allLines = getAllLines();
	unsigned int lastJ = NULL;
	unsigned int lastLastJ = NULL;
	double epsilon = 0.0001;
	COLORREF blackColor = RGB(0, 0, 0);
	for (unsigned int i = 0; i < allLines.size(); i++) {
		for (unsigned int j = 0; j < allLines.size(); j++) {
			if (i == 0) {
				if (allLines[j].getPointA().closePoints(Point(getStartPos().getX(), getStartPos().getY() + getLength()), epsilon) ||
						allLines[j].getPointB().closePoints(Point(getStartPos().getX(), getStartPos().getY() + getLength()), epsilon)) {
					allLines[j].drawGuiLine(pDC, blackColor, 1);
					allLines[j].getPointA().drawGuiPoint(pDC, getCurveColor(), 6, 6);
					allLines[j].getPointB().drawGuiPoint(pDC, getCurveColor(), 6, 6);
					progradeColors(allLines.size());
					lastJ = j;
					break;
				}
			}
			if (((i == 1 && j != lastJ) || (i > 1 && j != lastJ && j != lastLastJ)) &&
					(allLines[j].getPointB().closePoints(allLines[lastJ].getPointB(), epsilon) ||
					allLines[j].getPointA().closePoints(allLines[lastJ].getPointA(), epsilon) ||
					allLines[j].getPointB().closePoints(allLines[lastJ].getPointA(), epsilon) ||
					allLines[j].getPointA().closePoints(allLines[lastJ].getPointB(), epsilon))) {
				allLines[j].drawGuiLine(pDC, blackColor, 1);
				allLines[j].getPointA().drawGuiPoint(pDC, getCurveColor(), 6, 6);
				allLines[j].getPointB().drawGuiPoint(pDC, getCurveColor(), 6, 6);
				progradeColors(allLines.size());
				lastLastJ = lastJ;
				lastJ = j;
				break;
			}
		}
	}
}

IMPLEMENT_SERIAL(HilbertCurveColorPoints, CObject, VERSIONABLE_SCHEMA | 1)
void HilbertCurveColorPoints::Serialize(CArchive& ar) {
	HilbertCurve::Serialize(ar);
	colors.Serialize(ar);
}