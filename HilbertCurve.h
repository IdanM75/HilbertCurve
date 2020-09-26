#pragma once
#include "Curve.h"
#include "CartesianDirections.h"
#include "LineWithPos.h"


class HilbertCurve : public Curve<HilbertCurve, LineWithPos> {
private:
	Direction dir;
protected:
	void developUpCurves(double blockSize, Point upLeftStartPos, Point upRightStartPos,
		Point downLeftStartPos, Point dowRightStartPos);
	void developRightCurves(double blockSize, Point upLeftStartPos, Point upRightStartPos,
		Point downLeftStartPos, Point dowRightStartPos);
	void developDownCurves(double blockSize, Point upLeftStartPos, Point upRightStartPos,
		Point downLeftStartPos, Point dowRightStartPos);
	void developLeftCurves(double blockSize, Point upLeftStartPos, Point upRightStartPos,
		Point downLeftStartPos, Point dowRightStartPos);
	void developUpLines(double length, double blockSize, double dividedLength);
	void developRightLines(double length, double blockSize, double dividedLength);
	void developDownLines(double length, double blockSize, double dividedLength);
	void developLeftLines(double length, double blockSize, double dividedLength);
public:
	// Constructors and Destructor
	HilbertCurve(); // Empty constructor is necessary for the serialization
	HilbertCurve(Point startPos, double length, Direction dir);
	~HilbertCurve();

	// Getters
	Direction getDir() const;

	// Setters
	void setDir(Direction d);

	// Others
	bool isInside(const Point& p) const override;
	void develop() override;

	// Serialization
	DECLARE_SERIAL(HilbertCurve);
	void Serialize(CArchive& ar);
};