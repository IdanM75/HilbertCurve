#pragma once
#include "Line.h"
#include <vector>
#include <iostream>
using namespace std;


// CRTP
template<class CurveType, class LineType>
class Curve : public CObject {
private:
	Point startPos; // Top left corner
	double length;
	int level = 0;
	vector<LineType> lines;
	vector<CurveType> curves;
public:
	int maxLevel = 1;

	// Constructors and Destructor
	Curve() : length { 0 } {} // Empty constructor is necessary for the serialization
	Curve(Point startPos, double length) : startPos{ startPos }, length{ length } {}
	Curve(const Curve& c) : startPos{ c.getStartPos() }, length{ c.getLength() }, level{ c.getLevel() },
		lines{ c.getLines() }, curves{ c.getCurves() }, maxLevel{ c.maxLevel } {} // Needed to create for the serialization
	virtual ~Curve() {}

	// Getters
	Point getStartPos() const { return startPos; }
	double getLength() const { return length; }
	int getLevel() const { return level; }
	vector<LineType> getLines() const { return lines; }
	LineType& getLine(int index) { return lines[index]; }
	vector<CurveType> getCurves() const { return curves; }
	CurveType& getCurve(int index) { return curves[index]; }
	vector<LineType> getAllLines() {
		vector<LineType> temp;
		vector<LineType> tempTemp;
		for (unsigned int i = 0; i < lines.size(); i++) {
			temp.push_back(lines[i]);
		}
		if (level > 0) {
			for (unsigned int i = 0; i < curves.size(); i++) {
				tempTemp = curves[i].getAllLines();
				temp.insert(temp.end(), tempTemp.begin(), tempTemp.end());
			}
		}
		return temp;
	}

	// Setters
	void setStartPos(const Point& pos) { startPos = pos; }
	void setLength(double len) { length = len; }
	void setLevel(int lev) { level = lev; }
	void setLines(const vector<LineType> ls) { lines = ls; }
	void setCurves(const vector<CurveType> cs) { curves = cs; }
	void addLine(const LineType& l) { lines.push_back(l); }
	void addCurve(const CurveType& c) { curves.push_back(c); }

	// Others
	void clearLines() { lines.clear(); }
	void clearCurves() { curves.clear(); }
	virtual bool isInside(const Point& p) const = 0;
	virtual void drawGuiCurve(CDC* pDC) {
		for (unsigned int i = 0; i < lines.size(); i++) {
			lines[i].drawGuiLine(pDC);
		}
		if (level > 0) {
			for (unsigned int i = 0; i < curves.size(); i++) {
				curves[i].drawGuiCurve(pDC);
			}
		}
	}
	virtual void develop() = 0;

	// Serialization
	void Serialize(CArchive& ar) {
		if (ar.IsStoring()) {
			startPos.Serialize(ar);
			ar << length << level << maxLevel;
			ar << lines.size();
			for (unsigned int i = 0; i < lines.size(); i++) {
				lines[i].Serialize(ar);
			}
			ar << curves.size();
			for (unsigned int i = 0; i < curves.size(); i++) {
				curves[i].Serialize(ar);
			}
		}
		else {
			startPos.Serialize(ar);
			ar >> length >> level >> maxLevel;
			unsigned int linesSize;
			ar >> linesSize;
			for (unsigned int i = 0; i < linesSize; i++) {
				LineType tempLine;
				tempLine.Serialize(ar);
				lines.push_back(tempLine);
			}
			unsigned int curvesSize;
			ar >> curvesSize;
			for (unsigned int i = 0; i < curvesSize; i++) {
				CurveType tempCurve;
				tempCurve.Serialize(ar);
				curves.push_back(tempCurve);
			}
		}
	}
};
