#include "pch.h"
#include "TriangleHilbertCurve.h"


TriangleHilbertCurve::TriangleHilbertCurve() : Curve(), horDir{ Direction::down }, verDir{ Direction::right } {}

TriangleHilbertCurve::TriangleHilbertCurve(Point startPos, double length, Direction horDir, Direction verDir)
	: Curve(startPos, length), horDir{ horDir }, verDir{ verDir } {
	if (horDir == Direction::up && verDir == Direction::right) {
		LineWithPos	leftLine(Point(getStartPos().getX(), getStartPos().getY() + getLength()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + (getLength() * (1 - triRatio))),
			Direction::left);
		LineWithPos rightLine(Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + (getLength() * (1 - triRatio))),
			Point(getStartPos().getX() + getLength(), getStartPos().getY() + getLength()), Direction::right);
		LineWithPos upLine(Point(getStartPos().getX() + getLength(), getStartPos().getY() + getLength()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY()), Direction::up);
		addLine(leftLine);
		addLine(rightLine);
		addLine(upLine);
	}
	else if (horDir == Direction::down && verDir == Direction::right) {
		LineWithPos	leftLine(Point(getStartPos().getX(), getStartPos().getY()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + (getLength() * triRatio)),
			Direction::left);
		LineWithPos rightLine(Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + (getLength() * triRatio)),
			Point(getStartPos().getX() + getLength(), getStartPos().getY()), Direction::right);
		LineWithPos upLine(Point(getStartPos().getX() + getLength(), getStartPos().getY()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + getLength()), Direction::down);
		addLine(leftLine);
		addLine(rightLine);
		addLine(upLine);
	}
	else if (horDir == Direction::up && verDir == Direction::left) {
		LineWithPos rightLine(Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + (getLength() * (1 - triRatio))),
			Point(getStartPos().getX() + getLength(), getStartPos().getY() + getLength()), Direction::right);
		LineWithPos	leftLine(Point(getStartPos().getX(), getStartPos().getY() + getLength()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + (getLength() * (1 - triRatio))),
			Direction::left);
		LineWithPos upLine(Point(getStartPos().getX(), getStartPos().getY() + getLength()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY()), Direction::up);
		addLine(rightLine);
		addLine(leftLine);
		addLine(upLine);
	}
	else if (horDir == Direction::down && verDir == Direction::left) {
		LineWithPos rightLine(Point(getStartPos().getX() + getLength(), getStartPos().getY()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + (getLength() * triRatio)),
			Direction::right);
		LineWithPos	leftLine(Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + (getLength() * triRatio)),
			Point(getStartPos().getX(), getStartPos().getY()),
			Direction::left);
		LineWithPos downLine(Point(getStartPos().getX(), getStartPos().getY()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + getLength()), Direction::down);
		addLine(rightLine);
		addLine(leftLine);
		addLine(downLine);
	}
}

TriangleHilbertCurve::~TriangleHilbertCurve() {}

Direction TriangleHilbertCurve::getHorDir() const { return horDir; }

Direction TriangleHilbertCurve::getVerDir() const { return verDir; }

void TriangleHilbertCurve::setHorDir(Direction d) { horDir = d; }

void TriangleHilbertCurve::setVerDir(Direction d) { verDir = d; }

bool TriangleHilbertCurve::isInside(const Point& p) const {
	double d1, d2, d3;
	bool hasNeg, hasPos;
	if (horDir == Direction::up) {
		d1 = isInsideHelpFunc(p, Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY()),
			Point(getStartPos().getX(), getStartPos().getY() + getLength()));
		d2 = isInsideHelpFunc(p, Point(getStartPos().getX(), getStartPos().getY() + getLength()),
			Point(getStartPos().getX() + getLength(), getStartPos().getY() + getLength()));
		d3 = isInsideHelpFunc(p, Point(getStartPos().getX() + getLength(), getStartPos().getY() + getLength()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY()));
	}
	if (horDir == Direction::down) {
		d1 = isInsideHelpFunc(p, Point(getStartPos().getX(), getStartPos().getY()),
			Point(getStartPos().getX() + getLength(), getStartPos().getY()));
		d2 = isInsideHelpFunc(p, Point(getStartPos().getX() + getLength(), getStartPos().getY()),
			Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + getLength()));
		d3 = isInsideHelpFunc(p, Point(getStartPos().getX() + (getLength() / 2), getStartPos().getY() + getLength()),
			Point(getStartPos().getX(), getStartPos().getY()));
	}
	hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);
	return !(hasNeg && hasPos);
}

double TriangleHilbertCurve::isInsideHelpFunc(Point p1, Point p2, Point p3) {
	return (p1.getX() - p3.getX()) * (p2.getY() - p3.getY()) - (p2.getX() - p3.getX()) * (p1.getY() - p3.getY());
}

void TriangleHilbertCurve::develop() {
	double length = getLength();
	int division = (int)((4 * pow(2, getLevel())) - 1);
	double blockSize = length * (((double)(division - 1) / 2) / division);
	double dividedLength = (length / division);
	double limHalfBlock = (blockSize / 2) + (dividedLength / 2);
	if (horDir == Direction::up && verDir == Direction::right) {
		Point downLeftStartPos(getStartPos().getX(), getStartPos().getY() + length - blockSize);
		Point downMiddleStartPos(getStartPos().getX() + limHalfBlock, getStartPos().getY() + blockSize + (dividedLength * (1 - triRatio)));
		Point downRightStartPos(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + length - blockSize);
		Point upMiddleStartPos(getStartPos().getX() + limHalfBlock, getStartPos().getY());
		if (getLevel() == 0) {
			clearLines();
			developUpRightCurves(blockSize, downLeftStartPos, downMiddleStartPos, downRightStartPos, upMiddleStartPos);
			developUpRightLines(length, blockSize, dividedLength);
		}
		else {
			for (unsigned int i = 0; i < getCurves().size(); i++) {
				getCurve(i).setLength(blockSize);
				if (i == 0) getCurve(i).setStartPos(downLeftStartPos);
				if (i == 1) getCurve(i).setStartPos(downMiddleStartPos);
				if (i == 2) getCurve(i).setStartPos(downRightStartPos);
				if (i == 3) getCurve(i).setStartPos(upMiddleStartPos);
				getCurve(i).develop();
			}
		}
	}
	if (horDir == Direction::down && verDir == Direction::right) {
		Point upLeftStartPos(getStartPos().getX(), getStartPos().getY());
		Point upMiddleStartPos(getStartPos().getX() + limHalfBlock, getStartPos().getY() + (dividedLength * triRatio));
		Point upRightStartPos(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY());
		Point downMiddleStartPos(getStartPos().getX() + limHalfBlock, getStartPos().getY() + blockSize + dividedLength);
		if (getLevel() == 0) {
			clearLines();
			developDownRightCurves(blockSize, upLeftStartPos, upMiddleStartPos, upRightStartPos, downMiddleStartPos);
			developDownRightLines(length, blockSize, dividedLength);
		}
		else {
			for (unsigned int i = 0; i < getCurves().size(); i++) {
				getCurve(i).setLength(blockSize);
				if (i == 0) getCurve(i).setStartPos(upLeftStartPos);
				if (i == 1) getCurve(i).setStartPos(upMiddleStartPos);
				if (i == 2) getCurve(i).setStartPos(upRightStartPos);
				if (i == 3) getCurve(i).setStartPos(downMiddleStartPos);
				getCurve(i).develop();
				clearLines();
			}
		}
	}
	if (horDir == Direction::up && verDir == Direction::left) {
		Point downLeftStartPos(getStartPos().getX(), getStartPos().getY() + length - blockSize);
		Point downMiddleStartPos(getStartPos().getX() + limHalfBlock, getStartPos().getY() + blockSize + (dividedLength * (1 - triRatio)));
		Point downRightStartPos(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + length - blockSize);
		Point upMiddleStartPos(getStartPos().getX() + limHalfBlock, getStartPos().getY());
		if (getLevel() == 0) {
			clearLines();
			developUpLeftCurves(blockSize, downLeftStartPos, downMiddleStartPos, downRightStartPos, upMiddleStartPos);
			developUpLeftLines(length, blockSize, dividedLength);
		}
		else {
			for (unsigned int i = 0; i < getCurves().size(); i++) {
				getCurve(i).setLength(blockSize);
				if (i == 0) getCurve(i).setStartPos(downLeftStartPos);
				if (i == 1) getCurve(i).setStartPos(downMiddleStartPos);
				if (i == 2) getCurve(i).setStartPos(downRightStartPos);
				if (i == 3) getCurve(i).setStartPos(upMiddleStartPos);
				getCurve(i).develop();
				clearLines();
			}
		}
	}
	if (horDir == Direction::down && verDir == Direction::left) {
		Point upLeftStartPos(getStartPos().getX(), getStartPos().getY());
		Point upMiddleStartPos(getStartPos().getX() + limHalfBlock, getStartPos().getY() + (dividedLength * triRatio));
		Point upRightStartPos(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY());
		Point downMiddleStartPos(getStartPos().getX() + limHalfBlock, getStartPos().getY() + blockSize + dividedLength);
		if (getLevel() == 0) {
			clearLines();
			developDownLeftCurves(blockSize, upLeftStartPos, upMiddleStartPos, upRightStartPos, downMiddleStartPos);
			developDownLeftLines(length, blockSize, dividedLength);
		}
		else {
			for (unsigned int i = 0; i < getCurves().size(); i++) {
				getCurve(i).setLength(blockSize);
				if (i == 0) getCurve(i).setStartPos(upLeftStartPos);
				if (i == 1) getCurve(i).setStartPos(upMiddleStartPos);
				if (i == 2) getCurve(i).setStartPos(upRightStartPos);
				if (i == 3) getCurve(i).setStartPos(downMiddleStartPos);
				getCurve(i).develop();
				clearLines();
			}
		}
	}
	clearLines();
	if (horDir == Direction::up && verDir == Direction::right) developUpRightLines(length, blockSize, dividedLength);
	if (horDir == Direction::down && verDir == Direction::right) developDownRightLines(length, blockSize, dividedLength);
	if (horDir == Direction::up && verDir == Direction::left) developUpLeftLines(length, blockSize, dividedLength);
	if (horDir == Direction::down && verDir == Direction::left) developDownLeftLines(length, blockSize, dividedLength);
	setLevel(getLevel() + 1);
}

void TriangleHilbertCurve::developUpRightCurves(double blockSize, Point downLeftStartPos, Point downMiddleStartPos,
	Point downRightStartPos, Point upMiddleStartPos) {
	TriangleHilbertCurve downLeft(downLeftStartPos, blockSize, Direction::up, Direction::right);
	TriangleHilbertCurve downMiddle(downMiddleStartPos, blockSize, Direction::down, Direction::right);
	TriangleHilbertCurve downRight(downRightStartPos, blockSize, Direction::up, Direction::right);
	TriangleHilbertCurve upMiddle(upMiddleStartPos, blockSize, Direction::up, Direction::left);
	addCurve(downLeft);
	addCurve(downMiddle);
	addCurve(downRight);
	addCurve(upMiddle);
}

void TriangleHilbertCurve::developDownRightCurves(double blockSize, Point downLeftStartPos, Point downMiddleStartPos,
	Point downRightStartPos, Point upMiddleStartPos) {
	TriangleHilbertCurve upLeft(downLeftStartPos, blockSize, Direction::down, Direction::right);
	TriangleHilbertCurve upMiddle(downMiddleStartPos, blockSize, Direction::up, Direction::right);
	TriangleHilbertCurve upRight(downRightStartPos, blockSize, Direction::down, Direction::right);
	TriangleHilbertCurve downMiddle(upMiddleStartPos, blockSize, Direction::down, Direction::left);
	addCurve(upLeft);
	addCurve(upMiddle);
	addCurve(upRight);
	addCurve(downMiddle);
}

void TriangleHilbertCurve::developUpLeftCurves(double blockSize, Point downLeftStartPos, Point downMiddleStartPos,
	Point downRightStartPos, Point upMiddleStartPos) {
	TriangleHilbertCurve downLeft(downLeftStartPos, blockSize, Direction::up, Direction::left);
	TriangleHilbertCurve downMiddle(downMiddleStartPos, blockSize, Direction::down, Direction::left);
	TriangleHilbertCurve downRight(downRightStartPos, blockSize, Direction::up, Direction::left);
	TriangleHilbertCurve upMiddle(upMiddleStartPos, blockSize, Direction::up, Direction::right);
	addCurve(downLeft);
	addCurve(downMiddle);
	addCurve(downRight);
	addCurve(upMiddle);
}

void TriangleHilbertCurve::developDownLeftCurves(double blockSize, Point downLeftStartPos, Point downMiddleStartPos,
	Point downRightStartPos, Point upMiddleStartPos) {
	TriangleHilbertCurve upLeft(downLeftStartPos, blockSize, Direction::down, Direction::left);
	TriangleHilbertCurve upMiddle(downMiddleStartPos, blockSize, Direction::up, Direction::left);
	TriangleHilbertCurve upRight(downRightStartPos, blockSize, Direction::down, Direction::left);
	TriangleHilbertCurve downMiddle(upMiddleStartPos, blockSize, Direction::down, Direction::right);
	addCurve(upLeft);
	addCurve(upMiddle);
	addCurve(upRight);
	addCurve(downMiddle);
}

void TriangleHilbertCurve::developUpRightLines(double length, double blockSize, double dividedLength) {
	double limHalfBlock = (blockSize / 2) + (dividedLength / 2);
	LineWithPos leftLine(Point(getStartPos().getX() + (blockSize / 2), getStartPos().getY() + blockSize + dividedLength),
		Point(getStartPos().getX() + limHalfBlock, getStartPos().getY() + blockSize + ((1 - triRatio) * dividedLength)),
		Direction::left);
	LineWithPos rightLine(Point(getStartPos().getX() + (length / 2), getStartPos().getY() + length - (triRatio * dividedLength)),
		Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY() + length),
		Direction::left);
	LineWithPos upLine(Point(getStartPos().getX() + (1.5 * blockSize) + dividedLength, getStartPos().getY() + blockSize + dividedLength),
		Point(getStartPos().getX() + blockSize + limHalfBlock, getStartPos().getY() + blockSize),
		Direction::down);
	addLine(leftLine);
	addLine(rightLine);
	addLine(upLine);
}

void TriangleHilbertCurve::developDownRightLines(double length, double blockSize, double dividedLength) {
	double limHalfBlock = (blockSize / 2) + (dividedLength / 2);
	LineWithPos leftLine(Point(getStartPos().getX() + (blockSize / 2), getStartPos().getY() + blockSize),
		Point(getStartPos().getX() + limHalfBlock, getStartPos().getY() + blockSize + (dividedLength * triRatio)),
		Direction::left);
	LineWithPos rightLine(Point(getStartPos().getX() + (length / 2), getStartPos().getY() + (dividedLength * triRatio)),
		Point(getStartPos().getX() + blockSize + dividedLength, getStartPos().getY()),
		Direction::left);
	LineWithPos downLine(Point(getStartPos().getX() + length - (blockSize / 2), getStartPos().getY() + blockSize),
		Point(getStartPos().getX() + blockSize + limHalfBlock, getStartPos().getY() + blockSize + dividedLength),
		Direction::down);
	addLine(leftLine);
	addLine(rightLine);
	addLine(downLine);
}

void TriangleHilbertCurve::developUpLeftLines(double length, double blockSize, double dividedLength) {
	double limHalfBlock = (blockSize / 2) + (dividedLength / 2);
	LineWithPos rightLine(Point(getStartPos().getX() + length - (blockSize / 2), getStartPos().getY() + length - blockSize),
		Point(getStartPos().getX() + blockSize + limHalfBlock, getStartPos().getY() + blockSize + ((1 - triRatio) * dividedLength)),
		Direction::left);
	LineWithPos leftLine(Point(getStartPos().getX() + (length / 2), getStartPos().getY() + length - (triRatio * dividedLength)),
		Point(getStartPos().getX() + blockSize, getStartPos().getY() + length),
		Direction::left);
	LineWithPos upLine(Point(getStartPos().getX() + (blockSize / 2), getStartPos().getY() + blockSize + dividedLength),
		Point(getStartPos().getX() + limHalfBlock, getStartPos().getY() + blockSize),
		Direction::down);
	addLine(rightLine);
	addLine(leftLine);
	addLine(upLine);
}

void TriangleHilbertCurve::developDownLeftLines(double length, double blockSize, double dividedLength) {
	double limHalfBlock = (blockSize / 2) + (dividedLength / 2);
	LineWithPos rightLine(Point(getStartPos().getX() + (1.5 * blockSize) + dividedLength, getStartPos().getY() + blockSize),
		Point(getStartPos().getX() + blockSize + limHalfBlock, getStartPos().getY() + blockSize + (triRatio * dividedLength)),
		Direction::left);
	LineWithPos leftLine(Point(getStartPos().getX() + (length / 2), getStartPos().getY() + (triRatio * dividedLength)),
		Point(getStartPos().getX() + blockSize, getStartPos().getY()),
		Direction::left);
	LineWithPos downLine(Point(getStartPos().getX() + (blockSize / 2), getStartPos().getY() + blockSize),
		Point(getStartPos().getX() + limHalfBlock, getStartPos().getY() + blockSize + dividedLength),
		Direction::down);
	addLine(rightLine);
	addLine(leftLine);
	addLine(downLine);
}

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

IMPLEMENT_SERIAL(TriangleHilbertCurve, CObject, VERSIONABLE_SCHEMA | 1)
void TriangleHilbertCurve::Serialize(CArchive& ar) {
	Curve::Serialize(ar);
	if (ar.IsStoring()) {
		ar << horDir << verDir;
	}
	else {
		ar >> horDir >> verDir;
	}
}
