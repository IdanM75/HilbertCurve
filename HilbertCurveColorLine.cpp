#include "pch.h"
#include "HilbertCurveColorLine.h"
#include <algorithm>
using namespace std;


HilbertCurveColorLine::HilbertCurveColorLine() : HilbertCurveColor() {}

HilbertCurveColorLine::HilbertCurveColorLine(Point startPos, double length, Direction dir)
	: HilbertCurveColor(startPos, length, dir, Color(0, 0, 255)) {
	addColor(Color(0, 180, 255));
	addColor(Color(0, 255, 200));
	addColor(Color(0, 255, 100));
}

HilbertCurveColorLine::~HilbertCurveColorLine() {}

void HilbertCurveColorLine::drawGuiCurve(CDC* pDC) {
	vector<LineWithPos> allLines = getAllLines();
	unsigned int lastJ = NULL;
	unsigned int lastLastJ = NULL;
	double epsilon = 0.0001;
	for (unsigned int i = 0; i < allLines.size(); i++) {
		for (unsigned int j = 0; j < allLines.size(); j++) {
			if (i == 0) {
				if (allLines[j].getPointA().closePoints(Point(getStartPos().getX(), getStartPos().getY() + getLength()), epsilon) ||
					allLines[j].getPointB().closePoints(Point(getStartPos().getX(), getStartPos().getY() + getLength()), epsilon)) {
					allLines[j].drawGuiLine(pDC, getCurveColor(), 3);
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
					allLines[j].drawGuiLine(pDC, getCurveColor(), 3);
					progradeColors(allLines.size());
					lastLastJ = lastJ;
					lastJ = j;
					break;
			}
		}
	}
}

IMPLEMENT_SERIAL(HilbertCurveColorLine, CObject, VERSIONABLE_SCHEMA | 1)
void HilbertCurveColorLine::Serialize(CArchive& ar) {
	HilbertCurve::Serialize(ar);
	colors.Serialize(ar);
}