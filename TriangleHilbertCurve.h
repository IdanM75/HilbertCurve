#pragma once
#include "Curve.h"
#include "LineWithPos.h"
#include "CartesianDirections.h"


class TriangleHilbertCurve : public Curve<TriangleHilbertCurve, LineWithPos> {
private:
	Direction horDir;
	Direction verDir;
	double triRatio = 1.0/3;
protected:
	void developUpRightCurves(double blockSize, Point downLeftStartPos, Point downMiddleStartPos,
		Point downRightStartPos, Point upMiddleStartPos);
	void developDownRightCurves(double blockSize, Point upLeftStartPos, Point upMiddleStartPos,
		Point upRightStartPos, Point downMiddleStartPos);
	void developUpLeftCurves(double blockSize, Point downLeftStartPos, Point downMiddleStartPos,
		Point downRightStartPos, Point upMiddleStartPos);
	void developDownLeftCurves(double blockSize, Point upLeftStartPos, Point upMiddleStartPos,
		Point upRightStartPos, Point downMiddleStartPos);
	void developUpRightLines(double length, double blockSize, double dividedLength);
	void developDownRightLines(double length, double blockSize, double dividedLength);
	void developUpLeftLines(double length, double blockSize, double dividedLength);
	void developDownLeftLines(double length, double blockSize, double dividedLength);
public:
	// Constructors and Destructor
	TriangleHilbertCurve(); // Empty constructor is necessary for the serialization, don't use it
	TriangleHilbertCurve(Point startPos, double length, Direction horDir, Direction verDir);
	~TriangleHilbertCurve();

	// Getters
	Direction getHorDir() const;
	Direction getVerDir() const;

	// Setters
	void setHorDir(Direction d);
	void setVerDir(Direction d);

	// Others
	bool isInside(const Point& p) const override;
	double static isInsideHelpFunc(Point p1, Point p2, Point p3);
	void develop() override;

	// Serialization
	DECLARE_SERIAL(TriangleHilbertCurve);
	void Serialize(CArchive& ar);
};