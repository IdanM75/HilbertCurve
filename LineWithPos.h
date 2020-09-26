#pragma once
#include "Line.h"
#include "CartesianDirections.h"


class LineWithPos : public Line {
private:
	Direction dir;
public:
	// Constructors and Destructor
	LineWithPos(); // Empty constructor is necessary for the serialization, don't use it
	LineWithPos(Point a, Point b, Direction dir);

	// Getters
	Direction getDir() const;

	// Setters
	void setDir(Direction dir);

	// Serialization
	DECLARE_SERIAL(LineWithPos);
	void Serialize(CArchive& ar);
};