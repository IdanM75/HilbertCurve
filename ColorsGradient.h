#pragma once
#include "pch.h"
#include "Color.h"
#include<vector>
using namespace std;


class ColorsGradient : public CObject {
private:
	vector<Color> colors;
	Color currentColor;
	int currentStep = 0;
	int currentColorIndex = 0;
public:
	// Constructor
	ColorsGradient(); // Empty constructor is necessary for the serialization
	ColorsGradient(Color firstColor);
	ColorsGradient(const ColorsGradient& cg);

	// Getters
	vector<Color> getColors() const;
	Color getColor() const;
	Color getColor(int index) const; 

	// Setters
	void setColors(vector<Color> cs);
	void addColor(Color c);

	// Other
	void prograde(int ColorAmount);   // ColorAmount: How much different colors you want to have
	void reset();

	// Serialization
	DECLARE_SERIAL(ColorsGradient);
	void Serialize(CArchive& ar);
};