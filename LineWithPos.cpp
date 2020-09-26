#include "pch.h"
#include "LineWithPos.h"


LineWithPos::LineWithPos() : Line(), dir{ Direction::down } {}

LineWithPos::LineWithPos(Point pa, Point pb, Direction dir) : Line(pa, pb), dir{ dir } {}

Direction LineWithPos::getDir() const { return dir; }

void LineWithPos::setDir(Direction dir) { dir = dir; }

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

IMPLEMENT_SERIAL(LineWithPos, CObject, VERSIONABLE_SCHEMA | 1)
void LineWithPos::Serialize(CArchive& ar) {
	Line::Serialize(ar);
	if (ar.IsStoring()) {
		ar << dir;
	}
	else {
		ar >> dir;
	}
}