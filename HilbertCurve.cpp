#include "pch.h"
#include "HilbertCurve.h"
#include <math.h>
using namespace std;


HilbertCurve::HilbertCurve() : Curve(), dir{ Direction::down } {}

HilbertCurve::HilbertCurve(Point startPos, double length, Direction dir)
	: Curve<HilbertCurve, LineWithPos>(startPos, length), dir{ dir } {
	LineWithPos upLine(Point(getStartPos().getX(), getStartPos().getY()),
		Point(getStartPos().getX() + getLength(), getStartPos().getY()),
		Direction::up);
	LineWithPos rightLine(Point(getStartPos().getX() + getLength(), getStartPos().getY()),
		Point(getStartPos().getX() + getLength(), getStartPos().getY() + getLength()),
		Direction::right);
	LineWithPos downLine(Point(getStartPos().getX(), getStartPos().getY() + getLength()),
		Point(getStartPos().getX() + getLength(), getStartPos().getY() + getLength()),
		Direction::down);
	LineWithPos leftLine(Point(getStartPos().getX(), getStartPos().getY()),
		Point(getStartPos().getX(), getStartPos().getY() + getLength()),
		Direction::left);
	if (dir == Direction::up) {
		addLine(rightLine);
		addLine(downLine);
		addLine(leftLine);
	}
	else if (dir == Direction::right) {
		addLine(downLine);
		addLine(leftLine);
		addLine(upLine);
	}
	else if (dir == Direction::down) {
		addLine(leftLine);
		addLine(upLine);
		addLine(rightLine);
	}
	else if (dir == Direction::left) {
		addLine(upLine);
		addLine(rightLine);
		addLine(downLine);
	}
}

HilbertCurve::~HilbertCurve() {}

Direction HilbertCurve::getDir() const { return dir; }

void HilbertCurve::setDir(Direction d) { dir = d; }

bool HilbertCurve::isInside(const Point& p) const {
	if ((p.getX() >= getStartPos().getX() && p.getX() <= getStartPos().getX() + getLength()) &&
		(p.getY() >= getStartPos().getY() && p.getY() <= getStartPos().getY() + getLength())) return true;
	return false;
}

void HilbertCurve::develop() {
	double length = getLength();
	int division = (int)((4 * pow(2, getLevel())) - 1);
	double blockSize = length * (((double)(division - 1) / 2) / division);
	double dividedLength = (length / division);
	Point upLeftStartPos(getStartPos().getX(), getStartPos().getY());
	Point upRightStartPos(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY());
	Point downLeftStartPos(getStartPos().getX(), getStartPos().getY() + blockSize + dividedLength);
	Point dowRightStartPos(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + blockSize + dividedLength);
	if (getLevel() == 0) {
		if (dir == Direction::up) 
			developUpCurves(blockSize, upLeftStartPos, upRightStartPos, downLeftStartPos, dowRightStartPos);
		if (dir == Direction::right)
			developRightCurves(blockSize, upLeftStartPos, upRightStartPos, downLeftStartPos, dowRightStartPos);
		if (dir == Direction::down)
			developDownCurves(blockSize, upLeftStartPos, upRightStartPos, downLeftStartPos, dowRightStartPos);
		if (dir == Direction::left)
			developLeftCurves(blockSize, upLeftStartPos, upRightStartPos, downLeftStartPos, dowRightStartPos);
	}
	else {
		for (unsigned int i = 0; i < getCurves().size(); i++) {
			getCurve(i).setLength(blockSize);
			if (i == 0) getCurve(i).setStartPos(upLeftStartPos);
			if (i == 1) getCurve(i).setStartPos(upRightStartPos);
			if (i == 2) getCurve(i).setStartPos(downLeftStartPos);
			if (i == 3) getCurve(i).setStartPos(dowRightStartPos);
			getCurve(i).develop();
		}
	}
	clearLines();
	if (dir == Direction::up) developUpLines(length, blockSize, dividedLength);
	if (dir == Direction::right) developRightLines(length, blockSize, dividedLength);
	if (dir == Direction::down) developDownLines(length, blockSize, dividedLength);
	if (dir == Direction::left) developLeftLines(length, blockSize, dividedLength);
	setLevel(getLevel() + 1);
}

void HilbertCurve::developUpCurves(double blockSize, Point upLeftStartPos, Point upRightStartPos,
	Point downLeftStartPos, Point dowRightStartPos) {
	HilbertCurve upLeft(upLeftStartPos, blockSize, Direction::left);
	HilbertCurve upRight(upRightStartPos, blockSize, Direction::right);
	HilbertCurve downLeft(downLeftStartPos, blockSize, Direction::up);
	HilbertCurve downRight(dowRightStartPos, blockSize, Direction::up);
	addCurve(upLeft);
	addCurve(upRight);
	addCurve(downLeft);
	addCurve(downRight);
}

void HilbertCurve::developRightCurves(double blockSize, Point upLeftStartPos, Point upRightStartPos,
	Point downLeftStartPos, Point dowRightStartPos) {
	HilbertCurve upLeft(upLeftStartPos, blockSize, Direction::right);
	HilbertCurve upRight(upRightStartPos, blockSize, Direction::up);
	HilbertCurve downLeft(downLeftStartPos, blockSize, Direction::right);
	HilbertCurve downRight(dowRightStartPos, blockSize, Direction::down);
	addCurve(upLeft);
	addCurve(upRight);
	addCurve(downLeft);
	addCurve(downRight);
}

void HilbertCurve::developDownCurves(double blockSize, Point upLeftStartPos, Point upRightStartPos,
	Point downLeftStartPos, Point dowRightStartPos) {
	HilbertCurve upLeft(upLeftStartPos, blockSize, Direction::down);
	HilbertCurve upRight(upRightStartPos, blockSize, Direction::down);
	HilbertCurve downLeft(downLeftStartPos, blockSize, Direction::left);
	HilbertCurve downRight(dowRightStartPos, blockSize, Direction::right);
	addCurve(upLeft);
	addCurve(upRight);
	addCurve(downLeft);
	addCurve(downRight);
}

void HilbertCurve::developLeftCurves(double blockSize, Point upLeftStartPos, Point upRightStartPos, 
	Point downLeftStartPos, Point dowRightStartPos) {
	HilbertCurve upLeft(upLeftStartPos, blockSize, Direction::up);
	HilbertCurve upRight(upRightStartPos, blockSize, Direction::left);
	HilbertCurve downLeft(downLeftStartPos, blockSize, Direction::down);
	HilbertCurve downRight(dowRightStartPos, blockSize, Direction::left);
	addCurve(upLeft);
	addCurve(upRight);
	addCurve(downLeft);
	addCurve(downRight);
}

void HilbertCurve::developUpLines(double length, double blockSize, double dividedLength) {
	LineWithPos rightLine(Point(getStartPos().getX() + length, getStartPos().getY() + blockSize),
		Point(getStartPos().getX() + length, getStartPos().getY() + blockSize + dividedLength),
		Direction::right);
	LineWithPos downLine(Point(getStartPos().getX() + blockSize, getStartPos().getY() + blockSize + dividedLength),
		Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + blockSize + dividedLength),
		Direction::down);
	LineWithPos leftLine(Point(getStartPos().getX(), getStartPos().getY() + blockSize),
		Point(getStartPos().getX(), getStartPos().getY() + blockSize + dividedLength),
		Direction::left);
	addLine(rightLine);
	addLine(downLine);
	addLine(leftLine);
}

void HilbertCurve::developRightLines(double length, double blockSize, double dividedLength) {
	LineWithPos downLine(Point(getStartPos().getX() + blockSize, getStartPos().getY() + length),
		Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + length),
		Direction::down);
	LineWithPos leftLine(Point(getStartPos().getX() + blockSize, getStartPos().getY() + blockSize),
		Point(getStartPos().getX() + blockSize, getStartPos().getY() + blockSize + dividedLength),
		Direction::left);
	LineWithPos upLine(Point(getStartPos().getX() + blockSize, getStartPos().getY()),
		Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY()),
		Direction::up);
	addLine(downLine);
	addLine(leftLine);
	addLine(upLine);
}

void HilbertCurve::developDownLines(double length, double blockSize, double dividedLength) {
	LineWithPos leftLine(Point(getStartPos().getX(), getStartPos().getY() + blockSize),
		Point(getStartPos().getX(), getStartPos().getY() + blockSize + dividedLength),
		Direction::left);
	LineWithPos upLine(Point(getStartPos().getX() + blockSize, getStartPos().getY() + blockSize),
		Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + blockSize),
		Direction::up);
	LineWithPos rightLine(Point(getStartPos().getX() + length, getStartPos().getY() + blockSize),
		Point(getStartPos().getX() + length, getStartPos().getY() + blockSize + dividedLength),
		Direction::right);
	addLine(leftLine);
	addLine(upLine);
	addLine(rightLine);
}
void HilbertCurve::developLeftLines(double length, double blockSize, double dividedLength) {
	LineWithPos upLine(Point(getStartPos().getX() + blockSize, getStartPos().getY()),
		Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY()),
		Direction::up);
	LineWithPos rightLine(Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + blockSize),
		Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + blockSize + dividedLength),
		Direction::right);
	LineWithPos downLine(Point(getStartPos().getX() + blockSize, getStartPos().getY() + length),
		Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + length),
		Direction::down);
	addLine(upLine);
	addLine(rightLine);
	addLine(downLine);
}

// Need to dive more, inline, AFXAPI, static_cast
inline CArchive& AFXAPI operator <<(CArchive& ar, const Direction& dir)
{
	int tempDir = static_cast<int>(dir);
	ar << tempDir;
	return ar;
}

inline CArchive& AFXAPI operator >>(CArchive& ar, Direction& dir)
{
	int tempDir = 0;
	ar >> tempDir;
	dir = (Direction)tempDir;
	return ar;
}

IMPLEMENT_SERIAL(HilbertCurve, CObject, VERSIONABLE_SCHEMA | 1)
void HilbertCurve::Serialize(CArchive& ar) {
	Curve::Serialize(ar);
	if (ar.IsStoring()) {
		ar << dir;
	}
	else {
		ar >> dir;
	}
}
