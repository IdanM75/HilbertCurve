#include "pch.h"
#include "Color.h"

Color::Color() : red{ 0 }, green{ 0 }, blue{ 0 } {}

Color::Color(int r, int g, int b) : red{ r }, green{ g }, blue{ b } {}

Color::Color(const Color& c) : red{ c.getRed() }, green{ c.getGreen() }, blue{ c.getBlue() } {}

int Color::getRed() const { return red; }

int Color::getGreen() const { return green; }

int Color::getBlue() const { return blue; }

void Color::setRed(int r) { red = r; }

void Color::setGreen(int g) { green = g; }

void Color::setBlue(int b) { blue = b; }

const Color& Color::operator=(const Color& c) {
	red = c.getRed();
	green = c.getGreen();
	blue = c.getBlue();
	return *this;
}

IMPLEMENT_SERIAL(Color, CObject, VERSIONABLE_SCHEMA | 1)
void Color::Serialize(CArchive& ar) {
	if (ar.IsStoring()) {
		ar << red << green << blue;
	}
	else {
		ar >> red >> green >> blue;
	}
}
