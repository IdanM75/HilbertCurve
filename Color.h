#pragma once
#include "pch.h"


class Color : public CObject{
private:
	int red = 0;
	int green = 0;
	int blue = 0;
public:
	// Constructors
	Color();
	Color(int r, int g, int b);
	Color(const Color& c);

	// Getters
	int getRed() const;
	int getGreen() const;
	int getBlue() const;

	// Setters
	void setRed(int r);
	void setGreen(int g);
	void setBlue(int b);

	// Overloaded
	const Color& operator=(const Color& c);

	// Serialization
	DECLARE_SERIAL(Color);
	void Serialize(CArchive& ar);
};